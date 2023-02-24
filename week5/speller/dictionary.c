// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct Node {
    char word[LENGTH + 1];
    struct Node *next;
} Node;

// TODO: Choose number of buckets in hash table
const unsigned int BUCKET_SIZE = 26 * 2;

// Hash table
typedef struct {
    Node *buckets[BUCKET_SIZE];
    unsigned int size;
} HashTable;

HashTable table = {{NULL}, 0};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    Node *curr_node = table.buckets[index];
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
    int word_type = (int) strlen(word)> 6;
    int first_letter = tolower(word[0]) - 'a';
    // TODO handle special case, like empty string, or strange char.
    unsigned int index = first_letter * 2 + word_type;
    return index;
}

bool save_to_hash(char *buffer)
{
    Node *vocable = calloc(1, sizeof(Node));
    if (vocable == NULL) {
        return false;
    }
    strcpy(vocable->word, buffer);
    vocable->next = NULL;
    // get word's position in hash table
    unsigned int index = hash(buffer);
    if (index < 0 || index >= BUCKET_SIZE) return false;
    vocable->next = table.buckets[index];
    table.buckets[index] = vocable;
    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the file of dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // read word from dictionary and save to hashtable
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF) {
        if(!save_to_hash(buffer)) {
            return false;
        }
        table.size++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    return table.size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    // free elements of hash table array
    for (int i = 0; i < BUCKET_SIZE; i++) {
        Node *curr_node = table.buckets[i];
        while (curr_node != NULL) {
            Node *next_node = curr_node->next;
            free(curr_node);
            table.size--;
            curr_node = next_node;
        }
    }
    return true;
}
