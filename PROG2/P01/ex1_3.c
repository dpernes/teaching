#include <stdio.h>

int main(int argc, char **argv){
    FILE *file;
    int char_hist[3];

    // initialize the array char_hist with zeros
    for(int i=0; i<3; i++) char_hist[i] = 0;

    // open the file for reading
    file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }

    // read until EOF
    for(int c, c_prev=0x00; (c=getc(file))!=EOF;)
    {
        if(c_prev==0xC3)
        {
            if(c==0x83 || c==0xA3) char_hist[0]++;
            else if(c==0x95 || c==0xB5) char_hist[1]++;
            else if(c==0x87 || c==0xA7) char_hist[2]++;
        }
        c_prev = c;
    }
    fclose(file);

    printf("Letra A com til: %d\n", char_hist[0]);
    printf("Letra O com til: %d\n", char_hist[1]);
    printf("Letra C com cedilha: %d\n", char_hist[2]);

    return 0;
}
