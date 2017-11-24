/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#define APPASTROF 39
#define LOWERA 97
#define MAXWORDLENTH 45

#include <stdbool.h>
#include <stdio.h>
// voor testen met exit(0);
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
    bool is_word;
    struct node *letter[27];
}
node;
node *root;

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Controleer het character dat je inneemt.
 */
int check_character(int character);

/**
 * Helper functie voor het legen van het geheugen.
 */
void free_tree(node *curser);

#endif // DICTIONARY_H
