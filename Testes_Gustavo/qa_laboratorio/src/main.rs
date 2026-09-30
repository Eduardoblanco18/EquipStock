use std::fs::File;
use std::io::{self, Read, Write};
use std::path::PathBuf;
use std::process::Command;
use std::thread;
use std::time::Duration;

#[cfg(windows)]
use std::os::windows::process::CommandExt;

const NOME_PROGRAMA_C: &str = "programarust";

#[cfg(windows)]
const CREATE_NEW_CONSOLE: u32 = 0x00000010;

struct EquipEsp {
    codigo_s: i32,
    codigo_e: String,
    nome: String,
    prioridade: i32,
    periodo: i32,
}

fn clear() {
    if cfg!(target_os = "windows") {
        let _ = Command::new("cmd")
            .args(["/c", "cls"])
            .status();
    } else {
        let _ = Command::new("clear").status();
    }
}

fn main() {
    let codigo = testar();

    println!("\nPressione Enter para fechar.");

    let mut input = String::new();
    let _ = io::stdin().read_line(&mut input);

    std::process::exit(codigo);
}

fn localizar_programa() -> Option<PathBuf> {
    let nome = if cfg!(windows) {
        format!("{}.exe", NOME_PROGRAMA_C)
    } else {
        NOME_PROGRAMA_C.to_string()
    };

    if let Ok(pasta) = std::env::current_dir() {
        let programa = pasta.join(&nome);

        if programa.is_file() {
            return Some(programa);
        }
    }

    let rust = std::env::current_exe().ok()?;
    let pasta_rust = rust.parent()?;

    let programa = pasta_rust.join(&nome);

    if programa.is_file() {
        return Some(programa);
    }

    for pasta in pasta_rust.ancestors() {
        let programa = pasta.join(&nome);

        if programa.is_file() {
            return Some(programa);
        }

        let programa = pasta
            .join("output")
            .join(&nome);

        if programa.is_file() {
            return Some(programa);
        }

        let programa = pasta
            .join("bin")
            .join("Debug")
            .join(&nome);

        if programa.is_file() {
            return Some(programa);
        }

        let programa = pasta
            .join("bin")
            .join("Release")
            .join(&nome);

        if programa.is_file() {
            return Some(programa);
        }
    }

    None
}

fn encontrar(buffer: &[u8], procurado: &[u8]) -> Option<usize> {
    buffer
        .windows(procurado.len())
        .position(|x| x == procurado)
}

fn testar() -> i32 {
    clear();

    println!("========================================");
    println!("        EquipStock - QA Rust");
    println!("========================================\n");

    print!("Quantos produtos voce quer testar? ");
    io::stdout().flush().unwrap();

    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .unwrap();

    let n_produtos: usize = match input.trim().parse() {
        Ok(n) => n,
        Err(_) => {
            println!("Digite um numero valido.");
            return 1;
        }
    };

    if n_produtos == 0 {
        println!("Nenhum produto para testar.");
        return 1;
    }

    if n_produtos > 999 {
        println!("Digite de 1 a 999 produtos.");
        return 1;
    }

    let mut entradas = String::new();
    let mut esperados = Vec::with_capacity(n_produtos);

    for i in 1..=n_produtos {
        let codigo_s = 1000 + i as i32;
        let codigo_e = format!("OSC{:03}", i);
        let nome = format!("osciloscopio_{}", i);

        let prioridade = (i % 3) as i32 + 1;

        let periodo = match prioridade {
            1 => 5,
            2 => 10,
            3 => 18,
            _ => unreachable!(),
        };

        entradas.push_str("1\n");
        entradas.push_str(&format!("{}\n", codigo_s));
        entradas.push_str(&format!("{}\n", codigo_e));
        entradas.push_str(&format!("{}\n", nome));
        entradas.push_str(&format!("{}\n", prioridade));
        entradas.push_str(&format!("{}\n", periodo));

        esperados.push(EquipEsp {
            codigo_s,
            codigo_e,
            nome,
            prioridade,
            periodo,
        });
    }

    let programa = match localizar_programa() {
        Some(p) => p,

        None => {
            println!(
                "\nNao encontrei {}.exe",
                NOME_PROGRAMA_C
            );

            println!(
                "Coloque o executavel do C perto do QA."
            );

            return 1;
        }
    };

    println!("\nPrograma encontrado:");
    println!("{}", programa.display());

    let pasta_qa = std::env::temp_dir().join(
        format!(
            "equipstock_qa_{}",
            std::process::id()
        )
    );

    if pasta_qa.exists() {
        let _ = std::fs::remove_dir_all(&pasta_qa);
    }

    if let Err(erro) = std::fs::create_dir_all(&pasta_qa) {
        println!(
            "Erro criando pasta temporaria: {}",
            erro
        );

        return 1;
    }

    let entrada_qa = pasta_qa.join("entrada.txt");
    let saida_qa = pasta_qa.join("saida.txt");

    let mut entrada = match File::create(&entrada_qa) {
        Ok(f) => f,

        Err(erro) => {
            println!(
                "Erro criando entrada.txt: {}",
                erro
            );

            return 1;
        }
    };

    if let Err(erro) = entrada.write_all(entradas.as_bytes()) {
        println!(
            "Erro escrevendo entrada.txt: {}",
            erro
        );

        return 1;
    }

    drop(entrada);

    let mut comando = Command::new(&programa);

    comando
        .env(
            "EQUIPSTOCK_QA_ENTRADA",
            &entrada_qa
        )
        .env(
            "EQUIPSTOCK_QA_SAIDA",
            &saida_qa
        );

    #[cfg(windows)]
    comando.creation_flags(CREATE_NEW_CONSOLE);

    let mut child = match comando.spawn() {
        Ok(child) => child,

        Err(erro) => {
            println!(
                "\nNao foi possivel abrir o programa C:"
            );

            println!("{}", erro);

            limpar_temporarios(
                &entrada_qa,
                &saida_qa,
                &pasta_qa
            );

            return 1;
        }
    };

    println!("\n========================================");
    println!(
        "{} equipamentos sendo enviados.",
        n_produtos
    );
    println!("Programa C aberto em outro CMD.");
    println!("========================================");

    println!(
        "\nDepois das insercoes, digite 3 no CMD do C."
    );

    println!(
        "Quando terminar, digite 0 no CMD do C."
    );

    let mut tentativas = 0;

    let mut arquivo_saida = loop {
        match File::open(&saida_qa) {
            Ok(file) => break file,

            Err(_) => {
                tentativas += 1;

                match child.try_wait() {
                    Ok(Some(status)) => {
                        println!(
                            "\nO programa C fechou antes de iniciar o QA."
                        );

                        println!("{}", status);

                        limpar_temporarios(
                            &entrada_qa,
                            &saida_qa,
                            &pasta_qa
                        );

                        return 1;
                    }

                    Ok(None) => {}

                    Err(erro) => {
                        println!(
                            "Erro verificando programa C: {}",
                            erro
                        );

                        return 1;
                    }
                }

                if tentativas >= 250 {
                    println!(
                        "\nO programa C nao criou saida.txt."
                    );

                    let _ = child.kill();

                    limpar_temporarios(
                        &entrada_qa,
                        &saida_qa,
                        &pasta_qa
                    );

                    return 1;
                }

                thread::sleep(
                    Duration::from_millis(20)
                );
            }
        }
    };

    let escolha = b"Escolha: ";

    let mut buffer: Vec<u8> = Vec::new();

    let mut menus = 0usize;
    let mut avisou = false;
    let mut verificado = false;
    let mut sucesso_total = true;

    let mut status_final = None;

    loop {
        let mut novos = Vec::new();

        match arquivo_saida.read_to_end(&mut novos) {
            Ok(_) => {}

            Err(erro) => {
                println!(
                    "\nErro lendo saida do C: {}",
                    erro
                );

                sucesso_total = false;
                break;
            }
        }

        if !novos.is_empty() {
            buffer.extend_from_slice(&novos);

            while let Some(pos) =
                encontrar(&buffer, escolha)
            {
                let trecho =
                    buffer[..pos].to_vec();

                buffer.drain(
                    ..pos + escolha.len()
                );

                menus += 1;

                let texto =
                    String::from_utf8_lossy(
                        &trecho
                    )
                    .to_string();

                if !avisou
                    && menus >= n_produtos + 1
                {
                    println!(
                        "\n{} equipamentos enviados para o C.",
                        n_produtos
                    );

                    println!(
                        "Agora digite 3 na janela do C."
                    );

                    avisou = true;
                }

                if texto.contains(
                    "-------------------------------"
                )
                    || texto.contains(
                        "Lista Vazia!"
                    )
                {
                    println!();
                    println!(
                        "========================================"
                    );
                    println!("LISTAGEM DETECTADA");
                    println!(
                        "========================================"
                    );

                    if !verificar(
                        &texto,
                        &esperados
                    ) {
                        sucesso_total = false;
                    }

                    verificado = true;

                    println!(
                        "\nDigite 3 novamente para testar de novo."
                    );

                    println!(
                        "Ou digite 0 no C para sair."
                    );
                }
            }
        }

        match child.try_wait() {
            Ok(Some(status)) => {
                status_final = Some(status);
                break;
            }

            Ok(None) => {
                thread::sleep(
                    Duration::from_millis(50)
                );
            }

            Err(erro) => {
                println!(
                    "\nErro acompanhando programa C: {}",
                    erro
                );

                sucesso_total = false;

                match child.wait() {
                    Ok(status) => {
                        status_final = Some(status);
                    }

                    Err(erro) => {
                        println!(
                            "Erro esperando programa C: {}",
                            erro
                        );

                        drop(arquivo_saida);

                        limpar_temporarios(
                            &entrada_qa,
                            &saida_qa,
                            &pasta_qa
                        );

                        return 1;
                    }
                }

                break;
            }
        }
    }

    let status_final = match status_final {
        Some(status) => status,

        None => {
            match child.wait() {
                Ok(status) => status,

                Err(erro) => {
                    println!(
                        "\nNao foi possivel obter o estado final do C: {}",
                        erro
                    );

                    drop(arquivo_saida);

                    limpar_temporarios(
                        &entrada_qa,
                        &saida_qa,
                        &pasta_qa
                    );

                    return 1;
                }
            }
        }
    };

    drop(arquivo_saida);

    limpar_temporarios(
        &entrada_qa,
        &saida_qa,
        &pasta_qa
    );

    if !status_final.success() {
        println!(
            "\nO programa C encerrou com erro:"
        );

        println!("{}", status_final);

        return 1;
    }

    if !verificado {
        println!(
            "\nNenhuma listagem foi verificada."
        );

        println!(
            "Use a opcao 3 antes de fechar o programa C."
        );

        return 1;
    }

    println!("\nPrograma C encerrado.");

    if sucesso_total {
        println!();
        println!(
            "========================================"
        );
        println!("          QA FINAL: APROVADO");
        println!(
            "========================================"
        );

        0
    } else {
        println!();
        println!(
            "========================================"
        );
        println!("         QA FINAL: REPROVADO");
        println!(
            "========================================"
        );

        1
    }
}

fn limpar_temporarios(
    entrada: &PathBuf,
    saida: &PathBuf,
    pasta: &PathBuf,
) {
    let _ = std::fs::remove_file(entrada);
    let _ = std::fs::remove_file(saida);
    let _ = std::fs::remove_dir_all(pasta);
}

fn verificar(
    saida: &str,
    esperados: &[EquipEsp],
) -> bool {
    println!("\nVerificando equipamentos...\n");

    let mut sucesso_total = true;

    let caminho = std::env::current_exe()
        .unwrap()
        .with_file_name("relatorio_qa.txt");

    let mut arquivo = match File::create(&caminho) {
        Ok(f) => f,

        Err(erro) => {
            println!(
                "Nao foi possivel criar relatorio: {}",
                erro
            );

            return false;
        }
    };

    writeln!(
        arquivo,
        "Código Solicitação;Código Equipamento;Nome Equipamento;Prioridade;Período (dias);Status QA"
    )
    .unwrap();

    let blocos: Vec<&str> =
        saida
            .split("-------------------------------")
            .collect();

    for exp in esperados {
        let esperado = vec![
            exp.codigo_s.to_string(),
            exp.codigo_e.clone(),
            exp.nome.clone(),
            exp.prioridade.to_string(),
            exp.periodo.to_string(),
        ];

        let encontrado = blocos.iter().any(
            |bloco| {
                let valores: Vec<String> =
                    bloco
                        .lines()
                        .filter_map(
                            |linha| {
                                linha
                                    .split_once(": ")
                                    .map(
                                        |(_, valor)| {
                                            valor
                                                .trim()
                                                .to_string()
                                        }
                                    )
                            }
                        )
                        .collect();

                valores
                    .windows(esperado.len())
                    .any(
                        |janela| {
                            janela
                                == esperado.as_slice()
                        }
                    )
            }
        );

        let status;

        if encontrado {
            println!(
                "[OK] {} | codigo {}",
                exp.nome,
                exp.codigo_s
            );

            status = "aprovado";
        } else {
            println!(
                "[ERRO] {} | codigo {} nao encontrado",
                exp.nome,
                exp.codigo_s
            );

            sucesso_total = false;
            status = "reprovado";
        }

        writeln!(
            arquivo,
            "{};{};{};{};{};{}",
            exp.codigo_s,
            exp.codigo_e,
            exp.nome,
            exp.prioridade,
            exp.periodo,
            status
        )
        .unwrap();
    }

    println!();

    if sucesso_total {
        println!(
            "{} equipamentos aprovados.",
            esperados.len()
        );
    } else {
        println!(
            "Foram encontrados erros na listagem."
        );
    }

    println!(
        "\nRelatorio: {}",
        caminho.display()
    );

    sucesso_total
}
