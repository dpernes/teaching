#include <stdio.h>
#include <string.h>
#include "vetor.h"

#define NSTRINGS 5
#define MAX_LEN 128

int main()
{
    vetor *v=vetor_novo();
    char str[MAX_LEN];

    // ask the user for NSTRINGS strings
    for(int i=0; i<NSTRINGS; i++)
    {
        printf("Introduza %dª string: ", i+1);
        fgets(str, MAX_LEN, stdin);
        str[strlen(str) - 1] = '\0';
        if(vetor_insere(v, str, -1) == -1)
        {
            printf("Erro a inserir %s no vetor\n", str);
            return -1;
        }
    }

    // print the vector
    printf("Vetor: [ ");
    for(int i=0; i<vetor_tamanho(v); i++)
        printf("\"%s\", ", vetor_elemento(v, i));
    printf("]\n");

    // ask the user for a string to remove
    printf("Introduza string a apagar: ");
    fgets(str, MAX_LEN, stdin);
    str[strlen(str) - 1] = '\0';
    int pos = vetor_pesquisa(v, str);
    if(pos!=-1) vetor_remove(v, pos);

    // print the vector
    printf("Vetor: [ ");
    for(int i=0; i<vetor_tamanho(v); i++)
        printf("\"%s\", ", vetor_elemento(v, i));
    printf("]\n");

    // sort the vector
    if(vetor_ordena(v)==-1)
    {
        printf("Erro a ordenar o vetor\n");
        return -1;
    }

    // print the vector
    printf("Vetor ordenado: [ ");
    for(int i=0; i<vetor_tamanho(v); i++)
        printf("\"%s\", ", vetor_elemento(v, i));
    printf("]\n");
}
