// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

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
typedef struct HashTable
{
    node *table[N];
    int size;
}
HashTable;

HashTable *table;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *curr_node = table->table[index];
    while (curr_node != NULL)
    {
        if(strcasecmp(curr_node->word, word) == 0)
        {
            return true;
        }
        curr_node = curr_node->next;
    }
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
    strcpy(vocable->word, buffer);
    vocable->next = NULL;

    // get word's position in hash table
    unsigned int index = hash(buffer);
    vocable->next = table->table[index];
    table->table[index] = vocable;
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
    // read word from dictionary and save to hashtable
    table = malloc(sizeof(HashTable));
    if (table == NULL)
    {
        return false;
    }
    table->size = 0;

    char buffer[LENGTH + 2];
    while (fgets(buffer, LENGTH+2, file))
    {
        if(!save_to_hash(buffer))
        {
            return false;
        }
        else
        {
            table->size++;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return table->size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // free elements of hash array
    if (table == NULL)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        node *curr_node = table->table[i];
        if (curr_node == NULL)
        {
            continue;
        }
        while (curr_node != NULL)
        {
            node *next_node = curr_node->next;
            free(curr_node);
            curr_node = next_node;
        }
    }
    // free the table
    free(table);
    return true;
}
