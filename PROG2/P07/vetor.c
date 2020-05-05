/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2018/19           */
/*****************************************************************/

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

vetor* vetor_novo()
{
    vetor* vec;

    /* aloca memoria para a estrutura vetor */
    vec = (vetor*)malloc(sizeof(vetor));
    if(vec == NULL)
    return NULL;

    vec->tamanho = 0;
    vec->capacidade = 0;
    vec->elementos = NULL;

    return vec;
}

void vetor_apaga(vetor* vec)
{
    if(vec == NULL)
    return;

    /* liberta memoria do array */
    free(vec->elementos);

    /* liberta memoria da estrutura vetor */
    free(vec);
}

int vetor_atribui(vetor* vec, int pos, int valor)
{
    if (vec == NULL || pos < 0 || pos >= vec->tamanho)
        return -1;

    vec->elementos[pos] = valor;

    return pos;
}

int vetor_tamanho(vetor* vec)
{
    if(vec == NULL)
        return -1;

    return vec->tamanho;
}

int vetor_elemento(vetor* vec, int indice)
{
    if (vec == NULL || indice < 0 || indice >= vec->tamanho)
        return -1;

    return vec->elementos[indice];
}

int vetor_insere(vetor* vec, int valor, int pos)
{
    int i;

    if(vec == NULL || pos < -1 || pos > vec->tamanho)
        return -1;

    /* aumenta elementos do vetor se capacidade nao for suficiente */
    if(vec->tamanho == vec->capacidade)
    {
        if(vec->capacidade == 0)
        vec->capacidade = 1;
        else
        vec->capacidade *= 2;

        vec->elementos = (int*)realloc(vec->elementos, vec->capacidade * sizeof(int));
        if(vec->elementos == NULL)
        return -1;
    }

    /* se pos=-1 insere no fim do vetor */
    if(pos == -1)
        pos = vec->tamanho;

    /* copia todos os elementos a partir da posicao pos ate' ao fim do vetor para pos+1 */
    for(i=vec->tamanho-1; i>=pos; i--)
    {
        vec->elementos[i+1] = vec->elementos[i];
    }

    /* copia valor */
    vec->elementos[pos] = valor;

    vec->tamanho++;

    return pos;
}

int vetor_remove(vetor* vec, int pos)
{
    int i;

    if(vec == NULL || pos < 0 || pos >= vec->tamanho)
        return -1;

    /* copia todos os elementos a partir da posicao pos+1 ate' ao fim do vetor para pos */
    for(i=pos+1; i<vec->tamanho; i++)
    {
        vec->elementos[i-1] = vec->elementos[i];
    }

    vec->tamanho--;

    return 0;
}
