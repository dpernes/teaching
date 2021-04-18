#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
vetor* contar_remetente_destinatario(vetor *vrem, vetor *vdest)
{
    if(!vrem || !vdest)
        return NULL;

    vetor *pessoas = vetor_novo();
    if(!pessoas)
        return NULL;

    int n_pessoas_max = vrem->tamanho + vdest->tamanho;  // máximo número possível de pessoas distintas
    int n_cartas[n_pessoas_max];  // contador do número de cartas de cada pessoa

    // percorre vrem contando as cartas de cada pessoa
    for(int i = 0; i < vrem->tamanho; i++)
    {
        const char *rem = vetor_elemento(vrem, i);
        int pos = vetor_pesquisa(pessoas, rem);
        if(pos == -1)  // se a pessoa ainda não existe no vetor pessoas, insere-a (no fim do vetor) e conta a sua primeira carta
        {
            if(vetor_insere(pessoas, rem, -1) == -1)
            {
                vetor_apaga(pessoas);
                return NULL;
            }
            n_cartas[pessoas->tamanho-1] = 1;
        }
        else  // se já existe, incrementa o número de cartas na posição respetiva
            n_cartas[pos]++;
    }

    // percorre vdest contando as cartas de cada pessoa
    for(int i = 0; i < vdest->tamanho; i++)
    {
        const char *dest = vetor_elemento(vdest, i);
        int pos = vetor_pesquisa(pessoas, dest);
        if(pos == -1)  // se a pessoa ainda não existe no vetor pessoas, insere-a (no fim do vetor) e conta a sua primeira carta
        {
            if(vetor_insere(pessoas, dest, -1) == -1)
            {
                vetor_apaga(pessoas);
                return NULL;
            }
            n_cartas[pessoas->tamanho-1] = 1;
        }
        else  // se já existe, incrementa o número de cartas na posição respetiva
            n_cartas[pos]++;
    }

    // imprime a informação pedida
    for(int i = 0; i < pessoas->tamanho; i++)
    {
        const char *nome = vetor_elemento(pessoas, i);
        printf("%s : %d cartas\n", nome, n_cartas[i]);
    }

    return pessoas;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256
void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest);

int main()
{
    FILE *fin;
    vetor* vrem;
    vetor* vdest;
    vetor *vcp_dest;
    vrem=NULL; vdest=NULL; vcp_dest=NULL;

    fin = fopen("correspondencia.txt", "r");
    if(fin == NULL)
    {
        printf("Erro ao abrir ficheiro.\n");
        return 1;
    }

    vrem = vetor_novo();
    vdest = vetor_novo();
    vcp_dest = vetor_novo();
    lerParaVetores(fin, vrem, vdest, vcp_dest);

    fclose(fin);

    vetor *cp = contar_remetente_destinatario(vrem, vdest);

    if (cp == NULL)
        printf("\nFuncao retornou erro.\n");
    else {
        printf("\nNumero de pessoas distintas: %d\n", vetor_tamanho(cp));
    }

    vetor_apaga(cp);

    return 0;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/
void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
    char buffer[256], *nlptr;

    if (ficheiro == NULL)
        return;

    while(fgets(buffer, 255, ficheiro) != NULL)
    {
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';
        vetor_insere(vrem, buffer, -1);

        fgets(buffer, 255, ficheiro);
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';
        vetor_insere(vdest, buffer, -1);

        fgets(buffer, 255, ficheiro);
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';
        vetor_insere(vcp_dest, buffer, -1);
    }
}
