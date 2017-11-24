/****************************************************************************
 * mario.c
 * Thomas de Lange
 *
 * Een programma dat een getal vraagt tussen de 0 en 23 en er vervolgens een
 * peramide an maakt.
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Make the variables
    int height;
    int width_h = 0;

    // Kijk of die wel goter is dan 0 en kleiner dan 24.
	do
	{
		printf("Height:");
		height = get_int();
        if (height == 0)
        {
            return 0;
        }
	} while (height < 1 || height > 23);

    // initiate whith of the spaces
	int width_s = height;


    // for each number in height loop:
    for (int i = 0; i < height; i++)
    {
        width_h++;
        width_s--;

        // Maak de spaties
        for (int j = 0; j < width_s; j++)
        {
            printf(" ");
        }

        // Maak de hashes links.
        for (int k = 0; k < width_h; k++)
        {
            printf("#");
        }

        // Maak de spatie in het midden.
        printf("  ");

        // Maak de hashes links
        for (int m = 0; m < width_h; m++)
        {
            printf("#");
        }

        printf("\n");
    }
}