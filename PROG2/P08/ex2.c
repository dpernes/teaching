#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabdispersao.h"

#define NOME_FICHEIRO "passwords.txt"
#define TAMANHO_TAB_DISP 10


tabela_dispersao *ler_para_tabela(const char *nomef, int tamanho, hash_func *hfunc)
{
    if(!nomef || (tamanho < 1) || !hfunc)
        return NULL;

    FILE *f = fopen(nomef, "r");
    if(!f)
        return NULL;

    tabela_dispersao *td = tabela_nova(tamanho, hfunc);
    while(1)
    {
        char linha[TAMANHO_CHAVE+TAMANHO_VALOR+3];
        char username[TAMANHO_CHAVE];
        char password[TAMANHO_VALOR];
        if(!fgets(linha, TAMANHO_CHAVE+TAMANHO_VALOR+2, f))
            break;
        linha[strlen(linha)-1] = '\0';

        char *tok = strtok(linha, " ");
        strcpy(username, tok);
        tok = strtok(NULL, " ");
        strcpy(password, tok);

        tabela_adiciona(td, username, password);
    }
    fclose(f);

    return td;
}

int main()
{

    tabela_dispersao *td = ler_para_tabela(NOME_FICHEIRO, TAMANHO_TAB_DISP, hash_djbm);
    if(!td)
    {
        printf("Error reading %s to hash table\n", NOME_FICHEIRO);
        return -1;
    }

    char username[TAMANHO_CHAVE+1], password[TAMANHO_VALOR+1];
    printf("Login: ");
    fgets(username, TAMANHO_CHAVE, stdin);
    username[strlen(username)-1] = '\0';

    printf("Password: ");
    fgets(password, TAMANHO_VALOR, stdin);
    password[strlen(password)-1] = '\0';

    if(strcmp(password, tabela_valor(td, username)) == 0)
        printf("Authentication succeeded\n");
    else
        printf("Authentication failed\n");

    return 0;
}