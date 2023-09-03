// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "dictionary.h"
#include <math.h>

#define PI 3.14


//global vars.
unsigned int hash_code;
unsigned int wordcount;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; //'+1' for nul char(?)
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26; //initial idea: 1 hash for each alphabet letter(?)

// Hash table -> keep track of dictionary words -> 'backbone' of hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *trav = NULL;
    trav = table[hash(word)]; //trav point to haed of linked list on position hash_code
    while(trav != NULL)
    {
        if(strcasecmp(word, trav->word) == 0)
        {
            return true;
        }
        else
        {
            trav = trav ->next;
        }
    }
    return false;
}

// Hashes word to a number (hash code) - hash function
unsigned int hash(const char *word)
{
    int hash = 0;
    for(int i = 0; i<strlen(word); i++)
    {
        if(isalpha(word[i]))
        {
            hash = round(toupper(word[i]) * pow(PI, i));
        }
    }
    hash = hash % N;
    return hash;
}



// Loads dictionary into memory, returning true if successful, else false => insert words into hash table?
bool load(const char *dictionary)
{
    //open dict and check for safety
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL){
        printf("could not open dictionary.\n");
        unload();
        fclose(dict);
        return false;
    }
    //to store words
    char word[LENGTH+1];
    while(fscanf(dict, "%s", word)!= EOF)
    {
        //hash code for word and alloc mem
        hash_code = hash(word);
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            unload();
            return false;
        }
        strcpy(n->word, word); //word into node
        n->next = table[hash_code];
        table[hash_code] = n;

        wordcount++;
    }
    fclose(dict);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //case: success in loading (and dict has words)
    if (wordcount>0){
        return wordcount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to this each bucket location
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            free(temp);
        }
        if (cursor == NULL && i == N-1)
        {
            return true;
        }
    }
    return false;
}
