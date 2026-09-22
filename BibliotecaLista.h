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

int alterarurgencia(Lista*L, int codigoS, int periodo) ALTERA O PERIODO DE DIAS RESTANTES ANTIGO DE UM EQUIPAMENTO PELO PASSADO PELO USUARIO. 
*/


typedef struct equipamento
{
    int codigoS;
    char[7] codigoE;
    char[21] nomeEquip;
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
    if(aux->info->codigoS < codS)
    {
        No *auxProx = aux->prox;
        while(auxProx->info->codigoS < codS)
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
    printf("Lista vazia! Impossível continuar");
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
    if(aux->info->prioridade < novo->info->prioridade)
    {
        No *auxProx = aux->prox;
        while(auxProx->info->prioridade < novo->info->prioridade)
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

void adicionarNaListaUrgencia(Lista* L, Equip prioridade){

    L->inicio=auxAdicionarListaUrgencia(L->inicio, prioridade);
}

int alterarprioridade(Lista *L, int codigoS, int prioridade){
  No* aux = L->inicio;
  while (aux!=NULL && aux->info->codigoS != codigoS){
    aux=aux->prox;
  } if (aux==NULL || aux->info->codigoS!=codigoS){
    printf("\nVoce quer alterar a prioridade de um equipamento que nao existe.\n");
    return 0;
  }

  printf("\nEquipamento %d com Prioridade %d", codigoS, aux->info->prioridade);
  aux->info->prioridade = prioridade;
  printf(" teve a sua prioridade alterada para %d.". aux->info->prioridade);

  return 1;
}

int alterarurgencia(Lista*L, int codigoS, int periodo){

  No* aux = L->inicio;
  while (aux!=NULL && aux->info->codigoS != codigoS){
    aux=aux->prox;
  } if (aux==NULL || aux->info->codigoS!=codigoS){
    printf("\nVoce quer alterar a urgencia de um equipamento que nao existe.\n");
    return 0;
  }

  printf("\nEquipamento %d com urgencia %d", codigoS, aux->info->periodo);
  aux->info->periodo = periodo;
  printf(" teve o seu periodo alterado para %d.". aux->info->periodo);

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
            printf("\tCódigo de Solitação: %d\n", x.codigoS);
            printf("\tCódigo do Equipamento: %s\n", x.codigoE);
            printf("\tNome do Equipamento: %s\n", x.nomeEquip);
            printf("\tNível Prioridade: %d\n", x.prioridade);
            printf("\tPeríodo de Espera: %d\n", x.periodo);
            printf("-------------------------------\n");
            aux= aux->prox;
        }
    }
    else
    {
        printf("Lista Vazia! Impossível continuar");
        exit(1);
    }
}
#endif // BIBLIOTECALISTA_H_INCLUDED
