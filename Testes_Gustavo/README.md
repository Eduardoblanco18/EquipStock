O arquivo `EquipStock-portatil-windows-x64.zip` contem os executaveis do programa em C e do testador Rust para Windows 10 ou 11 de 64 bits.

Extraia o ZIP inteiro, mantenha os dois executaveis juntos e abra `qa_laboratorio.exe`. Informe a quantidade de equipamentos e digite **3 na janela do programa em C**. A verificacao aparece na janela do Rust e o arquivo `relatorio_qa.txt` fica na pasta extraida. Para sair, digite **0 no C** e pressione Enter no Rust.

O pacote funciona sem instalar Rust, Cargo, GCC, Code::Blocks ou Python. O `programa.exe` tambem funciona sozinho. Para levar ao outro PC, copie o ZIP; nao copie somente o executavel do Rust.

O codigo principal fica em `programa.c` e `BibliotecaLista.h`, na raiz do repositorio. O testador fica em `Testes_Gustavo/qa_laboratorio`. O conversor opcional `Python/gerador_excel.py` continua disponivel para transformar o relatorio em planilha.

Para recompilar, instale Rust com o alvo `x86_64-pc-windows-msvc` e GCC MinGW de 64 bits. No PowerShell, na raiz do repositorio, execute:

```powershell
New-Item -ItemType Directory -Force output\portatil | Out-Null
gcc -O2 -static -s programa.c -o output\programa.exe -Wall -Wextra
cargo rustc --manifest-path Testes_Gustavo\qa_laboratorio\Cargo.toml --release -- -C target-feature=+crt-static
Copy-Item output\programa.exe output\portatil\programa.exe -Force
Copy-Item Testes_Gustavo\qa_laboratorio\target\release\qa_laboratorio.exe output\portatil\qa_laboratorio.exe -Force
Copy-Item Testes_Gustavo\README.md output\portatil\LEIA-ME.md -Force
Compress-Archive -Path output\portatil\qa_laboratorio.exe,output\portatil\programa.exe,output\portatil\LEIA-ME.md -DestinationPath Testes_Gustavo\EquipStock-portatil-windows-x64.zip -Force
```
