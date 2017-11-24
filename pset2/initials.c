/****************************************************************************
* initials.c
* Thomas de Lange
*
* Een programma dat de eerste letters van een naam geeft de initialen als hoofdletters.
***************************************************************************/

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string();
    int length_string = strlen(name);

    // Print de eerst letter van de naam uit.
    printf("%c", toupper(name[0]));

    // Kijk binnen de loop of er een spatie is. Na de spatie komt een nieuwe initial die geprint moet worden.
    for (int i = 0; i < length_string; i++)
    {
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }
    }

    // Print een enter voor corretheid.
    printf("\n");
}