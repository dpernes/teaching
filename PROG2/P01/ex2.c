#include <stdio.h>
#include <string.h>

#define ST_HEADER 0
#define ST_TITLE 1
#define ST_ARTIST 2
#define ST_ALBUM 3
#define ST_YEAR 4
#define ST_COMMENT 5
#define ST_BYTE_ZERO 6
#define ST_NUMBER 7
#define ST_GENRE 8

#define LEN_HEADER 3
#define LEN_TITLE 30
#define LEN_ARTIST 30
#define LEN_ALBUM 30
#define LEN_YEAR 4
#define LEN_COMMENT 30
#define POS_BYTE_ZERO 28
#define POS_NUMBER 29

const char GENRE_LIST[126][32] =
{
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
};


int main(int argc, char **argv){
    FILE *file;
    char header[LEN_HEADER+1], title[LEN_TITLE+1], artist[LEN_ARTIST+1],
         album[LEN_ALBUM+1], year[LEN_YEAR+1],comment[LEN_COMMENT+1], genre[32];

    unsigned char byte_zero, number, genre_byte;

    // open the file for reading
    file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }

    // jump to the last 128 bytes of the file
    fseek(file, -128, SEEK_END);

    // read metadata
    int state = ST_HEADER, n_read;
    switch(state)
    {
        case ST_HEADER:
            n_read = fread(header, 1, LEN_HEADER, file);
            if(n_read!=LEN_HEADER)
            {
                printf("%d: leitura inválida, %d/%d bytes lidos\n",
                        state, n_read, LEN_HEADER);
                return -1;
            }
            header[LEN_HEADER] = '\0';
            if(strcmp(header, "TAG"))
            {
                printf("Cabeçalho inválido, %s\n", header);
                return -1;
            }
            else state = ST_TITLE;

        case ST_TITLE:
            n_read = fread(title, 1, LEN_TITLE, file);
            if(n_read!=LEN_TITLE)
            {
                printf("%d: leitura inválida, %d/%d bytes lidos\n",
                        state, n_read, LEN_TITLE);
                return -1;
            }
            title[LEN_TITLE] = '\0';
            state = ST_ARTIST;

        case ST_ARTIST:
            n_read = fread(artist, 1, LEN_ARTIST, file);
            if(n_read!=LEN_ARTIST)
            {
                printf("%d: leitura inválida, %d/%d bytes lidos\n",
                        state, n_read, LEN_ARTIST);
                return -1;
            }
            artist[LEN_ARTIST] = '\0';
            state = ST_ALBUM;

        case ST_ALBUM:
            n_read = fread(album, 1, LEN_ALBUM, file);
            if(n_read!=LEN_ALBUM)
            {
                printf("%d: leitura inválida, %d/%d bytes lidos\n",
                        state, n_read, LEN_ALBUM);
                return -1;
            }
            album[LEN_ALBUM] = '\0';
            state = ST_YEAR;

        case ST_YEAR:
           n_read = fread(year, 1, LEN_YEAR, file);
            if(n_read!=LEN_YEAR)
            {
                printf("%d: leitura inválida, %d/%d bytes lidos\n",
                        state, n_read, LEN_YEAR);
                return -1;
            }
            year[LEN_YEAR] = '\0';
            state = ST_COMMENT;

        case ST_COMMENT:
            n_read = fread(comment, 1, LEN_COMMENT, file);
            if(n_read!=LEN_COMMENT)
            {
                printf("%d: leitura inválida, %d/%d bytes lidos\n",
                        state, n_read, LEN_COMMENT);
                return -1;
            }
            state = ST_BYTE_ZERO;

        case ST_BYTE_ZERO:
            byte_zero = comment[POS_BYTE_ZERO];
            if(!(int)byte_zero)
            {
                comment[POS_BYTE_ZERO] = '\0';
                state = ST_NUMBER;
            }
            else
            {
                comment[LEN_COMMENT] = '\0';
                state = ST_GENRE;
            }

        case ST_NUMBER:
            number = comment[POS_NUMBER];
            state = ST_GENRE;

        case ST_GENRE:
            n_read = fread(&genre_byte, 1, 1, file);
            if(n_read!=1)
            {
                printf("%d: leitura inválida, %d/%d bytes lidos\n",
                        state, n_read, 1);
                return -1;
            }
            strcpy(genre, GENRE_LIST[(int)genre_byte]);
            break;

        default:
            printf("Default case reached\n");
            return -1;
    }
    fclose(file);

    printf("Título: %s\n", title);
    printf("Artista: %s\n", artist);
    printf("Álbum: %s\n", album);
    printf("Ano: %s\n", year);
    printf("Comentário: %s\n", comment);
    if(!(int)byte_zero)
        printf("Número: %d\n", (int)number);
    printf("Género: %s\n", genre);

    return 0;
}
