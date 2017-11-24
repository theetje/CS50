/****************************************************************************
* caesar.c
* Thomas de Lange
* Student nummer: 11067632
*
* codeerd een tekst met behulp van ceasars cypher
***************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main( int argc, char *argv[] )
{
    if ( argc == 2 )
    {
        // initieren van de variabelen
        printf("The plaintext: ");
        string plaintext = get_string();
        int lenth_text = strlen(plaintext);
        int c_steps = atoi(argv[1]);
        int ciphertext;

        if (c_steps > 26)
        {
            c_steps = c_steps % 26;
        }


        printf("The ciphertext: ");

        for (int i = 0; i < lenth_text; i++)
        {
            ciphertext = plaintext[i] + c_steps;

            //   Kijk eerst naar de grote letters
            if (plaintext[i] > 64 && plaintext[i] < 91)
            {
                if (ciphertext > 90)
                {
                    ciphertext -= 26;
                }
                printf("%c", ciphertext);
            }
            //   Kijk daarna naar de kleine letters
            else if (plaintext[i] > 96 && plaintext[i] < 123)
            {
                if (ciphertext > 122)
                {
                    ciphertext -= 26;
                }
                printf("%c", ciphertext);
            }
            // print gewoone text als het iets anders is
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;

    }
    // als er teveel of niet genoeg argumenten worden gegeven dan gaat die dood
    else if ( argc > 2 )
    {
        printf("Too many arguments supplied.\n");
        return 1;
    }
    else
    {
        printf("One argument expected.\n");
        return 1;
    }
}
