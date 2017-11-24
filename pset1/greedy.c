/****************************************************************************
 * greedy.c
 * Thomas de Lange
 *
 * Neemt een getal en gooit het in potjes van .25 .10 .05 en .01 dan geeft die
 * terug het aantal muntjes van iedere groep.
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {

    // Maak de float mony aan en kijk of deze hoger is dan 0.
    float mony;
    do {
        printf("O hai! How much change is owed? ");
        mony = get_float();
    } while (mony < 0);


    int mony_temp = round(money * 100);
    int counter = 0;

    counter = counter + (mony_temp / 25);
    mony_temp = (mony_temp % 25);

    counter = counter + (mony_temp / 10);
    mony_temp = (mony_temp % 10);

    counter = counter + (mony_temp / 5);
    mony_temp = (mony_temp % 5);

    counter = counter + (mony_temp / 1);
    mony_temp = (mony_temp % 1);

    printf("%i\n", counter);
}