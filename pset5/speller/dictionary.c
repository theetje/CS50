/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

int counter_words = 0;
bool loader = false;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Zet de curser op de root
    node *curser = root;

    // Loop letter voor letter door de text heen.
    // Eventueel de strlen eruit halen of anders declareren dat die niet elke keer de foorloop opvraagd --------------------------!
    for (int i = 0; i < strlen(word); i++)
    {
        int temp_letter = check_character(word[i]);

        // Als het onderdeel leeg is betekend het dat er zeker geen woord is dus return false
        if (curser->letter[temp_letter] != NULL)
        {
            curser = curser->letter[temp_letter];
        }
        else
        {
            return false;
        }
    }

    // Als die niet leeg is de loop klaar is en curser->is_word is true dan is het een woord.
    if (curser->is_word == true)
    {
        return true;
    }

    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.\
 *
 */
bool load(const char *dictionary)
{
    // Open plek in het geheugen die naar het bestand wijst van de dictionary.
    FILE *fp = fopen(dictionary, "r");

    // Maak hier de plek van het geheugen bekend waar de tree begint.
    root = malloc(sizeof(node));

    // Kreeg een fout van valgrind dat het geheugen gecontroleerd word op niets
    // dit lost dat op omdat het geheugen dan gezet is op NULL niet op niks.
    // Bron: https://cs50.stackexchange.com/questions/18563/conditional-jump-or-move-depends-on-uninitialised-values
    memset(root, 0, sizeof(node));
    node *curser = root;

    // Maak
    char word[MAXWORDLENTH];

    // Loop door de dictionary heen tot je bij het EOF komt.
    while (fscanf(fp, "%s", word) != EOF)
    {
        // Neem Een woord en laat deze letter voor letter in de trie
        for (int i = 0; i < strlen(word); i++)
        {
            // kijk op welke plek het woord moet staan met een soort hash
            int current_character = check_character(word[i]);

            // Je hebt hieronder calloc gebruikt ipv memset en daarvoor malloc
            if (curser->letter[current_character] == NULL)
            {
                node *new_ptr = calloc(sizeof(node));
                curser->letter[current_character] = new_ptr;
            }

            curser = curser->letter[current_character];
        }
        counter_words++;
        curser->is_word = true;
        curser = root;
    }

    fclose(fp);
    loader = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (loader == true)
    {
        return counter_words;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    free_tree(root);
    return true;
}

void free_tree(node *curser)
{
    for (int i = 0; i < 27; i++)
    {
        if (curser->letter[i] != NULL)
        {
            free_tree(curser->letter[i]);
            curser->letter[i] = NULL;
        }
    }
    free(curser);
    return;
}


/**
 * Maakt de nieuewe letters op volgorde van 0 tot 26 ( + '\'')
 */

int check_character(int character)
{
    int letter_temp = 0;

    // Kijk of de eerste letter een letter is of een comma en zet dan om.
    if (isalpha(character))
    {
        letter_temp = tolower(character) - LOWERA;
        return letter_temp;
    }
    else if (character == APPASTROF)
    {
        letter_temp = APPASTROF - 13;
        return letter_temp;
    }
    else
    {
        // Er is geen geldig teken door gegeven.
        exit(1);
    }
}