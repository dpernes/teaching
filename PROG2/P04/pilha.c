/*****************************************************************/
/*                Pilha | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include "pilha.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

pilhaItem* pilha_novo_elemento(int valor)
{
    /* aloca memoria para a estrutura pilhaItem */
    pilhaItem *item = (pilhaItem *) malloc(sizeof(pilhaItem));
    if(item == NULL)
        return NULL;

    item->elemento = valor;

    /* item ainda nao tem proximo */
    item->proximo = NULL;

    return item;
}

pilha* pilha_nova()
{
    /* cria pilha */
    pilha *p = (pilha*) malloc(sizeof(pilha));
    if(p == NULL)
        return NULL;

    /* pilha esta' vazia */
    p->raiz = NULL;
    p->tamanho = 0;

  return p;
}


void pilha_apaga(pilha *p)
{
    pilhaItem *aux;

    if(p==NULL)
        return;

    /* percorre toda a pilha e liberta memoria de cada item */
    while(p->raiz)
    {
        aux = p->raiz;
        p->raiz = p->raiz->proximo;
        free(aux);
    }

    free(p);
    return;
}

int	pilha_vazia(pilha *p)
{
    if(p == NULL)
        return 1;

    return p->raiz == NULL;
}

int pilha_tamanho(pilha *p)
{
    if (p == NULL)
        return -1;

    return p->tamanho;
}


int pilha_top(pilha *p)
{
    pilhaItem *aux;

    if (p == NULL || p->tamanho == 0)
        return INT_MIN;

    aux = p->raiz;
    return aux->elemento;
}

void pilha_push(pilha *p, int valor)
{
    pilhaItem *novo = NULL;

    if (p == NULL)
        return;

    /* cria novo item */
    novo = pilha_novo_elemento(valor);
    if (novo == NULL)
    return;

    p->tamanho++;

    /* inserir no topo da pilha */
    /* se a pilha esta vazia */
    if (p->raiz == NULL)
    {
        p->raiz = novo;
        return;
    }

    /* primeiro elemento */
    novo->proximo = p->raiz;
    p->raiz = novo;
}

void pilha_pop(pilha *p)
{
    pilhaItem *curr;

    if (p == NULL || p->tamanho == 0)
        return;

    curr = p->raiz;
    p->raiz = curr->proximo;
    p->tamanho--;

    /* liberta memoria associada ao item removido */
    free(curr);
}
