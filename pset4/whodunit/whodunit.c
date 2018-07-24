#include<stdio.h>
#include <stdlib.h>
#include<cs50.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    //Test du nb d'arguments
    if (argc != 3)
    {
        fprintf(stderr, "Incorrect number of arguments :\n (2 required;\t%d given)\nFormat : ./whodunit INPUT OUTPUT\n", argc - 1);
        return 1;
    }

    // Ouvre les deux fichiers avec l'opération ("read/write") adéquate
    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
    {
        fprintf(stderr, "Input (%s) cannot be opened for reading\n", argv[1]);
        return 2;
    }

    FILE *out = fopen(argv[2], "w");
    if (in == NULL)
    {
        fprintf(stderr, "Output (%s) cannot be opened for writing\n", argv[2]);
        return 3;
    }

    //Vérifie que in est bien une image BMP 4.0 24-bit
    // Simple vérification des "magic numbers" (0x42 et 0x4d)

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, in);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, in);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42) //|| bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(out);
        fclose(in);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, out);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, out);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, in);

            //retire tout le rouge de l'image
            if (triple.rgbtRed == 0xff)
            {
                triple.rgbtRed = 0x00;
            }
            //transforme les bleus/vert en blancs
            if (triple.rgbtGreen == 0xff && triple.rgbtRed == 0x00)
            {
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtRed = 0xff;
            }
            // accentue la couleur blanc bleutée
            if (triple.rgbtRed == 0xe0)
            {
                triple.rgbtBlue = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtRed = 0xff;
            }
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, out);
        }

        // skip over padding, if any
        fseek(in, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, out);
        }
    }

    // close infile
    fclose(in);

    // close outfile
    fclose(out);

    // success
    return 0;
}

