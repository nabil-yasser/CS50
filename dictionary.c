// Implements a dictionary's functionality

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;
unsigned int sizeCounter = 0;

// Hash table
node* table[N];

// Returns true if word is in dictionary, else false
bool check(const char* word)
{
    unsigned int hashCode = hash(word);
    for (node* n = table[hashCode]; n != NULL; n = n->next)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char* word)
{
    unsigned char letters[] = { 'a', 'b', 'c', 'd' ,'e' ,'f' ,'g' ,'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    for (unsigned char i = 0; i < 26; i++)
    {
        if (tolower(word[0]) == letters[i])
        {
            for (unsigned char j = 0; j < 26; j++)
            {
                if (tolower(word[1]) == letters[j])
                {
                    for (unsigned char k = 0; k < 26; k++)
                    {
                        if (tolower(word[2]) == letters[k])
                        {
                            return ((676 * i) + (26 * j) + k);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char* dictionary)
{
    FILE* dictionaryFile = fopen(dictionary, "r");
    if (dictionaryFile == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while (fscanf(dictionaryFile, "%s", buffer) != EOF)
    {
        node* newElement = malloc(sizeof(node));
        if (newElement == NULL)
        {
            return false;
        }
        strcpy(newElement->word, buffer);
        newElement->next = NULL;
        int hashCode = hash(newElement->word);
        newElement->next = table[hashCode];
        table[hashCode] = newElement;
        sizeCounter++;
    }
    fclose(dictionaryFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        for (node* cursor = table[i]; cursor != NULL; )
        {
            node* tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
