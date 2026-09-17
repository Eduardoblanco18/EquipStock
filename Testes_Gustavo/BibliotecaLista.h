#ifndef BIBLIOTECALISTA_H_INCLUDED
#define BIBLIOTECALISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} No;

typedef struct lista
{
    No *inicio;
} Lista;

Lista* CriaLista()
{
    Lista *aux = (Lista*) malloc(sizeof(Lista));
    aux->inicio = NULL;
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
    No *novo = (No*) malloc(sizeof(No));
    novo->info = x;
    novo->prox = NULL;

    if(velho == NULL)
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
            auxProx = auxProx->prox;
        }
        novo->prox = auxProx;
        aux->prox = novo;
    }
    else
    {
        novo->prox = aux;
        velho = novo; 
    }

    return velho;
}

void adicionarNaLista(Lista *L, Equip valores)
{
    L->inicio = auxAdicionarLista(L->inicio, valores);
}

No* auxRemoveLista(No *velho, int cod)
{
    if (velho == NULL) return NULL;

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
            apag = apag->prox;
        }
        if (apag != NULL) {
            aux->prox = apag->prox;
            free(apag);
        }
    }
    return velho;
}

void removerDaLista(Lista *L, int codS)
{
    if(!listaVazia(L))
    {
        L->inicio = auxRemoveLista(L->inicio, codS);
    } else {
        printf("Lista vazia! Impossível continuar\n");
    }
}
#endif // BIBLIOTECALISTA_H_INCLUDED