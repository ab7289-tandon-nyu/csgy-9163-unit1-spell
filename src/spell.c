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

            //TODO need to remove line breaks
            
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
    int result = fclose(fptr);
    if (result != 0) {
        printf("unable to close the file");
    }
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
    hashmap_t cursor;
    // move the cursor along the hashtable
    for (int i = 0; i < bucket; i++) {
        hashtable++;
    }
    cursor = *hashtable;
    // move the cursor back, not sure if this is necessary but the tests pass
    for (int i = 0; i < bucket; i++) {
        hashtable--;
    }

    while (cursor != NULL && cursor->word != NULL) {
        if (strcmp(word, cursor->word) == 0) {
            return true;
        }
        cursor = cursor->next;
    }
    
    // set word to lowercase
    char l_word[LENGTH + 1];
    lower_case(l_word, word); 

    bucket = hash_function(l_word);
    for (int i = 0; i < bucket; i++) {
        hashtable++;
    }
    cursor = *hashtable;

    while (cursor != NULL) {
        if (strcmp(l_word, cursor->word) == 0) {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

/**
 * Array misspelled is populated with words that are misspelled. Returns the length of misspelled.
 */
/**
 * Inputs:
 *  fp:         A file pointer to the document to check for spelling errors.
 *  hashtable:  The hash table used to determine spelling
 *  misspelled: An empty char* array to be populated with misspelled words.
 *              This array will never be greater than 1000 words long.
 *
 * Returns:
 *  int:        The number of words in the misspelled arary.
 *
 * Modifies:
 *  misspelled: This array will be filled with misspelled words.
 *
 * Example:
 *  int num_misspelled = check_words(text_file, hashtable, misspelled);
 **/
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {

    int num_misspelled = 0;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL) {
        printf("fp was null");
        return -1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        // split line on spaces
        int len = 32;
        char * word_list[len];
        int count = split_line(line, word_list, len);

        //for each word in line
        for (int i = 0; i < count; ++i) {
            char dest[strlen(word_list[i])];
            //remove punctuation
            remove_punc(word_list[i], dest);
                //if not check word
            if (!check_word(dest, hashtable)) {
                //append to mispelled
                strcpy(*misspelled++, dest);
                // increment num_mispelled
                ++num_misspelled;
            }
        }
    }

    return num_misspelled;
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

/**
 * Returns an array of strings and a length
 * */
/**
 * Inputs:
 *  line:           the line to be split
 *  word_list:      the array of size to fill with the words
 *  len:            the length of the passed in array
 * 
 * Returns:
 *  int:            the number of words in the returned list
 * 
 * Modifies:
 *  word_list:      word_list should be filled with the split words
 **/
int split_line(const char * line, char ** word_list, int list_length) {
    int word_size = 0;
    char delim[] = " ";

    int line_size = strlen(line);
    char temp_str[line_size];
    // want to copy to a temporary string since strtok modifies
    // the original
    strcpy(temp_str, line);

    // get the pointer to the first token
    char * split_ptr = strtok(temp_str, delim);
    while (split_ptr != NULL && word_size < list_length) {
        // allocate space for the new word
        *word_list = (char *) malloc(strlen(split_ptr) * sizeof(char*));
        // copy it from the token
        strcpy(*word_list, split_ptr);

        split_ptr = strtok(NULL, delim);
        ++word_size;
        ++word_list; // increment the list ptr so next iteration we're looking at next index
    }
    
    return word_size;
}

// removes punctuation marks from a word
// assumes that the word is not an empty string
void remove_punc(const char * word, char * dest) {
    char punc[] = { ',', '!', '.', '?', ';', ':', '-', '{', '}', '[', ']', '(', ')', '\'', '"', NULL};
    int len = strlen(word);

    for ( ; *word; ++word) {
        bool is_punc = true;
        for (int i = 0; punc[i]; ++i) {
            if (*word == punc[i]) {
                is_punc = false;
                break;
            }
        }
        if (is_punc) {
            *dest++ = *word;
        }
    }
    *dest = 0;
}
