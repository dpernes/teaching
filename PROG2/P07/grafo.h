/*****************************************************************/
/*   Grafo c/ matriz de adjacencias | PROG2 | MIEEC | 2018/19    */
/*****************************************************************/

#ifndef _GRAFO_H_
#define _GRAFO_H_

#include "vetor.h"

/* grafo e' uma matriz de adjacencias.
   tamanho da matriz e' o numero de vertices no grafo */
typedef struct
{
    int tamanho;        /* numero de vertices */
    int **adjacencias;  /* matriz de adjacencias */
} grafo;

/* cria grafo com n vertices */
grafo* grafo_novo(int n);

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g);

/* adiciona uma aresta ao grafo*/
int grafo_adiciona(grafo *g, int origem, int dest);

/* remove uma aresta do grafo*/
int grafo_remove(grafo *g, int origem, int dest);

/* verifica se existe uma aresta entre os vertices origem e dest */
int grafo_aresta(grafo *g, int origem, int dest);

/* cria novo grafo dada uma sequencia de pares de adjacencias e o numero de arestas */
grafo* grafo_deLista(int* adjacencias, int n_arestas);

/* cria vetor com os vertices de destino com origem i */
vetor* grafo_arestasSaida(grafo* g, int i);

/* cria vetor com os vertices de origem com destino i */
vetor* grafo_arestasEntrada(grafo* g, int i);

/* verifica se o grafo g e' completo */
int grafo_completo(grafo* g);

/* verifica se o vertice i do grafo g e' uma celebridade */
int grafo_eCelebridade(grafo* g, int i);

/* verifica se o grafo g tem pelo menos uma celebridade */
int grafo_temCelebridade(grafo* g);

/* imprime as adjacencias do grafo */
void grafo_imprime(grafo* g);

#endif
