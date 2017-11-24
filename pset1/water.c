#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>

int main (void)
{
    // Maak de variabelen.
    printf("Minutes:");
    int minutes = get_int();
    int bottles;

    // Bereken hoeveel bottles het kost per minut.ls
    bottles = minutes * 12;

    printf("Bottles: %i\n", bottles);
}