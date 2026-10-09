#ifndef BIBLIOTECALISTA_H_INCLUDED
#define BIBLIOTECALISTA_H_INCLUDED

/* FUN��ES DE MANIPULA��O DE LISTA

Lista* CriaLista() CRIA A LISTA

int listaVazia(Lista *L) VERIFICA SE A LISTA EST� VAZIA (1) OU N�O (0)

void liberarLista(Lista *L) LIBERA A LISTA DA MEMORIA

void adicionarNaLista(Lista *L, Equip valores) ADICIONA UM EQUIPAMENTO NA LISTA (J� ORDENADO)

void removerDaLista(Lista *L, int codS) REMOVE UM EQUIPAMENTO DA LISTA DE ACORDO COM O C�DIGO DE SOLITA��O

void imprimeDados(Equip x) IMPRIME DADOS ESPEC�FICOS DE UM EQUIPAMENTO

int existeCodigo(Lista *L, int cod) VERIFICA SE UM C�DIGO DE SOLITA��O EXISTE(1) OU N�O (0)

void consultaLista(Lista *L, int cod) PROCURA UM C�DIGO DE SOLITA��O NA LISTA E IMPRIME OS DADOS DO EQUIPAMENTOS

void adicionarNaListaUrgencia(Lista*L, Equip Prioridade) ADICIONA UM ELEMENTO NA LISTA DE URGENCIA DE ACORDO OM A PRIORIDADE ENVIADA

int alterarprioridade(Lista *L, int codigoS, int prioridade) ALTERA A PRIORIDADE ANTIGA PELA PASSADA PELO USUARIO DE UM EQUIPAMENTO
*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>





typedef struct equipamento
{
    int codigoS;
    char codigoE[7];
    char nomeEquip[21];
    int prioridade;
    int periodo;
} Equip;

typedef struct no
{
    Equip info;
    struct no *prox;
}No;

typedef struct lista
{
    No *inicio;
}Lista;

Lista* CriaLista()
{
    Lista *aux;
    aux = (Lista*) malloc(sizeof(Lista));
    aux ->inicio = NULL;
    return aux;
}

int listaVazia(Lista *L)
{
    if(L->inicio == NULL)
    {
        return 1;
    }
    return 0;
}

void liberarLista(Lista *L)
{
    if(!listaVazia(L))
    {
        No *apag;
        while (!listaVazia(L))
        {
            apag = L->inicio;
            L->inicio = L->inicio->prox;
            free(apag);
        }
    }

    free(L);
}


// ERRO: nao ta funcionando. permite dois  codigos com valores iguais.
No* auxAdicionarLista(No *velho, Equip x)
{
    No *novo;
    novo = (No*) malloc(sizeof(No));
    novo->info = x;
    novo->prox = NULL;
    if(velho == NULL )
    {
        return novo;
    }
    No *aux = velho;
    if(aux->info.codigoS < x.codigoS)
    {
        No *auxProx = aux->prox;
        while(auxProx != NULL && auxProx->info.codigoS < x.codigoS)
        {
            aux = auxProx;
            auxProx = auxProx ->prox;
        }
        novo->prox = auxProx;
        aux->prox = novo;
    }
    else
    {
        novo->prox = velho;
        return novo;
    }

    return velho;
}

void adicionarNaLista(Lista *L, Equip valores)
{
    L->inicio = auxAdicionarLista(L->inicio, valores);
}


//ERRO: tambem com erro, permite remover valor que nao existe.
No* auxRemoveLista(No *velho, int cod)
{
    No *aux = velho;
    if(aux->info.codigoS == cod)
    {
        velho = aux->prox;
        free(aux);
    }
    else
    {
        No *apag = aux->prox;
        while(apag != NULL && apag->info.codigoS != cod)
        {
            aux = apag;
            if (apag == NULL){
                return velho;
            }
            apag = apag->prox;
        }
        aux->prox = apag->prox;
        free(apag);
    }
    return velho;
}

void removerDaLista(Lista *L, int codS)
{
    if(!listaVazia(L))
    {
        L->inicio = auxRemoveLista(L->inicio, codS);
    }
    printf("Lista vazia! Impossível continuar");
}

void imprimeDados(Equip x)
{
    printf("\tCódigo de Solitação: %d\n", x.codigoS);
    printf("\tCódigo do Equipamento: %s\n", x.codigoE);
    printf("\tNome do Equipamento: %s\n", x.nomeEquip);
    printf("\tNível Prioridade: %d\n", x.prioridade);
    printf("\tPeríodo de Espera: %d\n", x.periodo);
    printf("-------------------------------\n");
}

int existeCodigo(Lista *L, int cod)
{
    if(!listaVazia(L))
    {
        No *aux = L->inicio;
        while(aux != NULL)
        {
            if(aux->info.codigoS == cod)
            {
                return 1;
            }
            aux = aux->prox;
        }
    }

    return 0;
}

void consultaLista(Lista *L, int cod)
{
    if(existeCodigo(L, cod))
    {
        No *aux = L->inicio;
        while(aux->info.codigoS != cod)
        {
            aux = aux->prox;
        }
        imprimeDados(aux->info);
    }
    else
    {
        printf("\nEsse código não existe, tente outro");
    }
}


    int antes(Equip a, Equip b){
    if (a.prioridade != b.prioridade){
        return a.prioridade<b.prioridade; // se a.prioridade nao for igual a b.prioridade e for maior, retorna 1 se nao, 0. se for igual vai pra frente e assim por diante
    }
    if (a.periodo!=b.periodo){
        return a.periodo<b.periodo;
    }
    return a.codigoS<b.codigoS; //se codigo de solicitacao de a maior retorna 1 senao, 0 e essa eh a logica do desempate.
    }



No* auxadicionarNaListaUrgencia(No* inicio, Equip x){

    No* novo = (No*) malloc(sizeof(No));
    if (novo ==NULL){
        return inicio;
    }
    novo->info=x;
    novo->prox = NULL;
    if (inicio==NULL || antes(x, inicio->info)){
        novo->prox = inicio;
        return novo;
    }
    No *aux = inicio;
    while(aux->prox!=NULL && !antes(x, aux->prox->info)){
        aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
    return inicio;
}

void adicionarNaListaUrgencia(Lista *L, Equip x){
    L->inicio = auxadicionarNaListaUrgencia(L->inicio, x);


}

Lista *criarListaUrgencia (Lista *principal) {
    Lista *urgencia = CriaLista();
    No*aux = principal->inicio;
    while (aux!=NULL){
        adicionarNaListaUrgencia(urgencia, aux->info);
        aux = aux->prox;
    }
    return urgencia;
}


//Lista *urgencia = criarListaUrgencia(listaPrincipal);

int periodovalido(int prioridade, int periodo){
    if (periodo < 1){
        return 0;
    } // se periodo menos que 1 dia nao pode
    if (prioridade == 1) {
        return periodo <= 7; //se a prioridade for 1 e periodo menor ou igual a 7, pode, entao retorna verdadeiro, se nao falso, e assim por diante.
    }
    if (prioridade == 2){ 
        return periodo <=15;
    }
    if (prioridade == 3){
        return periodo <=20;
    }
    return 0; //se maior que 3 nao pode entao tambem retorna 0
 //evitar o uso de ifs e elses e colocar returns no lugar aumenta sim a velocidade do programa. embora haja os ifs antes dos returns.
    // se eu fosse fazer sem return eu colocaria diversos ifs e elses, entao optamos pelos returns aqui.

}




int alterarprioridade(Lista *L, int codigoS, int prioridade){

    if (prioridade<1|| prioridade>3){
        printf("nao da");
        return 0;
    }
    No* aux = L->inicio;
    while (aux!=NULL && aux->info.codigoS != codigoS){
        aux = aux->prox;
    }
    if (aux == NULL){
        printf("\nEquipamento inválido");
        return 0;
    }
    if (!periodovalido(prioridade, aux->info.periodo)) //agora e so chamar a funcao que ja retorna verdadeiro ou falso, entao fica mais facil de fazer o alterar prioridade
    {
        printf("\n O periodo atual de %d dias nao é valido para a prioridade %d. \n", aux->info.periodo, prioridade);
        return 0;
    }
    aux->info.prioridade = prioridade;
    printf("\nSolicitação %d: prioridade %d", codigoS, aux->info.prioridade);
    return 1;




}

int alterarurgencia(Lista*L, int codigoS, int periodo){

  No* aux = L->inicio;
  while (aux!=NULL && aux->info.codigoS != codigoS){
    aux=aux->prox;
  } if (aux==NULL){
    printf("\nVoce quer alterar a urgencia de um equipamento que nao existe.\n");
    return 0;
  }


  if (!periodovalido(aux->info.prioridade, periodo)){ //eh como se o a funcao periodo valido fosse uma condicao de parada.
        printf("\n O periodo atual de %d dias nao é valido para a prioridade %d. \n", aux->info.periodo, aux->info.prioridade);
        return 0;
  }

  printf("\nEquipamento %d com urgencia %d", codigoS, aux->info.periodo);
  aux->info.periodo = periodo;
  printf(" teve o seu periodo alterado para %d.", aux->info.periodo);

  return 1;
}
int alterarprioridadeperiodo(Lista *L, int codigoS, int prioridade, int periodo)
{
    No *aux = L->inicio;

    while (aux != NULL && aux->info.codigoS != codigoS)
    {
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        printf("\nEquipamento invalido.\n");
        return 0;
    }

    if (prioridade < 1 || prioridade > 3)
    {
        printf("\nPrioridade invalida.\n");
        return 0;
    }

    if (!periodovalido(prioridade, periodo)) //veja so como fica mais facil
    {
        printf("\nPeriodo invalido para a prioridade %d.\n", prioridade);
        return 0;
    }

    aux->info.prioridade = prioridade;
    aux->info.periodo = periodo;

    printf("\nPrioridade alterada para %d.", aux->info.prioridade);
    printf("\nPeriodo alterado para %d dias.\n", aux->info.periodo);

    return 1;
}

void imprimirLista(Lista *L)
{
    if(!listaVazia(L))
    {
        setlocale(LC_ALL, "portuguese-brazilian");
        No *aux = L->inicio;
        Equip x;
        printf("\n");
        while(aux != NULL)
        {
            imprimeDados(aux->info);
            aux= aux->prox;
        }
    }
    else
    {
        printf("Lista Vazia! Impossível continuar");
        // exit(1);
    }
}
#endif // BIBLIOTECALISTA_H_INCLUDED
