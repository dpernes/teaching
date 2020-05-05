#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 255
#define MAX_URL_LEN 255
#define MAX_NAME_LEN 255
#define INI_TAG "<a href=\""

int main(int argc, char **argv){
    FILE *file;
    char url[MAX_URL_LEN+1], name[MAX_NAME_LEN+1], *pos, *pos_max;

    // open the file for reading
    file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }

    // read the file line by line
    for(char line[MAX_LINE_LEN+1]; fgets(line, MAX_LINE_LEN, file) != NULL;)
    {
        // look for INI_TAG in the line
        if((pos = strstr(line, INI_TAG)) != NULL)
        {
            pos_max = line + strlen(line);
            pos += strlen(INI_TAG);
            // check if pos is a valid pointer
            if(pos >= pos_max)
            {
                printf("Erro de sintaxe no ficheiro html (%s)\n", argv[1]);
                fclose(file);
                return -1;
            }
            // extract the URL
            for(int i = 0; i < MAX_URL_LEN; i++)
            {
                url[i] = *pos;
                url[i+1] = '\0';
                pos++;
                // check if pos is a valid pointer
                if(pos >= pos_max)
                {
                    printf("Erro de sintaxe no ficheiro html (%s)\n", argv[1]);
                    fclose(file);
                    return -1;
                }
                // the char " marks the end of the URL (not very robust, but we'll keep it simple)
                if(*pos == '\"')
                    break;
            }
            pos += 2;
            // check if pos is a valid pointer
            if(pos >= pos_max)
            {
                printf("Erro de sintaxe no ficheiro html (%s)\n", argv[1]);
                fclose(file);
                return -1;
            }
            // extract the name
            for(int i = 0; i < MAX_NAME_LEN; i++)
            {
                name[i] = *pos;
                name[i+1] = '\0';
                pos++;
                // check if pos is a valid pointer
                if(pos >= pos_max)
                {
                    printf("Erro de sintaxe no ficheiro html (%s)\n", argv[1]);
                    fclose(file);
                    return -1;
                }
                // the char < marks the end of the name (not very robust, but we'll keep it simple)
                if(*pos == '<')
                    break;
            }

            printf("%s - %s\n", name, url);
        }
    }
    fclose(file);

    return 0;
}
