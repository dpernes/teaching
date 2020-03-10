#include <stdio.h>

const int OFFSET = (int)'a' - (int)'A',
          N_LETTERS = (int)'z' - (int)'a' + 1;

int main(int argc, char **argv){
    FILE *file;
    int char_hist[N_LETTERS], char_cnt=0;

    // initialize the array char_hist with zeros
    for(int i=0; i<N_LETTERS; i++) char_hist[i] = 0;

    // open the file for reading
    file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }

    // read until EOF
    for(int c; (c=getc(file))!=EOF;)
    {
        // convert "special A" to a
        if (c>=0xC0 && c<=0xC3) c = (int)'a';
        // convert "special a" to a
        else if (c>=0xE0 && c<=0xE3) c = (int)'a';
        // convert "special O" to o
        else if (c>=0xD3 && c<=0xD5) c = (int)'o';
        // convert "special o" to o
        else if (c>=0xF3 && c<=0xF5) c = (int)'o';
        // convert "special i" to i
        else if (c==0xCD || c==0xED) c = (int)'i';
        // convert "special e" to e
        else if (c==0xC9 || c==0xCA) c = (int)'e';
        // convert "special E" to e
        else if (c==0xE9 || c==0xEA) c = (int)'e';
        // convert "special u" to u
        else if (c==0xDA || c==0xFA) c = (int)'u';
        // convert "special c" to c
        else if (c==0xC7 || c==0xE7) c = (int)'c';
        // convert upper case to lower case
        else if(c>=(int)'A' && c<=(int)'Z') c += OFFSET;

        // if it's a letter, count this occurency
        if(c>=(int)'a' && c<=(int)'z'){
            char_cnt += 1;
            char_hist[c - (int)'a'] += 1;
        }
    }
    fclose(file);

    printf("Número de letras no ficheiro: %d\n", char_cnt);
    for(int i=0; i<N_LETTERS; i++)
    {
        printf("Letra %c: %.2f%%\n",
               (char)(i + (int)'a'), (100.*char_hist[i])/(char_cnt));
    }

    return 0;
}
