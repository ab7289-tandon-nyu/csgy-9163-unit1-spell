/****************************************************************************
 * spell.c
 *
 * Application Security, Assignment 1
 *
 * Adapted from code written by Ben Halperin.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "spell.h"

// Hash table is an array of linked lists.
node* hashtable[HASH_SIZE];

// Maps a word to an integer value to place it in the hash table.
// Sum the value of each character in the word, then find the
// remainder after dividing by the size of the hash table.
int hash_function(const char* word)
{
    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        sum += word[i];
    }
    
    int bucket = sum % HASH_SIZE;
    return bucket;
}


// given a dictionary file and a hashtable, load the dictionary file 
// into the hastable
// if successfull returns true
// otherwise returns false
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {

    // check if hashtable is null
    if (hashtable == NULL) {
        // hashtable was not initialized
        return false;
    }
    
    // initialize each of its values to NULL if it's valid
    for (int i = 0; i < HASH_SIZE; i++) {
        hashtable[i] = NULL;
    }

    // make sure we weren't handed an empty pointer
    if (dictionary_file == NULL) {
        printf("dictionary_file was null");
        return false;
    }
    
    FILE * fptr;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fptr = fopen(dictionary_file, "r");
    if (fptr == NULL) {
        printf("fptr was null");
        return false;
    }

    while ((read = getline(&line, &len, fptr)) != -1) {
        // printf("read word %s\n", line);
        if (read <= LENGTH) {
            hashmap_t new_node = (hashmap_t) malloc(sizeof(hashmap_t));
            new_node->next = NULL;
            strcpy(new_node->word, line);
            
            // printf("\tcopied word is: %s\n", new_node->word);
            int bucket = hash_function(line);

            if (hashtable[bucket] == NULL) {
                hashtable[bucket] = new_node;
            } else {
                new_node->next = hashtable[bucket];
                hashtable[bucket] = new_node;
            }
        } else {
            printf("word was too big %s", line);
        }
    }

    // close file
    fclose(fptr);

    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
/**
 * Inputs:
 *  word:       A word to check the spelling of.
 *  hashtable:  The hash table used to determine spelling
 *
 * Returns:
 *  bool:       A boolean value indicating if the word was correctly spelled.
 *
 * Modifies:
 *
 * Example:
 *  bool correct  = check_word(word, hashtable);
 **/
bool check_word(const char* word, hashmap_t hashtable[]) {

    if (word == NULL || hashtable == NULL) {
        return false;
    }

    int bucket = hash_function(word);
    hashmap_t cursor = hashtable[bucket];

    while (cursor != NULL) {
        if (strcmp(word, cursor->word) == 0) {
            return true;
        }
        cursor = cursor->next;
    }

    cursor = hashtable[bucket];
    
    // set word to lowercase
    char l_word[LENGTH + 1];
    lower_case(l_word, word); 

    while (cursor != NULL) {
        if (strcmp(l_word, cursor->word) == 0) {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}


/**
 * Returns a string as lower case
 * */
/**
 * Inputs:
 *  l_word:     the word to be populated
 *  word:       the word to be made lower_case
 * 
 * Returns:
 *  bool:      whether or not the word was made lower case
 * 
 * Modifies:
 *  l_word:      l_word should be filled by the word all lower case
 **/
bool lower_case(char * l_word, const char * word) {
    
    if (l_word == NULL || word == NULL) {
        return false;
    }

    for (int i = 0; i < LENGTH; i++) {
        l_word[i] = NULL;
    }

    for (int i = 0; word[i]; ++i) {
        l_word[i] = tolower(word[i]);
    }
    return true;
}
