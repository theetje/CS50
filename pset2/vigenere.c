/****************************************************************************
* vigenere.c
* Thomas de Lange
*
* Student nummer: 11067632
*
* Vigenere codeert een woord of reeks woorden met behulp van een ander woord
* waarvan de letters de verschruiving in stappen op het ASCII zijn.
*
* running ./vigenere baz...
* sending input barfoo...
* checking for output "gecodeerde_text: caqgon "...
***************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// #define de hun lettrs ASCII waarden
#define LOWERA  97
#define LOWERZ  122
#define UPPERA  65
#define UPPERZ  90

int main( int argc, char *argv[] )
{
    if ( argc == 2 )
    {
        // Stel de variabelen samen
        int lengte_sleutel = strlen(argv[1]);
        int v_key[lengte_sleutel];
        int isascii(int c);

        // Zet de letters van de v_key om in de juiste key value
        for (int i = 0; i < lengte_sleutel; i++)
        {
            v_key[i] = argv[1][i];

            if (v_key[i] >= UPPERA && v_key[i] <= UPPERZ)
            {
                v_key[i] -= UPPERA;
            }
            //   Kijk daarna naar de kleine letters
            else if (v_key[i] >= LOWERA && v_key[i] <= LOWERZ)
            {
                v_key[i] -= LOWERA;
            }
            else if (isascii(v_key[i]) != 0)
            {
                return 1;
            }
        }
        // Vraag om de orginele_text
        printf("plaintext: ");
        string orginele_text = get_string();
        int length_text = strlen(orginele_text);

        printf("ciphertext: ");
        int gecodeerde_text;

        // Zet de orginele_text om in de cipertext m.b.v. de v_key
        for (int i = 0; i < length_text; i++)
        {
            gecodeerde_text = orginele_text[i] + v_key[i % lengte_sleutel];

            //   Kijk eerst naar de grote letters
            if (orginele_text[i] >= UPPERA && orginele_text[i] <= UPPERZ)
            {
                if (gecodeerde_text > UPPERZ)
                {
                    gecodeerde_text -= 26;
                }
                printf("%c", gecodeerde_text);
            }

            //   Kijk daarna naar de kleine letters
            else if (orginele_text[i] >= LOWERA && orginele_text[i] <= LOWERZ)
            {
                if (gecodeerde_text > LOWERZ)
                {
                    gecodeerde_text -= 26;
                }
                printf("%c", gecodeerde_text);
            }
            else
            {
                printf("%c", orginele_text[i]);
            }
        }
        printf("\n");
        return 0;
    }

    // Kijk naar de argc als deze niet 2 is is er zeker een fout.
    else if ( argc > 2 )
    {
        printf("Usage: ./vigenere k.\n");
        return 1;
    }
    else
    {
        printf("Usage: ./vigenere k.\n");
        return 1;
    }
}