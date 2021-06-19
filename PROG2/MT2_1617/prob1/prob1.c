#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "grafo.h"

/*** problema 1.1 ***/
char *avl_maiorstring(no_avl *no)
{
    if (!no)
        return NULL;

    char *str_no = no->str;
    char *str_esq = avl_maiorstring(no->esquerda); // procurar a maior string na sub-árvore da esquerda
    char *str_dir = avl_maiorstring(no->direita);  // procurar a maior string na sub-árvore da direita

    // calcular os tamanhos das três strings (string NULL tem tamanho 0)
    int tam_no = 0, tam_esq = 0, tam_dir = 0;
    if (str_no != NULL)
        tam_no = strlen(str_no);
    if (str_esq != NULL)
        tam_esq = strlen(str_esq);
    if (str_dir != NULL)
        tam_dir = strlen(str_dir);

    // comparar os tamanhos para determinar qual a maior das três strings
    int max_tam = tam_no;
    char *max_str = str_no;
    if (tam_esq > max_len)
    {
        max_len = tam_esq;
        max_str = str_esq;
    }
    if (tam_dir > max_len)
    {
        max_len = tam_dir;
        max_str = str_dir;
    }

    return max_str;
}

/*** problema 1.2 ***/

/*
Solução 1 (mais simples, menos eficiente):
    Utilizar a função grafo_bfs para determinar a distância entre a origem e cada um dos restantes nós.
    Guardar as distâncias entre a origem e cada um dos nós num vetor.
    Procurar o máximo do vetor de distâncias.

Solução 2 (menos óbvia, mais eficiente): ver código abaixo.
*/

/* função auxiliar de grafo_maisdistante (chamada recursivamente) */
int grafo_maisdistante_rec(grafo *g, int vertice_atual, int *visitados, int *distancia)
{
    visitados[vertice_atual] = 1; // marca o nó atual como visitado
    int max_dist = -1, max_vertice = vertice_atual;

    // percorre os filhos do nó atual e procura aquele que retorna a maior distância
    for (lista_no *aresta = g->adjacencias[vertice_atual].inicio; aresta != NULL; aresta = aresta->proximo)
    {
        if (visitados[aresta->vertice]) // se já visitámos este nó, este caminho não é mínimo, logo é descartado
            continue;

        int dist, vertice = grafo_maisdistante_rec(g, aresta->vertice, visitados, &dist);
        if (dist > max_dist)
        {
            max_dist = dist;
            max_vertice = vertice;
        }
    }

    // a distância retornada ao nó-pai é 1 + a maior distância retornada pelos nós-filhos
    *distancia = 1 + max_dist;
    return max_vertice;
}

int grafo_maisdistante(grafo *g, int origem, int *distancia)
{
    if ((g == NULL) || (origem < 0) || (origem > g->tamanho - 1) || (distancia == NULL))
        return -1;

    int visitados[g->tamanho]; // array auxiliar para registar que nós já foram visitados
    for (int i = 0; i < g->tamanho; i++)
        visitados[i] = 0; // inicialmente, nenhum nó foi ainda visitado

    // chamar a função auxiliar recursivamente a partir do nó origem
    return grafo_maisdistante_rec(g, origem, visitados, distancia);
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    FILE *fp = fopen("paises.txt", "r");
    char str_aux[MAX_STR], *str;

    /* teste problema 1.1 */
    {
        arvore_avl *arv;
        puts("* Problema 1.1 *");
        arv = avl_nova();
        while (fgets(str_aux, MAX_STR, fp) != NULL)
        {
            if (str_aux[strlen(str_aux) - 1] == '\n')
                str_aux[strlen(str_aux) - 1] = '\0';
            avl_insere(arv, str_aux);
        }
        str = avl_maiorstring(arv->raiz);
        printf("Maior string: ");
        if (str != NULL)
            puts(str);
        else
            puts("(null)");
        avl_apaga(arv);
    }

    /* teste problema 1.2 */
    {
        grafo *g;
        int vertice, comprimento;
        puts("\n* Problema 1.2 *");
        g = grafo_novo(8, DIGRAFO);
        grafo_adiciona(g, 0, 4);
        grafo_adiciona(g, 1, 0);
        grafo_adiciona(g, 1, 5);
        grafo_adiciona(g, 2, 1);
        grafo_adiciona(g, 3, 2);
        grafo_adiciona(g, 4, 3);
        grafo_adiciona(g, 5, 4);
        grafo_adiciona(g, 6, 3);
        grafo_adiciona(g, 7, 2);
        grafo_adiciona(g, 7, 6);

        vertice = grafo_maisdistante(g, 1, &comprimento);
        if (vertice != -1)
            printf("Mais distante do vertice 1: %d (distancia %d)\n", vertice, comprimento);
        vertice = grafo_maisdistante(g, 6, &comprimento);
        if (vertice != -1)
            printf("Mais distante do vertice 6: %d (distancia %d)\n", vertice, comprimento);

        grafo_apaga(g);
    }

    fclose(fp);
    return 0;
}
