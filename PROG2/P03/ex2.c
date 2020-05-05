#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"

#define MAX_LEN 128
#define NPOS 10000

int main(int argc, char **argv)
{
    if(argc < 2) return -1;
    vetor *vec = vetor_novo();
    lista *lst = lista_nova();
    clock_t start_t, end_t;
    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }
    char str[MAX_LEN];

    /* Inserir todos os nomes no início do vetor */
    start_t = clock();
    while(1)
    {
        if(!fgets(str, MAX_LEN, file))
            break;  // EOF
        str[strlen(str) - 1] = '\0';

        if(vetor_insere(vec, str, 0) == -1)  // insere na primeira posição
        {
            printf("Erro a inserir no vetor\n");
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos inseridos no início do vetor\n", vec->tamanho);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    fseek(file, 0, SEEK_SET);

    /* Inserir todos os nomes no início da lista */
    start_t = clock();
    while(1)
    {
        if(!fgets(str, MAX_LEN, file))
            break;  // EOF
        str[strlen(str) - 1] = '\0';

        if(!lista_insere(lst, str, lista_elemento(lst, 0)))  // insere na primeira posição
        {
            printf("Erro a inserir na lista\n");
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos inseridos no início da lista\n", vec->tamanho);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    fseek(file, 0, SEEK_SET);

    /* Aceder a NPOS posições aleatórias do vetor */
    int pos[NPOS];
    for(int i=0; i<NPOS; i++)
        pos[i] = rand()%(vec->tamanho);

    start_t = clock();
    for(int i=0; i<NPOS; i++)
    {
        if(!vetor_elemento(vec, pos[i]))
        {
            printf("Erro a ler vetor\n");
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos lidos do vetor\n", NPOS);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    /* Aceder a NPOS posições aleatórias da lista */
    start_t = clock();
    for(int i=0; i<NPOS; i++)
    {
        if(!lista_elemento(lst, pos[i]))
        {
            printf("Erro a ler lista\n");
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos lidos da lista\n", NPOS);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    /* Remover todos os elementos do vetor a partir do início */
    int vec_tamanho = vec->tamanho;
    start_t = clock();
    for(int i=0; i<vec_tamanho; i++)
    {
        if(vetor_remove(vec, 0) == -1)
        {
            printf("Erro a remover elemento de vetor\n");
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos removidos do vetor\n", i);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    /* Remover todos os elementos do vetor a partir do início */
    int lst_tamanho = lst->tamanho;
    start_t = clock();
    for(i=0; i<lst_tamanho; i++)
    {
        if((!lista_remove(lst, lista_elemento(lst, 0))) && (lst->tamanho > 0))
        {
            printf("Erro a remover elemento de lista %d\n", i);
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos removidos da lista\n", i);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    /* Inserir todos os nomes no fim do vetor */
    start_t = clock();
    while(1)
    {
        if(!fgets(str, MAX_LEN, file))
            break;  // EOF
        str[strlen(str) - 1] = '\0';

        if(vetor_insere(vec, str, -1) == -1)  // insere na última posição
        {
            printf("Erro a inserir no vetor\n");
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos inseridos no fim do vetor\n", vec->tamanho);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    fseek(file, 0, SEEK_SET);

    /* Inserir todos os nomes no fim da lista */
    start_t = clock();
    while(1)
    {
        if(!fgets(str, MAX_LEN, file))
            break;  // EOF
        str[strlen(str) - 1] = '\0';

        if(!lista_insere(lst, str, NULL))  // insere na última posição
        {
            printf("Erro a inserir na lista\n");
            return -1;
        }
    }
    end_t = clock();
    printf("%d elementos inseridos no fim da lista\n", vec->tamanho);
    printf("tempo: %.3fs\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    printf("\n");

    fclose(file);
    vetor_apaga(vec);
    lista_apaga(lst);

    return 0;
}
