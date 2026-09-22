#ifndef BIBLIOTECALISTA_H_INCLUDED
#define BIBLIOTECALISTA_H_INCLUDED

/* FUNÇÕES DE MANIPULAÇÃO DE LISTA

Lista* CriaLista() CRIA A LISTA

int listaVazia(Lista *L) VERIFICA SE A LISTA ESTÁ VAZIA (1) OU NÃO (0)

void liberarLista(Lista *L) LIBERA A LISTA DA MEMORIA

void adicionarNaLista(Lista *L, Equip valores) ADICIONA UM EQUIPAMENTO NA LISTA (JÁ ORDENADO)

void removerDaLista(Lista *L, int codS) REMOVE UM EQUIPAMENTO DA LISTA DE ACORDO COM O CÓDIGO DE SOLITAÇÃO

void adicionarNaListaUrgencia(Lista*L, Equip Prioridade) ADICIONA UM ELEMENTO NA LISTA DE URGENCIA DE ACORDO OM A PRIORIDADE ENVIADA

int alterarprioridade(Lista *L, int codigoS, int prioridade) ALTERA A PRIORIDADE ANTIGA PELA PASSADA PELO USUARIO DE UM EQUIPAMENTO
*/



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
    if(aux->info.codigoS < codS)
    {
        No *auxProx = aux->prox;
        while(auxProx->info.codigoS < codS)
        {
            aux = auxProx;
            auxProx = auxProx ->prox;
        }
        novo->prox = auxProx;
        aux->prox = novo;
    }
    else
    {
        novo->prox = aux;
        velho->prox = novo;
    }

    return velho;
}

void adicionarNaLista(Lista *L, Equip valores)
{
    L->inicio = auxAdicionarLista(L->inicio, valores);
}

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
        while(apag->info.codigoS != cod)
        {
            aux = apag;
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
    printf("Lista vazia! Imposs�vel continuar");
    exit(1);
}
    No* auxAdicionarListaUrgencia(No* velho, x){
    No *novo = (No*) malloc(sizeof(No));
    novo->info = x;
    novo->prox = NULL;
    if(velho == NULL )
    {
        return novo;
    }
    No *aux = velho;
    if(aux->info.prioridade < novo->info.prioridade)
    {
        No *auxProx = aux->prox;
        while(auxProx->info.prioridade < novo->info.prioridade)
        {
            aux = auxProx;
            auxProx = auxProx ->prox;
        }
        novo->prox = auxProx;
        aux->prox = novo;
    }
    else
    {
        novo->prox = aux;
        velho->prox = novo;
    }

    return velho;

    }

    int antes(Equip a, Equip b){
    if (a.prioridade != b.prioridade){
        return a.prioridade<b.prioridade;
    }
    if (a.periodo!=b.periodo){
        return a.periodo<b.periodo;
    }
    return a.codigoS<b.codigoS;
    }



void auxadicionarNaListaUrgencia(No* inicio, Equip x){

    No* novo = (No*) malloc(sizeof(No));
    if (novo ==NULL){
        return inicio;
    }
    novo->info=x;
    novo->prox = NULL;
    if (inicio==NULL || vemantes(x, inicio->info)){
        novo->prox = inicio;
        return novo;
    }
    No *aux = inicio;
    while(aux->prox!=NULL && !vemantes(x, aux->prox->info)){
        aux = aux->prox;
    }
    novo->prox = aux-prox;
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
    }
    if (prioridade == 1) {
        return periodo <= 7;
    }
    if (prioridade == 2){
        return periodo <=15;
    }
    if (prioridade == 3){
        return periodo <=20;
    }
    return 0;


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
    if (!periodovalido(prioridade, aux->info.periodo))
    {
        printf("\n O periodo atual de %d dias nao é valido para a prioridade %d. \n", aux->info.periodo, prioridade);
        return 0;
    }
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


  if (!periodovalido(aux->info.prioridade, periodo)){
        printf("\n O periodo atual de %d dias nao é valido para a prioridade %d. \n", aux->info.periodo, prioridade);
        return 0;
  }

  printf("\nEquipamento %d com urgencia %d", codigoS, aux->info.periodo);
  aux->info.periodo = periodo;
  printf(" teve o seu periodo alterado para %d.". aux->info.periodo);

  return 1;
}

void imprimirLista(Lista *L)
{
    if(!listaVazia(L))
    {
        No *aux = L->inicio;
        Equip x;
        printf("\n");
        while(aux != NULL)
        {
            x = aux->info;
            printf("\tCódigo de Solita��o: %d\n", x.codigoS);
            printf("\tC�digo do Equipamento: %s\n", x.codigoE);
            printf("\tNome do Equipamento: %s\n", x.nomeEquip);
            printf("\tN�vel Prioridade: %d\n", x.prioridade);
            printf("\tPer�odo de Espera: %d\n", x.periodo);
            printf("-------------------------------\n");
            aux= aux->prox;
        }
    }
    else
    {
        printf("Lista Vazia! Imposs�vel continuar");
        exit(1);
    }
}
#endif // BIBLIOTECALISTA_H_INCLUDED
