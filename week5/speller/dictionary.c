// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 2;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // get word's position in hash table
    int word_type;
    if (strlen(word) <= 6)
    {
        word_type = 0;
    }
    else
    {
        word_type = 1;
    }
    int first_letter = tolower(word[0]) - 'a';
    unsigned int index = first_letter * 2 + word_type;

    return index;
}

bool save_to_hash(char *buffer)
{
    node *vocable = calloc(1, sizeof(node));
    if (vocable == NULL)
    {
        return false;
    }
    vocable->word = buffer;
    vocable->next = NULL;

    // get word's position in hash table
    int index = hash(buffer);
    vocable->next = table[index];
    table[index] = vocable;
    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the file of dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    // read word from dictionary
    char *buffer[LENGTH + 1];
    while (fgets(buffer, LENGTH+1, file))
    {
        if(!save_to_hash(buffer))
        {
            return false;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        table[i]
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
