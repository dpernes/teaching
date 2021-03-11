#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "vetor.h"

#define NSTRINGS 5
#define MAX_LEN 128

int main()
{
    char str[MAX_LEN];

    // initialize random number generator
    time_t t;
    srand((unsigned) time(&t));

    vetor *v1=vetor_novo();
    // ask the user for N_STRINGS strings
    for(int i=0; i<NSTRINGS; i++)
    {
        printf("Introduza %dª string: ", i+1);
        fgets(str, MAX_LEN, stdin);
        str[strlen(str) - 1] = '\0';
        if(vetor_insere(v1, str, -1) == -1)
        {
            printf("Erro a inserir %s no vetor\n", str);
            return -1;
        }
    }

    // print the vector
    printf("Vetor: [ ");
    for(int i=0; i<vetor_tamanho(v1); i++)
        printf("\"%s\", ", vetor_elemento(v1, i));
    printf("]\n");


    vetor *v2=vetor_novo();
    // ask the user for NSTRINGS strings
    for(int i=0; i<NSTRINGS; i++)
    {
        printf("Introduza %dª string: ", i+1);
        fgets(str, MAX_LEN, stdin);
        str[strlen(str) - 1] = '\0';
        if(vetor_insere(v2, str, -1) == -1)
        {
            printf("Erro a inserir %s no vetor\n", str);
            return -1;
        }
    }

    // print the vector
    printf("Vetor: [ ");
    for(int i=0; i<vetor_tamanho(v2); i++)
        printf("\"%s\", ", vetor_elemento(v2, i));
    printf("]\n");

    vetor *v_cat;
    if(!(v_cat=vetor_concatena(v1, v2)))
    {
        printf("Erro a concatenar o vetor\n");
        vetor_apaga(v1);
        vetor_apaga(v2);
        return -1;
    }

    // print the vector
    printf("Vetor concatenado: [ ");
    for(int i=0; i<vetor_tamanho(v_cat); i++)
        printf("\"%s\", ", vetor_elemento(v_cat, i));
    printf("]\n");
    vetor_apaga(v1);
    vetor_apaga(v2);

    // reverse the vector
    if(vetor_inverte(v_cat)==-1)
    {
        printf("Erro a inverter o vetor\n");
        vetor_apaga(v_cat);
        return -1;
    }

    // print the vector
    printf("Vetor invertido: [ ");
    for(int i=0; i<vetor_tamanho(v_cat); i++)
        printf("\"%s\", ", vetor_elemento(v_cat, i));
    printf("]\n");

    // shuffle the vector
    vetor *v_shuf;
    if(!(v_shuf = vetor_baralha(v_cat)))
    {
        printf("Erro a baralhar o vetor\n");
        vetor_apaga(v_cat);
        return -1;
    }

    // print the vector
    printf("Vetor baralhado: [ ");
    for(int i=0; i<vetor_tamanho(v_shuf); i++)
        printf("\"%s\", ", vetor_elemento(v_shuf, i));
    printf("]\n");

    vetor_apaga(v_cat);
    vetor_apaga(v_shuf);
}
