#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
int verifica_expressao(const char *expr);  // função auxiliar

int avalia_expressoes(FILE *ficheiro, vetor *expressoes)
{
    if(!ficheiro || !expressoes)
        return 0;

    for(int i = 0; i < expressoes->tamanho; i++)
    {
        const char *expr = vetor_elemento(expressoes, i);
        fprintf(ficheiro, "%s ", expr);
        if(verifica_expressao(expr) == 1)
            fprintf(ficheiro, "-> OK\n");
        else
            fprintf(ficheiro, "-> NOK\n");
    }

    return 1;
}

int verifica_expressao(const char *expr)
{
    if(!expr)
        return -1;

    pilha *p = pilha_nova();
    if(!p)
        return -1;

    int tamanho = strlen(expr);
    for(int i = 0; i < tamanho; i++)
    {
        if(expr[i] == '(')  // se encontrar parêntesis a abrir, adiciona elemento à pilha
            pilha_push(p, "0");

        else if(expr[i] == ')')  // se encontrar parêntesis a fechar, remove elemento da pilha (se for possível)
        {
            if(pilha_vazia(p))  // se a pilha estive vazia, então não houve parêntesis a abrir antes, logo é erro
                return 0;

            pilha_pop(p);
        }
    }

    // no final, o número de parêntesis a abrir e a fechar deve ser igual, logo a pilha tem de estar vazia
    if(!pilha_vazia(p))
        return 0;

    return 1;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

vetor* lerFicheiro(FILE *ficheiro)
{
    char buffer[BUFFER], *charptr;
    vetor *v;
    v = vetor_novo();
    while(fgets(buffer, BUFFER, ficheiro) != NULL)
    {
        charptr = strchr(buffer, '\n');
        if(charptr) *charptr = '\0';
        charptr = strchr(buffer, '\t');
        if(charptr) *charptr = '\0';
        if(strcmp(charptr+1, "infixa") == 0)
            vetor_insere(v, buffer, v->tamanho);
    }
    return v;
}

int main()
{
    FILE *fin, *fout;
    vetor *expressoes=NULL;

    fin = fopen("expressoes.txt", "r");
    if(fin == NULL)
    {
        printf("Erro ao abrir ficheiro.\n");
        return 1;
    }

    fout = fopen("avaliacao.txt", "w");
    if(fout == NULL)
    {
        printf("Erro ao abrir ficheiro.\n");
        return 1;
    }

    expressoes = lerFicheiro(fin);
    if(!expressoes)
    {
        printf("Erro ao ler ficheiro de expressoes.\n");
        return 1;
    }

    if(avalia_expressoes(fout, expressoes) == 1)
        printf("Funcao terminou corretamente - verificar ficheiro avaliacao.txt\n");
    else
        printf("Funcao retornou erro.\n");

    fclose(fin);
    fclose(fout);

    return 0;
}
