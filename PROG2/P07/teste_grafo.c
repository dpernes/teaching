#include "grafo.h"
#include <stdio.h>

int main()
{
    /* exemplo da alinea 1.2 */
    int adj[] = {1,2,1,3,1,4,2,5,3,5,4,5};
    grafo *g12 = grafo_deLista(adj, 6);
    grafo_imprime(g12);
    grafo_apaga(g12);

    /* outros testes */
    printf("\n");
    grafo *g = grafo_deLista(adj, 6);

    printf("arestasSaida(1) = {");
    vetor *s1 = grafo_arestasSaida(g, 1);
    for(int i = 0; i < s1->tamanho; i++)
        printf("%d,", vetor_elemento(s1, i));
    printf("}\n");

    printf("arestasEntrada(5) = {");
    vetor *e5 = grafo_arestasEntrada(g, 5);
    for(int i = 0; i < e5->tamanho; i++)
        printf("%d,", vetor_elemento(e5, i));
    printf("}\n");
    vetor_apaga(s1);
    vetor_apaga(e5);
    printf("\n");

    printf("g completo: %d\n\n", grafo_completo(g));
    grafo_adiciona(g, 0, 1);
    printf("aresta 0->1 adicionada\n");
    grafo_adiciona(g, 0, 2);
    printf("aresta 0->2 adicionada\n");
    grafo_adiciona(g, 0, 3);
    printf("aresta 0->3 adicionada\n");
    grafo_adiciona(g, 0, 4);
    printf("aresta 0->4 adicionada\n");
    grafo_adiciona(g, 0, 5);
    printf("aresta 0->5 adicionada\n");
    grafo_adiciona(g, 1, 5);
    printf("aresta 1->5 adicionada\n");
    grafo_adiciona(g, 2, 3);
    printf("aresta 2->3 adicionada\n");
    grafo_adiciona(g, 3, 4);
    printf("aresta 3->4 adicionada\n");
    grafo_adiciona(g, 4, 2);
    printf("aresta 4->2 adicionada\n");
    grafo_imprime(g);
    printf("g completo: %d\n\n", grafo_completo(g));

    for(int i = 0; i < g->tamanho; i++)
        printf("%d e' celebridade: %d\n", i, grafo_eCelebridade(g, i));
    printf("g tem celebridade: %d\n", grafo_temCelebridade(g));

    grafo_apaga(g);

    printf("\nFIM\n");

    return 0;
}
