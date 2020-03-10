#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSTRINGS 2

int main()
{
    char **v;
    char str[80];
    int i, pos;
    v = malloc(NSTRINGS * sizeof(char*));

    // initialize all positions in v with NULL
    for(i = 0; i < NSTRINGS; i++) v[i] = NULL;

    while(1)
    {
        for(i = 0; i < NSTRINGS; i++)
    	{
    		printf("[%d] ", i+1);
    		if(v[i] == NULL)
    			printf("(vazio)\n");
    		else
            	printf("%s\n", v[i]);
    	}

    	do
    	{
            printf("Posicao para nova string (1 a %d): ", NSTRINGS);
            scanf("%d", &pos);
            getchar(); /* elimina \n */
    	}
    	while(pos < 0 || pos > NSTRINGS);

        if (pos == 0)
            break;

        printf("Nova String: ");
        fgets(str, 80, stdin);
        str[strlen(str) - 1] = '\0';

        // allocate strlen(str)+1 bytes
        printf("realloc\n");
        v[pos - 1] = realloc(v[pos - 1], strlen(str)+1);
    	strcpy(v[pos - 1], str);
    }

    // free allocated memory
    for(i = 0; i < NSTRINGS; i++)
    {
        //free(v[i]);
        v[i] = NULL;
    }
    free(v);
    v = NULL;

    return 0;
}
