use std::io::{self, Write};
use std::process::{Command, Stdio};
use std::fs::File;

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
    clear();
    println!("testador bom, use certo.");
    print!("quantos produtos voce quer testar? ");
    io::stdout().flush().unwrap();

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n_produtos: usize = input.trim().parse().unwrap_or(0);

    if n_produtos == 0 {
        println!("Nenhum produto para testar. ");
        return;
    }

    let mut saidas = String::new();
    let mut expec: Vec<EquipEsp> = Vec::new();

   
    for i in 1..=n_produtos {
        let codigo_s = 1000 + i as i32; 
        let codigo_e = format!("OSC00{}", i);
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

        saidas.push_str("6\n");

       
        expec.push(EquipEsp {
            codigo_s, codigo_e, nome, prioridade, periodo
        });
    }

    if !expec.is_empty() {
        let codalvo = expec[0].codigo_s;
        saidas.push_str("2\n");
        saidas.push_str(&format!("{}\n", codalvo));
        saidas.push_str("6\n");
        
    }
    saidas.push_str("0\n");

  
   

    
   //POR FAVOR LEIA EU
   //LEIA ISSO SE FOR USAR O RUST -------
   //                                   |
   //                                   |
   //                                   V
   //presta atenção aqui se for usar.
   // altere "./programa" para o nome do exe gerado pelo Codeblocks
   //NAO PRECISA DO .EXE, APENAS DOQ ESTA ANTES DO .EXE!!!
    
    let mut child = Command::new("../programa") //altera isso aqui 
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("compila o arquivo ou muda o programa_c aqui no rust bobão");

   
    if let Some(mut stdin) = child.stdin.take() {
        stdin.write_all(saidas.as_bytes()).expect("cu"); //stdin
    }

    
    let output = child.wait_with_output().expect("deu merda"); //stdout
    let stdout_str = String::from_utf8_lossy(&output.stdout);

    println!("\nResultado");
    println!("{}", stdout_str);
    println!("\n");

    println!("verificando...");
    let mut sucesso_total = true;

println!("verificando e gerando TXT...");
    let mut sucesso_total = true;

    // Cria o arquivo TXT na mesma pasta
    let mut arquivo_txt = File::create("relatorio_qa.txt").expect("Não foi possível criar o arquivo txt");
    
    // Escreve o cabeçalho das colunas
    writeln!(arquivo_txt, "Código Solicitação;Código Equipamento;Nome Equipamento;Prioridade;Período (dias);Status QA").unwrap();

    for exp in &expec {
        let encontrousaida = stdout_str.contains(&exp.codigo_s.to_string());
        let encontrounome = stdout_str.contains(&exp.nome);

        let status_excel;
        if encontrousaida && encontrounome {
            println!("equipamento {} codS: {} inserido e exibido certo", exp.nome, exp.codigo_s);
            status_excel = "aprovado";
        } else {
            println!("equipamento {} nn foi encontrado na listagem da opção 6", exp.nome);
            sucesso_total = false;
            status_excel = "reprovado";
        }

        
        writeln!(arquivo_txt, "{};{};{};{};{};{}", 
            exp.codigo_s, exp.codigo_e, exp.nome, exp.prioridade, exp.periodo, status_excel
        ).unwrap();
    }

    if sucesso_total {
        println!("\n{} equipamentos foram aprovados conforme as regras", n_produtos);
    } else {
        println!("\ncoisas estão um pouco erradas. da um jeito nesse programa");
    }
}