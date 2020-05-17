#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabdispersao.h"

#define NOME_FICHEIRO "englishwords.txt"
#define TAMANHO_TAB_DISP 100000

elemento *ler_para_lista(const char *nomef, int *tamanho_lista)
{
    FILE *f = fopen(nomef, "r");
    if(!f)
        return NULL;

    elemento *inicio = malloc(sizeof(elemento));
    inicio->obj = NULL;
    inicio->proximo = NULL;

    elemento *anterior = inicio;
    int tamanho = 0;
    while(1)
    {
        char palavra[TAMANHO_CHAVE+1];
        if(!fgets(palavra, TAMANHO_CHAVE, f))
            break;
        palavra[strlen(palavra)-1] = '\0';

        objeto *obj = (objeto *)malloc(sizeof(objeto));
        strcpy(obj->chave, palavra);
        strcpy(obj->valor, palavra);

        elemento *elem = malloc(sizeof(elemento));
        elem->obj = obj;
        elem->proximo = NULL;

        anterior->proximo = elem;
        anterior = elem;
        tamanho++;
    }
    fclose(f);

    *tamanho_lista = tamanho;
    return inicio;
}

tabela_dispersao *ler_para_tabela(const char *nomef, int tamanho, hash_func *hfunc)
{
    FILE *f = fopen(nomef, "r");
    if(!f)
        return NULL;

    tabela_dispersao *td = tabela_nova(tamanho, hfunc);

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

elemento *lista_pesquisa(elemento *inicio, const char *str)
{
    if(!inicio || !str)
        return NULL;

    elemento *elem = inicio;
    while(elem)
    {
        if(!strcmp(elem->obj->valor, str))
            return elem;

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
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tamanho_lista);

    printf("Ler para tabela de dispersao (hash_djbm) - ");
    inicio = clock();
    tabela_dispersao *td_djbm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_djbm);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tabela_numelementos(td_djbm));

    char chave[TAMANHO_CHAVE] = "perform";
    printf("chave: %s, valor: %s\n\n", chave, tabela_valor(td_djbm, chave));

    printf("Ler para tabela de dispersao (hash_krm) - ");
    inicio = clock();
    tabela_dispersao *td_krm = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_krm);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    printf("#elementos: %d\n\n", tabela_numelementos(td_krm));

}