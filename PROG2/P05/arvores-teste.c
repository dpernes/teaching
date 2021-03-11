#include <stdio.h>
#include <time.h>
#include <string.h>
#include "bst.h"
#include "avl.h"

#define MAX_LEN 128
#define MAX_COUNT -1
#define QUERY_STR "Zywiec,Poland"

int main()
{
    /* TESTES BST */
    arvore_bst *bst = bst_nova();

    bst_insere(bst, "G");
    bst_insere(bst, "C");
    bst_insere(bst, "A");
    bst_insere(bst, "F");
    bst_insere(bst, "L");
    bst_insere(bst, "J");
    bst_insere(bst, "V");
    bst_insere(bst, "M");
    bst_insere(bst, "N");
    bst_insere(bst, "O");

    int altura_raiz = bst_altura(bst->raiz);
    printf("Altura da raiz BST: %d\n", altura_raiz);

    printf("Travessia em pré-ordem da árvore BST: ");
    bst_imprime(bst);

    bst_apaga(bst);
    printf("\n");
    /***/

    /* TESTES AVL */
    arvore_avl *avl = avl_nova();

    avl_insere(avl, "G");
    avl_insere(avl, "C");
    avl_insere(avl, "A");
    avl_insere(avl, "F");
    avl_insere(avl, "L");
    avl_insere(avl, "J");
    avl_insere(avl, "V");
    avl_insere(avl, "M");
    avl_insere(avl, "N");
    avl_insere(avl, "O");

    altura_raiz = avl_altura(avl->raiz);
    printf("Altura da raiz AVL: %d\n", altura_raiz);

    printf("Travessia em pré-ordem da árvore AVL: ");
    avl_imprime(avl);

    avl_remove(avl, "N");
    avl_remove(avl, "V");

    avl_apaga(avl);
    printf("\n");
    /***/

    /* TESTES DE DESEMPENHO */
    clock_t inicio, fim;
    double tempo;
    char cidade[MAX_LEN];
    int cidade_cnt = 0;
    FILE *f = fopen("cidades.txt", "r");
    if(!f)
        return -1;

    printf("Inserção em árvore BST... ");
    bst = bst_nova();
    inicio = clock();
    while(fgets(cidade, MAX_LEN-1, f))
    {
        cidade[strlen(cidade)-1] = '\0';
        bst_insere(bst, cidade);
        cidade_cnt++;
        if(cidade_cnt == MAX_COUNT) break;
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%d cidades inseridas\n", cidade_cnt);
    printf("tempo em segundos: %lf\n\n", tempo);
    fseek(f, 0, SEEK_SET);
    cidade_cnt = 0;

    printf("Inserção em árvore AVL... ");
    avl = avl_nova();
    inicio = clock();
    while(fgets(cidade, MAX_LEN-1, f))
    {
        cidade[strlen(cidade)-1] = '\0';
        avl_insere(avl, cidade);
        cidade_cnt++;
        if(cidade_cnt == MAX_COUNT) break;
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%d cidades inseridas\n", cidade_cnt);
    printf("tempo em segundos: %lf\n\n", tempo);
    fclose(f);
    cidade_cnt = 0;

    printf("Pesquisa em árvore BST (query = %s)... ", QUERY_STR);
    inicio = clock();
    if(!bst_pesquisa(bst, QUERY_STR))
        printf("não encontrado!\n");
    else
        printf("encontrado\n");
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n\n", tempo);

    printf("Pesquisa em árvore AVL (query = %s)... ", QUERY_STR);
    inicio = clock();
    if(!avl_pesquisa(avl, QUERY_STR))
        printf("não encontrado!\n");
    else
        printf("encontrado\n");
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n\n", tempo);

    bst_apaga(bst);
    avl_apaga(avl);

    f = fopen("cidades_sorted.txt", "r");
    if(!f)
        return -1;

    printf("Inserção ordenada em árvore BST... ");
    bst = bst_nova();
    inicio = clock();
    while(fgets(cidade, MAX_LEN-1, f))
    {
        cidade[strlen(cidade)-1] = '\0';
        bst_insere(bst, cidade);
        cidade_cnt++;
        if(cidade_cnt == MAX_COUNT) break;
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%d cidades inseridas\n", cidade_cnt);
    printf("tempo em segundos: %lf\n\n", tempo);
    fseek(f, 0, SEEK_SET);
    cidade_cnt = 0;

    printf("Inserção ordenada em árvore AVL... ");
    avl = avl_nova();
    inicio = clock();
    while(fgets(cidade, MAX_LEN-1, f))
    {
        cidade[strlen(cidade)-1] = '\0';
        avl_insere(avl, cidade);
        cidade_cnt++;
        if(cidade_cnt == MAX_COUNT) break;
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%d cidades inseridas\n", cidade_cnt);
    printf("tempo em segundos: %lf\n\n", tempo);
    fclose(f);
    cidade_cnt = 0;

    printf("Pesquisa em árvore BST (query = %s)... ", QUERY_STR);
    inicio = clock();
    if(!bst_pesquisa(bst, QUERY_STR))
        printf("não encontrado!\n");
    else
        printf("encontrado\n");
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n\n", tempo);

    printf("Pesquisa em árvore AVL (query = %s)... ", QUERY_STR);
    inicio = clock();
    if(!avl_pesquisa(avl, QUERY_STR))
        printf("não encontrado!\n");
    else
        printf("encontrado\n");
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n\n", tempo);

    bst_apaga(bst);
    avl_apaga(avl);

    return 0;
}