#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Maak variabelen aan en vraag om Number:
    printf("Number: ");
    long long card_number = get_long_long();
    int length_number = floor(log10(llabs(card_number))) + 1;
    int card_array[length_number];

    // Hier onder een array met daarin de getallen op ieder een apparte plek met card_array[0] het laatste getal
    for (int i = 0; i < length_number; i++)
    {
        int card_modulo = card_number % 10;
        card_array[i] = card_modulo;
        card_number = card_number - card_modulo;
        card_number = round(card_number / 10);
    }

    // Counter voor de oneven getallen
    int odd_counter = 0;

    // Loop door de card_array en laat de oneven getallen in odd_counter (correct)
    for (int j = 1; j < length_number; j+=2)
    {
        int multiple = card_array[j] * 2;

        if (multiple > 9)
        {
            odd_counter += multiple % 10;
            odd_counter += 1;
        }
        else
        {
            odd_counter += multiple;
        }
    }

    // counter voor de even getallen
    int equ_counter = 0;

    // Loop door de card_array en laat de even getallen in odd_counter (correct)
    for (int k = 0; k < length_number; k+=2)
    {
        equ_counter += card_array[k];
    }

    // Maak een totaal int en tel de odd_counter en equ_counter hier in, neem dan het laatste getal
    int total = odd_counter + equ_counter;
    int total_modulo = total % 10;

    // Kijk per onderdeel of het voldoet aan de vereisten van een credit card.
    if (total_modulo != 0)
    {
        printf("INVALID\n");
    }

    else if (card_array[length_number - 1] == 3 && card_array[length_number - 2] == 4)
    {
        printf("AMEX\n");
    }

    else if (card_array[length_number - 1] == 3 && card_array[length_number - 2] == 7)
    {
        printf("AMEX\n");
    }

    else if (card_array[length_number - 1] == 5 && card_array[length_number - 2] == 1)
    {
        printf("MASTERCARD\n");
    }

    else if (card_array[length_number - 1] == 5 && card_array[length_number - 2] == 2)
    {
        printf("MASTERCARD\n");
    }

    else if (card_array[length_number - 1] == 5 && card_array[length_number - 2] == 3)
    {
        printf("MASTERCARD\n");
    }

    else if (card_array[length_number - 1] == 5 && card_array[length_number - 2] == 4)
    {
        printf("MASTERCARD\n");
    }

    else if (card_array[length_number - 1] == 5 && card_array[length_number - 2] == 5)
    {
        printf("MASTERCARD\n");
    }

    else if (card_array[length_number - 1] == 4)
    {
        printf("VISA\n");
    }
}