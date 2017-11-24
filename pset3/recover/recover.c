/**
 * recover.c
 *
 * Thomas de lange
 * Student nummer: 11067632
 *
 * Neemt een bestand als 2e argument en zoekt naar JPEG.
 * Als ze er zijn maakt het er een bestand van.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Grote van het blok om in te lezen wordt hier bepaald
#define MBLOCK 512

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover [file to recover]\n");
        return 1;
    }

    // remember filenames and scale
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Maak hieronder de buffer counter aan en een schakel fileopen.
    unsigned char buffer[MBLOCK];
    int file_counter = -1;
    int fileopen = 0;
    char filename[8];
    FILE *img;

    while (fread(buffer, MBLOCK, 1, inptr) == 1)
    {
        // is het MBLOCK de start van een nieuwe JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // sluit het bestand hier als die al geopend is.
            if (fileopen == 1)
            {
                fclose(img);
            }
            else
            {
                fileopen = 1;
            }

            file_counter++;
            // maak hier de bestanden met naar naar counter
            sprintf(filename, "%03i.jpg", file_counter);
            img = fopen(filename, "w");
        }

        // Schijf het bestand hier weg.
        if (fileopen == 1)
        {
            fwrite(&buffer, MBLOCK, 1, img);
        }
    }
    return 0;
}

