#ifndef BIBLIOTECALISTA_H_INCLUDED
#define BIBLIOTECALISTA_H_INCLUDED

/* FUNÇÕES DE MANIPULAÇÃO DE LISTA

Lista* CriaLista() CRIA A LISTA

int listaVazia(Lista *L) VERIFICA SE A LISTA ESTÁ VAZIA (1) OU NÃO (0)

void liberarLista(Lista *L) LIBERA A LISTA DA MEMORIA

void adicionarNaLista(Lista *L, Equip valores) ADICIONA UM EQUIPAMENTO NA LISTA (JÁ ORDENADO)

void removerDaLista(Lista *L, int codS) REMOVE UM EQUIPAMENTO DA LISTA DE ACORDO COM O CÓDIGO DE SOLITAÇÃO
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
