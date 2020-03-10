#include <stdio.h>
#include <string.h>
#include "lista.h"

#define MAX_LEN 128


int main(int argc, char **argv)
{
    if(argc < 2) return -1;
    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }

    lista *lst = lista_nova();
    char str[MAX_LEN];
    while(1)
    {
        if(!fgets(str, MAX_LEN, file)) break;  // EOF
        str[strlen(str) - 1] = '\0';

        if(!lista_insere(lst, str, NULL))  // insere na última posição
        {
            printf("Erro a inserir na lista\n");
            return -1;
        }
    }
    fclose(file);

    printf("Foram carregados %d jogos:\n", lst->tamanho);
    lista_imprime(lst, stdout);
    printf("\n");
    /* FIM DO EX. 1. a) */

    //DEBUG
    lista_remove(lst, lista_elemento(lst, 0));
    lista_imprime(lst, stdout);
    //DEBUG

    lista *lst_ps2 = lista_pesquisa_substring(lst, "PS2");
    printf("Foram encontrados %d jogos da PS2:\n", lst_ps2->tamanho);
    lista_imprime(lst_ps2, stdout);
    printf("\n");
    /* FIM DO EX. 1. b) */

    lista_remove_substring(lst, "PS2");
    printf("Apos remoção de jogos PS2 a lista tem %d jogos.\n", lst->tamanho);
    lista_imprime(lst, stdout);
    printf("\n");

    if(argc < 3) return 0;
    file = fopen(argv[2], "w");
    if(!file)
    {
        printf("Erro a abrir %s para escrita\n", argv[2]);
        return -1;
    }
    lista_imprime(lst, file);
    fclose(file);

    /* FIM DO EX. 1. c) */

    if(argc < 4) return 0;
    file = fopen(argv[3], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[3]);
        return -1;
    }

    lista *lst_oldies = lista_nova();
    while(1)
    {
        if(!fgets(str, MAX_LEN, file))
            break;  // EOF
        str[strlen(str) - 1] = '\0';

        if(!lista_insere(lst_oldies, str, NULL))  // insere na última posição
        {
            printf("Erro a inserir na lista\n");
            return -1;
        }
    }
    fclose(file);

    printf("Foram carregados %d jogos antigos:\n", lst_oldies->tamanho);
    lista_imprime(lst_oldies, stdout);
    printf("\n");

    lista_concatena(lst, lst_oldies);
    printf("Após concatenação, a lista final contém %d jogos:\n", lst->tamanho);
    lista_imprime(lst, stdout);
    printf("\n");
    /* FIM DO EX. 1. d) */

    if(lista_ordena(lst) == -1)
    {
        printf("Erro a ordenar lista\n");
        return -1;
    }
    printf("Lista ordenada:\n");
    lista_imprime(lst, stdout);
    printf("\n");
    /* FIM DO EX. 1. e) */

    l_elemento *l_elem = lista_pesquisa(lst, "Duke Nukem (PS3)", LISTA_INICIO);
    if(!l_elem)
    {
        printf("Elemento não encontrado\n");
        return -1;
    }

    int pos;
    for(pos=0; pos<lst->tamanho; pos++)
        if(lista_elemento(lst, pos) == l_elem) break;
    printf("O jogo Duke Nukem (PS3) encontra-se na posição %d.\n", pos);
    printf("\n");
    /* FIM DO EX. 1. f) */

    char inserir[MAX_LEN] = "Pinball (PS2)";
    pos = lista_insere_ordenada(lst, inserir);
    printf("O jogo %s foi inserido na posição %d.\n", inserir, pos);
    lista_imprime(lst, stdout);
    printf("\n");
    /* FIM DO EX. 1. g) */

    lista_apaga(lst);
    lista_apaga(lst_oldies);
    /* FIM DO EX. 1. h) */

    return 0;
}