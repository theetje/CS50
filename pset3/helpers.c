/**
 * helpers.c
 * Thomas de lange
 * student nummer 11067632
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <string.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // kijkt of er negative getallen uit komen (inclusief 0)
    if (value < 1)
    {
        return false;
    }

    // Geef variabelen die de structuur van de binare zoekfuncite vormen.
    int array_front = 0;
    int array_end = n - 1;
    int middle = ((array_front + array_end) / 2);


    // Neem de array(hooi) en kijk of het middelelste getal een naald is, hoger is of lager is.
    while (array_end >= array_front)
    {
        if (value == values[middle])
        {
            return true;
        }
        else if (value < values[middle])
        {
            array_end = middle - 1;
        }
        else if (value > values[middle])
        {
            array_front = middle + 1;
        }

        middle = ((array_front + array_end) / 2);
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Eerst sorteren anders kan de binary search algorithm niet
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (values[j] < values[j - 1])
            {
                int temp        = values[j - 1];
                values[j - 1]   = values[j];
                values[j]       = temp;
            }
        }
    }
}