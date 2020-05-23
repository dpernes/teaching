#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabdispersao.h"

#define NOME_FICHEIRO "englishwords.txt"
#define TAMANHO_TAB_DISP 100000

elemento *ler_para_lista(const char *nomef, int *tamanho)
{
    if(!nomef)
        return NULL;

    FILE *f = fopen(nomef, "r");
    if(!f)
        return NULL;

    elemento *inicio = NULL, *anterior = NULL;
    *tamanho = 0;
    while(1)
    {
        char palavra[TAMANHO_CHAVE+1];
        if(!fgets(palavra, TAMANHO_CHAVE, f))
            break;
        palavra[strlen(palavra)-1] = '\0';

        objeto *obj = (objeto *)malloc(sizeof(objeto));
        strcpy(obj->chave, palavra);
        strcpy(obj->valor, palavra);

        elemento *elem = (elemento *)malloc(sizeof(elemento));
        elem->obj = obj;
        elem->proximo = NULL;

        if(*tamanho == 0)
            inicio = elem;
        else
            anterior->proximo = elem;

        (*tamanho)++;
        anterior = elem;
    }
    fclose(f);

    return inicio;
}

tabela_dispersao *ler_para_tabela(const char *nomef, int tamanho, hash_func *hfunc)
{
    if(!nomef || (tamanho < 1) || !hfunc)
        return NULL;

    FILE *f = fopen(nomef, "r");
    if(!f)
        return NULL;

    tabela_dispersao *td = tabela_nova(tamanho, hfunc);
    if(!td)
        return NULL;

    while(1)
    {
        char palavra[TAMANHO_CHAVE+1];
        if(!fgets(palavra, TAMANHO_CHAVE, f))
            break;
        palavra[strlen(palavra)-1] = '\0';

        tabela_adiciona(td, palavra, palavra);
    }
    fclose(f);

    return td;
}

const char *lista_pesquisa(elemento *inicio, const char *chave)
{
    if(!inicio || !chave)
        return NULL;

    elemento *elem = inicio;
    while(elem)
    {
        if(strcmp(elem->obj->chave, chave) == 0)
            return elem->obj->valor;

        elem = elem->proximo;
    }

    return NULL;
}


int main()
{
    clock_t inicio, fim;
    double tempo;

    printf("Ler para lista ligada - ");
    int tamanho_lista;
    inicio = clock();
    elemento *lst = ler_para_lista(NOME_FICHEIRO, &tamanho_lista);
    if(!lst)
    {
        printf("erro a ler para lista ligada\n");
        return -1;
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tamanho_lista);

    printf("Ler para tabela de dispersao (hash_djbm) - ");
    inicio = clock();
    tabela_dispersao *td_djbm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_djbm);
    if(!td_djbm)
    {
        printf("erro a ler para tabela de dispersao\n");
        return -1;
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tabela_numelementos(td_djbm));

    char chave[TAMANHO_CHAVE] = "perform";

    printf("Ler para tabela de dispersao (hash_krm) - ");
    inicio = clock();
    tabela_dispersao *td_krm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_krm);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tabela_numelementos(td_krm));

    printf("Pesquisa em lista ligada - ");
    inicio = clock();
    printf("chave: %s, valor: %s\n", chave, lista_pesquisa(lst, chave));
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n\n", tempo);

    printf("Pesquisa em tabela de dispersão (hash_djbm) - ");
    inicio = clock();
    printf("chave: %s, valor: %s\n", chave, tabela_valor(td_djbm, chave));
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n\n", tempo);

    return 0;
}