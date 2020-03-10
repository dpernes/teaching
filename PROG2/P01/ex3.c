#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define MAX_URL_LEN 256
#define MAX_NAME_LEN 256
#define INI_TAG "<a href=\""

int main(int argc, char **argv){
    FILE *file;
    char url[MAX_URL_LEN], name[MAX_NAME_LEN], *pos;

    // open the file for reading
    file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }

    // read the file line by line
    for(char line[MAX_LINE_LEN]; fgets(line, MAX_LINE_LEN, file)!=NULL;)
    {
        // look for INI_TAG in the line
        if((pos=strstr(line, INI_TAG))!=NULL)
        {
            pos += strlen(INI_TAG);
            // extract the URL
            for(int i=0; 1; i++)
            {
                url[i] = *pos;
                url[i+1] = '\0';
                pos++;
                if(*pos=='\"') break;
            }
            pos += 2;
            // extract the name
            for(int i=0; 1; i++)
            {
                name[i] = *pos;
                name[i+1] = '\0';
                pos++;
                if(*pos=='<') break;
            }

            printf("%s - %s\n", name, url);
        }
    }
    fclose(file);

    return 0;
}
