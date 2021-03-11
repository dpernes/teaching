#include <stdio.h>
#include <stdint.h>

// lengths of the headers
#define LEN_BITMAP_HDR 14
#define LEN_DIB_HDR 108

// addresses of LSBs of Bitmap header fields
#define ADDR_FILE_SIZE 0x02
#define ADDR_OFFSET 0x0A

// lengths of Bitmap header fields
#define LEN_FILE_SIZE 4
#define LEN_OFFSET 4

// addresses of LSBs of DIP header fields
#define ADDR_WIDTH 0x04
#define ADDR_HEIGHT 0x08
#define ADDR_COLOR_PLANES 0x0C
#define ADDR_BPP 0x0E
#define ADDR_IMG_SIZE 0x14

// lengths of DIP header fields
#define LEN_WIDTH 4
#define LEN_HEIGHT 4
#define LEN_COLOR_PLANES 2
#define LEN_BPP 2
#define LEN_IMG_SIZE 4

int main(int argc, char **argv){
    FILE *file;
    uint8_t bitmap_hdr[LEN_BITMAP_HDR], dib_hdr[LEN_DIB_HDR],
            file_size_a[LEN_FILE_SIZE], offset_a[LEN_OFFSET],
            width_a[LEN_WIDTH], height_a[LEN_HEIGHT],
            color_planes_a[LEN_COLOR_PLANES], bpp_a[LEN_BPP],
            img_size_a[LEN_IMG_SIZE];

    // open the file for reading
    file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Erro a abrir %s\n", argv[1]);
        return -1;
    }

    // read the Bitmap header
    int n_read = fread(bitmap_hdr, 1, LEN_BITMAP_HDR, file);
    if(n_read!=LEN_BITMAP_HDR)
    {
        printf("Bitmap: leitura inválida, %d/%d bytes\n",
               n_read, LEN_BITMAP_HDR);
        return -1;
    }

    // read the DIB header
    n_read = fread(dib_hdr, 1, LEN_DIB_HDR, file);
    if(n_read!=LEN_DIB_HDR)
    {
        printf("DIB: leitura inválida, %d/%d bytes\n",
               n_read, LEN_DIB_HDR);
        return -1;
    }

    // parse the Bitmap header
    for(int addr=0x00; addr<LEN_BITMAP_HDR; addr++)
    {
        switch(addr)
        {
            case ADDR_FILE_SIZE ... ADDR_FILE_SIZE + LEN_FILE_SIZE - 1:
                file_size_a[addr-ADDR_FILE_SIZE] = bitmap_hdr[addr];
                break;

            case ADDR_OFFSET ... ADDR_OFFSET + LEN_OFFSET - 1:
                offset_a[addr-ADDR_OFFSET] = bitmap_hdr[addr];
                break;
        }
    }

    // parse the DIB header
    for(int addr=0x00; addr<LEN_DIB_HDR; addr++)
    {
        switch(addr)
        {
            case ADDR_WIDTH ... ADDR_WIDTH + LEN_WIDTH - 1:
                width_a[addr-ADDR_WIDTH] = dib_hdr[addr];
                break;

            case ADDR_HEIGHT ... ADDR_HEIGHT + LEN_HEIGHT - 1:
                height_a[addr-ADDR_HEIGHT] = dib_hdr[addr];
                break;

            case ADDR_COLOR_PLANES ... ADDR_COLOR_PLANES + LEN_COLOR_PLANES - 1:
                color_planes_a[addr-ADDR_COLOR_PLANES] = dib_hdr[addr];
                break;

            case ADDR_BPP ... ADDR_BPP + LEN_BPP - 1:
                bpp_a[addr-ADDR_BPP] = dib_hdr[addr];
                break;

            case ADDR_IMG_SIZE ... ADDR_IMG_SIZE + LEN_IMG_SIZE - 1:
                img_size_a[addr-ADDR_IMG_SIZE] = dib_hdr[addr];
                break;

            default: break;
        }
    }

    // cast char (byte) arrays to int
    int file_size = (int) *(uint32_t *)file_size_a;
    int offset = (int) *(uint32_t *)offset_a;
    int width = (int) *(int32_t *)width_a;
    int height = (int) *(int32_t *)height_a;
    int color_planes = (int) *(uint16_t *)color_planes_a;
    int bpp = (int) *(uint16_t *)bpp_a;
    int img_size = (int) *(uint32_t *)img_size_a;

    // compute actual width and size (with zero padding)
    int width_4 = (width%4==0) ? width : width + 4 - width%4;
    int img_size_4 = height * width_4 * 3;

    // image array
    unsigned char image[height][width_4][3];

    // jump to the start of the image array
    fseek(file, offset, SEEK_SET);

    // read image data (starting on the last line)
    for(int i=height-1, pix, byte_cnt=0; i>-1; i--)
    {
        for(int j=0; j<width_4; j++)
        {
            for(int k=0; k<3; k++, byte_cnt++)
            {
                if((pix=getc(file))==EOF)
                {
                    printf("EOF antes do esperado, %d/%d bytes lidos\n",
                           byte_cnt, img_size_4);
                    return -1;
                }
                image[i][j][k] = (unsigned char)pix;
            }
        }
    }
    fclose(file);

    printf("Tamanho total do ficheiro BMP (bytes): %d\n", file_size);
    printf("Largura da imagem: %d\n", width);
    printf("Altura da imagem: %d\n", height);
    printf("Planos de cor: %d\n", color_planes);
    printf("Bits por pixel: %d\n", bpp);
    printf("Tamanho da imagem (bytes): %d\n", img_size);
    printf("Valor RGB no pixel (0,0): %d %d %d\n",
           (int)image[0][0][2], (int)image[0][0][1], (int)image[0][0][0]);
    printf("Valor RGB no pixel (532,0): %d %d %d\n",
           (int)image[532][0][2], (int)image[532][0][1], (int)image[532][0][0]);
    printf("Valor RGB no pixel (408,443): %d %d %d\n",
           (int)image[408][443][2], (int)image[408][443][1], (int)image[408][443][0]);

    return 0;
}
