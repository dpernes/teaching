/*****************************************************************/
/*   Grafo c/ matriz de adjacencias | PROG2 | MIEEC | 2018/19    */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/* cria grafo com n vertices */
grafo* grafo_novo(int n)
{
    int v;
    grafo* g;

    g = (grafo*)malloc(sizeof(grafo));
    g->tamanho = n;

    /* cria array de listas de adjacencias */
    g->adjacencias = (int**)malloc(n * sizeof(int*));
    for(v=0; v<n; v++)
    {
        g->adjacencias[v] = (int*)calloc(n, sizeof(int));
    }

    return g;
}

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g)
{
    if(g == NULL)
        return;

    if(g->adjacencias != NULL)
    {
        int v;
        for (v = 0; v < g->tamanho; v++)
            free(g->adjacencias[v]);
        free(g->adjacencias);
    }
    free(g);
}

/* adiciona no grafo g uma aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta ja existir e 1 se foi adicionada */
int grafo_adiciona(grafo *g, int origem, int dest)
{
    /* alinea 1.1 */
    if(!g)
        return -1;
    if((origem < 0) || (dest < 0))
        return -1;
    if((origem > g->tamanho-1) || (dest > g->tamanho-1))
        return -1;

    if(g->adjacencias[origem][dest])
        return 0;
    else
    {
        g->adjacencias[origem][dest] = 1;
        return 1;
    }
}

/* remove do grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se foi removida */
int grafo_remove(grafo *g, int origem, int dest)
{
    /* alinea 1.1 */
    if(!g)
        return -1;
    if((origem < 0) || (dest < 0))
        return -1;
    if((origem > g->tamanho-1) || (dest > g->tamanho-1))
        return -1;

    if(!g->adjacencias[origem][dest])
        return 0;
    else
    {
        g->adjacencias[origem][dest] = 0;
        return 1;
    }
}

/* testa no grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se existir */
int grafo_aresta(grafo *g, int origem, int dest)
{
     /* alinea 1.1 */
    if(!g)
        return -1;
    if((origem < 0) || (dest < 0))
        return -1;
    if((origem > g->tamanho-1) || (dest > g->tamanho-1))
        return -1;

    return g->adjacencias[origem][dest];
}

/* cria um novo grafo com base numa lista de adjacencias
   parametro adjacencies e' um array de inteiros, representado
   um numero n_edges de arestas.
   retorna um apontador para o grafo criado */
grafo* grafo_deLista(int* adjacencias, int n_arestas)
{
    /* alinea 1.2 */
    if(!adjacencias || (n_arestas < 1))
        return NULL;

    int tamanho = adjacencias[0];
    for(int i = 1; i < 2*n_arestas; i++)
    {
        if(adjacencias[i] > tamanho)
            tamanho = adjacencias[i];
    }
    tamanho += 1;

    grafo *g = grafo_novo(tamanho);
    if(!g)
        return NULL;

    for(int i = 0; i < n_arestas; i++)
    {
        if(grafo_adiciona(g, adjacencias[2*i], adjacencias[2*i+1]) == -1)
        {
            grafo_apaga(g);
            return NULL;
        }
    }
    return g;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de destino de todas as arestas com origem em i */
vetor* grafo_arestasSaida(grafo* g, int i)
{
    /* alinea 1.3 */
    if(!g || (i < 0))
        return NULL;

    vetor *v = vetor_novo();
    if(!v)
        return NULL;

    // complexidade: O(g->tamanho)
    for(int j = 0; j < g->tamanho; j++)
    {
        if(grafo_aresta(g, i, j))
        {
            if(vetor_insere(v, j, -1) == -1)
            {
                vetor_apaga(v);
                return NULL;
            }
        }
    }

    return v;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de origem de todas as arestas com destino a i */
vetor* grafo_arestasEntrada(grafo* g, int i)
{
    /* alinea 1.3 */
    if(!g || (i < 0))
        return NULL;

    vetor *v = vetor_novo();
    if(!v)
        return NULL;

    // complexidade: O(g->tamanho)
    for(int j = 0; j < g->tamanho; j++)
    {
        if(grafo_aresta(g, j, i))
        {
            if(vetor_insere(v, j, -1) == -1)
            {
                vetor_apaga(v);
                return NULL;
            }
        }
    }

    return v;
}

/* verifica se o grafo g e' completo
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o grafo for completo e 0 se nao o for */
int grafo_completo(grafo* g)
{
    /* alinea 1.4 */
    if(!g)
        return -1;

    // complexidade: O(n^2), onde n é o número de nós no grafo (n = g->tamanho)
    for(int i = 0; i < g->tamanho; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(!grafo_aresta(g, i, j) && !grafo_aresta(g, j, i))
                return 0;
        }
    }
    return 1;
}

/* verifica se o vertice i do grafo g e' uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o vertice for uma celebridade e 0 se nao o for */
int grafo_eCelebridade(grafo* g, int i)
{
    /* alinea 1.5 */
    if(!g || (i < 0))
        return -1;

    // complexidade: O(n), onde n é o número de nós no grafo (n = g->tamanho)
    for(int j = 0; j < g->tamanho; j++)
    {
        if(j == i)
            continue;
        if(grafo_aresta(g, i, j) || !grafo_aresta(g, j, i))
            return 0;
    }
    return 1;
}

/* verifica se o grafo g tem pelo menos uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se existir uma celebridade e 0 se nao existir */
int grafo_temCelebridade(grafo* g)
{
    /* alinea 1.5 */
    if(!g)
        return -1;

    // complexidade: O(n^2) onde n é o número de nós no grafo (n = g->tamanho)
    for(int i = 0; i < g->tamanho; i++)
    {
        if(grafo_eCelebridade(g, i))
            return 1;
    }
    return 0;
}

/* imprime as adjacencias do grafo */
void grafo_imprime(grafo* g)
{
    int i, j;

    if (g == NULL)
        return;

    for (i = 0; i < g->tamanho; i++)
    {
        printf("%d: ", i);
        for(j = 0; j < g->tamanho; j++)
        {
            if(g->adjacencias[i][j] != 0)
                printf("%d ", j);
        }
        printf("\n");
    }
}
