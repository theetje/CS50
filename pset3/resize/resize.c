/**
 * resize.c
 *
 * Thomas de lange
 * Student nummer: 11067632
 *
 * Het programma neemt een bestand en veranderd de grote er van met scale
 * en in is gegeven als input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and scale
    int scale = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if( isdigit(scale) != 0)
    {
        fprintf(stderr, "Usage: n should be a number.\n");
        return 1; /* Kijk of je hier een andere return value moet gebruiken om zo te kloppen met de andere*/
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    BITMAPFILEHEADER new_bf;
	BITMAPINFOHEADER new_bi;
	new_bf = bf;
	new_bi = bi;
	new_bi.biWidth = bi.biWidth * scale;
	new_bi.biHeight = bi.biHeight * scale;

    // determine padding for scanlines
    int new_padding =  (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// recalculate the outputfile format
    new_bf.bfSize = new_bi.biWidth * abs(new_bi.biHeight) * 3 + abs(new_bi.biHeight) * new_padding + 54;
    new_bi.biSizeImage = ((((new_bi.biWidth * new_bi.biBitCount) + 31) & ~31) / 8) * abs(new_bi.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    printf("new_padding: %i\n", new_padding);
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Doe het geheel n keer om zo uit te komen op de correcte hoogte
        for (int n = 0; n < scale; n++)
        {
            // iterate over pixsels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                /* Je kan hieronder manipulaties uit voeren in de breete deze moet dus n keer gebeuren */
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile scale times
                for (int l = 0 ; l < scale; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // skip over padding if any
            // is de padding van de input file die je niet nog een keer moet meenemen
            fseek(inptr, padding, SEEK_CUR);

            // add padding keer 3
            for (int k = 0; k < (new_padding); k++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, -((bi.biWidth * 3) + padding), SEEK_CUR);
        }

        fseek(inptr, ((bi.biWidth * 3) + padding), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
