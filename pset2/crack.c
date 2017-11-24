/****************************************************************************
 * crack.c
 * Thomas de Lange
 *
 * Student nummer: 11067632
 *
 * crack.c neemt een gecodeerde string en kijkt wat hier het wachtwoord van is.
 *
 * $ ./crack 50fkUxYHbnXGw
 * rofl
 ***************************************************************************/

#define _XOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>
#include <crypt.h>
#include <cs50.h>
#include <string.h>

#define LOWERA  96
#define LOWERZ  122
#define UPPERA  65
#define UPPERZ  90

int check(const char* lhs, const char* rhs)
{
    int rc = strcmp(lhs, rhs);
    if(rc == 0)
        return 0;
    return 1;
}

int main( int argc, char *argv[] )
{
    if ( argc == 2 )
    {
        // initializeren van de variabelen
        string versleuteld_wachtwoord = argv[1];

        char salt[] = "50";
        char *versleuteld_tester;

        char wachtwoord_tester[4];
        wachtwoord_tester[1] = '\0';
        wachtwoord_tester[2] = '\0';
        wachtwoord_tester[3] = '\0';

        // for loop #i
        for (int i = UPPERA; i <= LOWERZ; i++)
        {
            // test op gelijkheid i
            wachtwoord_tester[0] = i;
            versleuteld_tester = crypt(wachtwoord_tester, salt);

            if (check(versleuteld_wachtwoord,versleuteld_tester) == 0)
            {
                puts(wachtwoord_tester);
                return 0;
            }
            printf("wachtwoord_tester: %s\n", wachtwoord_tester);

            int counter_j = UPPERA;

            for (int j = UPPERA; j <= LOWERZ; j++)
            {
                // test op gelijkheid j
                wachtwoord_tester[1] = counter_j;
                versleuteld_tester = crypt(wachtwoord_tester, salt);


                if (check(versleuteld_wachtwoord,versleuteld_tester) == 0)
                {
                    puts(wachtwoord_tester);
                    return 0;
                }

                counter_j++;
                int counter_k = UPPERA;

                for (int k = UPPERA; k <= LOWERZ; k++)
                {
                    // test op gelijkheid k
                    wachtwoord_tester[2] = counter_k;
                    versleuteld_tester = crypt(wachtwoord_tester, salt);

                    if (check(versleuteld_wachtwoord,versleuteld_tester) == 0)
                    {
                        puts(wachtwoord_tester);
                        return 0;
                    }

                    counter_k++;
                    int counter_l = UPPERA;

                    for (int l = UPPERA; l <= LOWERZ; l++)
                    {
                        // test op gelijkheid l
                        wachtwoord_tester[3] = counter_l;
                        versleuteld_tester = crypt(wachtwoord_tester, salt);

                        if (check(versleuteld_wachtwoord,versleuteld_tester) == 0)
                        {
                            puts(wachtwoord_tester);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    else if( argc > 2 )
    {
        printf("Usage: ./crack [50yourpassword]\n");
        return 1;
    }
    else
    {
        printf("Usage: ./crack [50yourpassword]\n");
        return 1;
    }
}


