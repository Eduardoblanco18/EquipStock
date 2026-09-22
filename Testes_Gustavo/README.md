O arquivo `EquipStock-portatil-windows-x64.zip` tem os executaveis do programa em C e do testador Rust .

Extraia o ZIP todo, deixe os dois executaveis juntos e abra `qa_laboratorio.exe`. Informe a quantidade de equipamentos. A verificacao aparece na janela do Rust e o arquivo `relatorio_qa.txt` fica na pasta extraida. Para sair, digite **0 no C** e pressione Enter no Rust.

O app funciona sem instalar Rust e o `programa.exe` tambem funciona sozinho.

O codigo principal fica em `programa.c` e `BibliotecaLista.h`, fora dessa pasta. O conversor eh opcional: `Python/gerador_excel.py` 
Para recompilar, instale Rust com o alvo `x86_64-pc-windows-msvc` e GCC MinGW de 64 bits (bibliotecas no C para conversar com rust exige outro compilador diferente do code blocks). No PowerShell execute: (caso nao conseguir e quiser muito mudar o rust, me avisa que eu posso ajudar)

```powershell
New-Item -ItemType Directory -Force output\portatil | Out-Null
gcc -O2 -static -s programa.c -o output\programa.exe -Wall -Wextra
cargo rustc --manifest-path Testes_Gustavo\qa_laboratorio\Cargo.toml --release -- -C target-feature=+crt-static
Copy-Item output\programa.exe output\portatil\programa.exe -Force
Copy-Item Testes_Gustavo\qa_laboratorio\target\release\qa_laboratorio.exe output\portatil\qa_laboratorio.exe -Force
Copy-Item Testes_Gustavo\README.md output\portatil\LEIA-ME.md -Force
Compress-Archive -Path output\portatil\qa_laboratorio.exe,output\portatil\programa.exe,output\portatil\LEIA-ME.md -DestinationPath Testes_Gustavo\EquipStock-portatil-windows-x64.zip -Force
```
