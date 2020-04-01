#include <stdio.h>
#include <string.h>
#include "bst.h"
#include "avl.h"

#define MAX_LEN 128
#define N_QUERIES 3

const char QUERY_STR[N_QUERIES][MAX_LEN] = {
    "Portugal",
    "Spain",
    "Russia"
};

int main()
{
    FILE *f = fopen("cidades.txt", "r");
    if(!f)
        return -1;
    arvore_avl *avl = avl_nova();
    char cidade_pais[MAX_LEN], *pais;
    int pais_cnt = 0;

    printf("Inserção em árvore AVL... ");
    while(fgets(cidade_pais, MAX_LEN-1, f))
    {
        // formato de cada linha: <nome_da_cidade>,<nome_do_país>
        cidade_pais[strlen(cidade_pais)-1] = '\0';
        strtok(cidade_pais, ",");  // retorna a cidade
        pais = strtok(NULL, ",");  // retorna o país
        avl_insere(avl, pais);
        pais_cnt++;
    }
    printf("%d países inseridos (com possíveis repetições)\n", pais_cnt);

    for(int i = 0; i < N_QUERIES; i++)
    {
        no_avl *no = avl_pesquisa(avl, QUERY_STR[i]);
        if(!no)
            printf("%s não encontrado\n", QUERY_STR[i]);
        else
            printf("%s – %d\n", QUERY_STR[i], no->contador);
    }

    return 0;
}