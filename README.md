# Tutorial
Compile os dois arquivos C com o code blocks.

Compile o araquivo rust e de cargo run uma vez para gerar a pasta target/debug.

Após isso coloque os dois exe gerado pelo C na pasta debug.

Rode o Rust novamente e teste

# O que faltou fazer
1 -> Corrigir inserção de código duplicado em auxadicionarlista(). É possível inserir dois equipamentos com o mesmo codigoS.

2 -> Em auxRemoveLista se tentar remover um codigo nao existente, pode chegar em apag==NULL e ainda assim executar aux->prox=apag->prox, ou seja NULL->prox, fazendo com que o programa crasha. Além disso, a função printa Lista vazia! mesmo depois de remover normalmente.

3 -> Ainda faltou a função para consultar alguma solicitação, recebe codigoS, consulta na lista e mostra todas as informações do equipamento.

4 -> Colocar no programa principal a chamada para a funçõa de aletrar o período, função ja feita na header: int alterarurgencia(lista *l, int codigoS, int periodo)

5 -> Colocar no programa principal a chamada para mostrar a lista de urgencia, função ja feita na header: lista *criarListaUrgencia(Lista *principal) (lista *urgencia = criarlistaurgencia, imprimirlista(urgencia), liberarlista(urgencia)).

6 -> Corrigir periodo na inserção, ainda tem como fazer periodo de 10 dias com prioridade 1, mas tem que ser prioridade 1-> 1 a 7 dias, prioridade 2-> 1-15 dias, prioridade 3-> 1-20 dias.

7 -> o codigo do equipamento tem que ser exatamente 3 chars no começo com mais 3 ints no final, precisa fazer algo para verificar posições de 0 - 2 e de 3 - 5.

8 -> pesquisei e o isdigit() serve para verificar um caractere, e nao um int. é só fazer onde tem isdigt um (scanf("%d",&novo.codigoS)!=1). se scanf da certo ele retorna 1, entao se de errado ele nao le oq o usuario colocou de errado.



# Lembretes
1 ---> NO FINAL DE TUDO o menu final DEVE ficar exatamente nessa ordem:

1 - Inserir Solicitaçao.

2 - Remover Solicitação.

3 - Consultar Solicitação.

4 - Alterar prioridade/periodo.

5 - exibir ordem de manuntenção

6 - exixibir todas as solicitações.

7 ou 0 - Sair do programa

# Funções designadas

1 -> Eduardo

2 -> Eduardo

3 -> Eduardo

4 -> Gustavo

5 -> Gustavo

6 -> Gustavo

7 -> Ulisses

8 -> Ulisses


# Gustavo

4 — Alterar prioridade e/ou período

A "BibliotecaLista.h" já possui:

int alterarprioridade(Lista *L, int codigoS, int prioridade);
int alterarurgencia(Lista *L, int codigoS, int periodo);
int periodovalido(int prioridade, int periodo);

Falta fazer

- [ ] Atualizar o "case 4" do "programa.c".
- [ ] Permitir que o usuário escolha entre:
  - alterar somente prioridade;
  - alterar somente período;
  - alterar prioridade e período.
- [ ] Chamar "alterarurgencia()" quando o usuário quiser mudar o período.
- [ ] Validar as entradas com "scanf(...) != 1".
- [ ] Caso prioridade e período sejam alterados juntos, validar o novo período usando a nova prioridade.



Não fazer

alterarprioridade(Labs, codigo, prioridade);
alterarurgencia(Labs, codigo, periodo);

porque "alterarprioridade()" verifica o período antigo.

Criar uma função específica para alterar os dois valores de uma vez.

---

5 — Exibir ordem de manutenção

Essa parte já está praticamente pronta na "BibliotecaLista.h".

Já existem:

int antes(Equip a, Equip b);
No *auxadicionarNaListaUrgencia(No *inicio, Equip x);
void adicionarNaListaUrgencia(Lista *L, Equip x);
Lista *criarListaUrgencia(Lista *principal);

A lista de urgência já é ordenada por:

1º Prioridade
2º Menor período
3º Menor código da solicitação

Falta fazer

- [ ] Criar o "case 5" no "programa.c".
- [ ] Criar uma lista temporária usando:

Lista *Urgencia = criarListaUrgencia(Labs);

- [ ] Mostrar a lista:

imprimirLista(Urgencia);

- [ ] Liberar a memória depois:

liberarLista(Urgencia);



Não é necessário manter:

Lista *Urgencia = CriaLista();

no começo do "main".

A lista de urgência pode ser criada somente quando a opção 5 for usada.

---

6 — Validar período durante a inserção

A função necessária já existe:

int periodovalido(int prioridade, int periodo);

Ela já considera:

Prioridade 1 -> 1 até 7 dias
Prioridade 2 -> 1 até 15 dias
Prioridade 3 -> 1 até 20 dias

Problema atual

Na inserção o programa verifica apenas:

1 até 20 dias

Então atualmente ainda seria possível inserir:

Prioridade = 1
Período = 18

mesmo sendo inválido.

Falta fazer

- [ ] Remover a validação antiga com "isdigit()".
- [ ] Validar o "scanf".
- [ ] Usar "periodovalido()" antes de adicionar o equipamento.

---

Correção necessária para testar as funções

case 5:

e:

case 6:

dentro do "switch".

Ordem 

1. Fazer o Item 6, porque é o mais simples.
2. Fazer o Item 5, porque toda a lógica da lista já está pronta.
3. Fazer o Item 4, porque precisa tratar o caso de alterar prioridade e período simultaneamente.


 
