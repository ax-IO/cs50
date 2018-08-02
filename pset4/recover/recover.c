#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>
#include<string.h>
#include<cs50.h>
//#include<math.h>

// Define Byte and bit Type
typedef uint8_t BYTE;
// FAT Block Size
#define BLOCK 512

//Fonction comparant les n bits suivant d'un
//File pointeur ouvert en lecture
//renvoie 0 en cas de succès
//renvoie 1 si les bits sont différents
size_t next_bits_compare(BYTE *chain, int n_bytes, FILE *fp)
{
    BYTE hexa;
    for (int i = 0; i < n_bytes; i++)
    {
        fread(&hexa, sizeof(BYTE), 1, fp);
        // if (i == n_bytes -1)
        // {
        //     hexa = hexa & ~0xf;
        //     //fprintf(stderr, "hexa =%#x\n~0xf = %#x\n", hexa, ~0xf);
        // }

        if (hexa != chain[i])
        {
            //fprintf(stderr, "hexa = %#x \nchain[%d] = %#x\nhexa & chain[i] = %#x\n~0 = %#x\n", hexa, i, chain[i], hexa & chain[i], ~0);
            fseek(fp, -(i + 1), SEEK_CUR);
            return 43;
        }
    }
    fseek(fp, -n_bytes, SEEK_CUR);
    return 0;
}

int main(int argc, char *argv[])
{
    //Test du nb d'arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover [IMAGE]\n");
        return 1;
    }


    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
    BYTE SIGNATURE[4] = {0xff, 0xd8, 0xff, 0xe0};

    //
    //char* fichier[7];
    char fichier[50][8];
    for (int i = 0; i < 50; i++)
    {
        sprintf(fichier[i], "%03d.jpg", i);
    }
    //
    int e = 0;
    fseek(inptr, 1024, SEEK_SET);

    e = next_bits_compare(SIGNATURE, 4, inptr);
    // Définit le commencement du 1er JPEG rencontré
    if (e == 0) //1111111111011000111111111110
    {
        for (int i = 0; i < 50; i++)
        {
            fprintf(stderr, "Signature block numero %d trouve !!\n", i + 1);
            FILE *image = fopen(fichier[i], "w");
            BYTE *buffer = malloc(BLOCK);
            do
            {
                int r = fread(buffer, 1, 512, inptr);
                if (r != 512)
                {
                    return 0;
                }
                fwrite(buffer, 1, 512, image);
            }
            while (next_bits_compare(SIGNATURE, 4, inptr) > 0);

            free(buffer);
            fclose(image);
        }
    }


    // free(fichier);
    // close infile
    fclose(inptr);

    // success
    return 0;
}