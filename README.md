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
 
