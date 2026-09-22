use std::io::{self, BufRead, BufReader, Write};
use std::process::Command;
use std::fs::File;
use std::thread;
use std::time::Duration;
#[cfg(windows)]
use std::os::windows::process::CommandExt;

struct EquipEsp {
    codigo_s: i32,
    codigo_e: String,
    nome: String,
    prioridade: i32,
    periodo: i32,
}

pub fn clear() {
	if cfg!(target_os = "windows") {
        Command::new("cmd").args(["/c", "cls"]).status().unwrap();
    } else {
        Command::new("clear").status().unwrap();
    }
}

fn main() {
    let output = testar();
    println!("\nPressione Enter para fechar.");
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    std::process::exit(output);
}

fn testar() -> i32 {
    clear();
    println!("testador bom, use certo.");
    print!("quantos produtos voce quer testar? ");
    io::stdout().flush().unwrap();

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n_produtos: usize = input.trim().parse().unwrap_or(0);

    if n_produtos == 0 {
        println!("Nenhum produto para testar. ");
        return 0;
    }

    if n_produtos > 999 {
        println!("Digite de 1 a 999 produtos para manter os codigos dos equipamentos validos.");
        return 0;
    }

    let mut saidas = String::new();
    let mut expec: Vec<EquipEsp> = Vec::new();

   
    for i in 1..=n_produtos {
        let codigo_s = 1000 + i as i32; 
        let codigo_e = format!("OSC{:03}", i);
        let nome = format!("osciloscopio_{}", i);
        
       
        let prioridade = (i % 3) as i32 + 1;
        let periodo = match prioridade {
            1 => 5,  
            2 => 10, 
            3 => 18, 
            _ => 1,
        };

       
        saidas.push_str("1\n"); 
        saidas.push_str(&format!("{}\n", codigo_s));
        saidas.push_str(&format!("{}\n", codigo_e));
        saidas.push_str(&format!("{}\n", nome));
        saidas.push_str(&format!("{}\n", prioridade));
        saidas.push_str(&format!("{}\n", periodo));

       
        expec.push(EquipEsp {
            codigo_s, codigo_e, nome, prioridade, periodo
        });
    }

  
   

    
   //POR FAVOR LEIA EU
   //LEIA ISSO SE FOR USAR O RUST -------
   //                                   |
   //                                   |
   //                                   V
   //presta atenção aqui se for usar.
   // altere "./programa" para o nome do exe gerado pelo Codeblocks
   //NAO PRECISA DO .EXE, APENAS DOQ ESTA ANTES DO .EXE!!!
    
    let programa = std::env::current_exe().expect("Nao foi possivel localizar o testador");
    let pasta = programa.parent().unwrap();
    let programa = pasta.join("programa"); //altera isso aqui
    let programa = programa.with_extension(std::env::consts::EXE_EXTENSION);
    let programa = if programa.is_file() {
        programa
    } else {
        match pasta.ancestors().map(|pasta| {
            pasta.join("output/programa").with_extension(std::env::consts::EXE_EXTENSION)
        }).find(|programa| programa.is_file()) {
            Some(programa) => programa,
            None => {
                println!("Nao foi possivel encontrar o programa.exe. Mantenha os dois executaveis na mesma pasta.");
                return 1;
            }
        }
    };

    let pasta_qa = std::env::temp_dir().join(format!("equipstock_qa_{}", std::process::id()));
    std::fs::create_dir_all(&pasta_qa).expect("Nao foi possivel criar a pasta do teste");
    let entrada_qa = pasta_qa.join("entrada.txt");
    let saida_qa = pasta_qa.join("saida.txt");
    let mut stdin = File::create(&entrada_qa).expect("Nao foi possivel criar a entrada do teste"); //stdin
    stdin.write_all(saidas.as_bytes()).expect("Nao foi possivel gravar os equipamentos");
    drop(stdin);
    File::create(&saida_qa).expect("Nao foi possivel criar a saida do teste");

    let mut comando = Command::new(&programa);
    comando.env("EQUIPSTOCK_QA_ENTRADA", &entrada_qa)
        .env("EQUIPSTOCK_QA_SAIDA", &saida_qa);
    #[cfg(windows)]
    comando.creation_flags(0x00000010);

    let mut child = comando.spawn()
        .expect("Nao foi possivel abrir o programa.exe");

    println!("\nPrograma aberto em outra janela: {}", programa.display());
    println!("Digite 3 na janela do programa em C. A verificacao aparece aqui no Rust.");
    println!("Digite 0 na janela do programa em C para sair.");

    let mut stdout = BufReader::new(File::open(&saida_qa).expect("Nao foi possivel abrir a saida do teste")); //stdout
    let mut output = Vec::new();
    let mut saidas = Vec::new();
    let escolha = b"Escolha: ";
    let mut menus = 0;
    let mut verificado = false;
    let mut sucesso_total = true;
    let mut encerrado = false;

    loop {
        output.clear();
        let n = stdout.read_until(b' ', &mut output).expect("Nao foi possivel ler a saida do programa");
        if n == 0 {
            if encerrado {
                break;
            }
            encerrado = child.try_wait().expect("Nao foi possivel acompanhar o programa").is_some();
            if !encerrado {
                thread::sleep(Duration::from_millis(50));
            }
            continue;
        }

        saidas.extend_from_slice(&output[..n]);

        if saidas.ends_with(escolha) {
            let pos = saidas.len() - escolha.len();
            let stdout_str = String::from_utf8_lossy(&saidas[..pos]);
            menus += 1;

            if menus == n_produtos + 1 {
                println!("\n{} equipamentos enviados para teste.", n_produtos);
                println!("Aguardando a opcao 3 na janela do programa em C...");
            }

            if stdout_str.contains("-------------------------------") || stdout_str.contains("Lista Vazia!") {
                if !verificar(&stdout_str, &expec) {
                    sucesso_total = false;
                }
                verificado = true;
                println!("\nAguardando a proxima listagem no programa em C...");
            }

            saidas.clear();
        }
    }

    let output = child.wait().expect("deu merda");
    drop(stdout);
    std::fs::remove_file(&entrada_qa).expect("Nao foi possivel remover a entrada do teste");
    std::fs::remove_file(&saida_qa).expect("Nao foi possivel remover a saida do teste");
    std::fs::remove_dir(&pasta_qa).expect("Nao foi possivel remover a pasta do teste");
    if !output.success() {
        println!("\nO programa encerrou com erro: {}", output);
        return 1;
    }

    if !verificado {
        println!("\nNenhuma listagem foi verificada. Use a opcao 3 durante o teste.");
    }

    println!("\nO programa em C foi encerrado.");

    if !sucesso_total {
        return 1;
    }

    0
}

fn verificar(stdout_str: &str, expec: &[EquipEsp]) -> bool {
    println!("\nverificando e gerando TXT...");
    let mut sucesso_total = true;

    // Cria o arquivo TXT na mesma pasta
    let mut arquivo_txt = File::create(std::env::current_exe().unwrap().with_file_name("relatorio_qa.txt"))
        .expect("Não foi possível criar o arquivo txt");
    
    // Escreve o cabeçalho das colunas
    writeln!(arquivo_txt, "Código Solicitação;Código Equipamento;Nome Equipamento;Prioridade;Período (dias);Status QA").unwrap();

    for exp in expec {
        let encontrousaida = stdout_str.split("-------------------------------").any(|saida| {
            let valores: Vec<&str> = saida.lines()
                .filter_map(|linha| linha.split_once(": ").map(|(_, valor)| valor.trim()))
                .collect();
            valores == [
                exp.codigo_s.to_string(), exp.codigo_e.clone(), exp.nome.clone(),
                exp.prioridade.to_string(), exp.periodo.to_string()
            ]
        });

        let status_excel;
        if encontrousaida {
            println!("equipamento {} codS: {} inserido e exibido certo", exp.nome, exp.codigo_s);
            status_excel = "aprovado";
        } else {
            println!("equipamento {} nn foi encontrado com os dados esperados na listagem da opção 3", exp.nome);
            sucesso_total = false;
            status_excel = "reprovado";
        }

        
        writeln!(arquivo_txt, "{};{};{};{};{};{}", 
            exp.codigo_s, exp.codigo_e, exp.nome, exp.prioridade, exp.periodo, status_excel
        ).unwrap();
    }

    if sucesso_total {
        println!("\n{} equipamentos foram aprovados conforme as regras", expec.len());
    } else {
        println!("\ncoisas estão um pouco erradas. da um jeito nesse programa");
    }

    sucesso_total
}
