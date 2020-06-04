//
//  test_spell.c
//  csgy-9163-unit1-spell
//
//  Created by Alex Biehl on 5/30/20.
//  Copyright © 2020 Alex Biehl. All rights reserved.
//
#include <config.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <check.h>
#include "../src/spell.h"

#define DICTIONARY "../res/wordlist.txt"
#define TESTDICT "../res/test_wordlist.txt"

// TODO add tests

bool check_bucket(hashmap_t map, char * test_val);


// start dictionary load test cases
START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
    // check buckets

    char * test_val = "first\n";
    int hash = hash_function(test_val);
    ck_assert(check_bucket(hashtable[hash], test_val));
    
    test_val = "second\n";
    hash = hash_function(test_val);
    ck_assert(check_bucket(hashtable[hash], test_val));

    test_val = "third\n";
    hash = hash_function(test_val);
    ck_assert(check_bucket(hashtable[hash], test_val));

    test_val = "test\n";
    hash = hash_function(test_val);
    ck_assert(check_bucket(hashtable[hash], test_val));
}
END_TEST

START_TEST(test_dictionary_bad_hashtable) {
    
    hashmap_t hashtable = NULL;
    ck_assert(!load_dictionary(TESTDICT, hashtable));

} END_TEST

START_TEST(test_dictionary_null_hashtable) {
    
    ck_assert(!load_dictionary(TESTDICT, NULL));

} END_TEST

START_TEST(test_dictionary_empty_filename) {
    
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(!load_dictionary("bad_file.txt", hashtable));

} END_TEST
// end dictionary load test cases

//start check_word test cases
START_TEST(test_check_word_empty_word) {

    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(TESTDICT, hashtable);
    const char * null_word = NULL;
    ck_assert(!check_word(null_word, hashtable));

} END_TEST

START_TEST(test_check_word_empty_table) {

    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(TESTDICT, hashtable);
    const char * word = "first";
    ck_assert(!check_word(word, NULL));

} END_TEST

START_TEST(test_check_word) {

    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(TESTDICT, hashtable);

    const char * w = "first\n";
    ck_assert(check_word(w, hashtable));

    const char * word = "FIRST\n";
    ck_assert(check_word(word, hashtable));

    const char * word1 = "sEconD\n";
    ck_assert(check_word(word1, hashtable));

    const char * word_invalid = "nOt HeRe";
    ck_assert(!check_word(word_invalid, hashtable));

} END_TEST
//end check word_test cases

// start lower_case test cases

START_TEST(test_lower_null_l_word) {

    char * word = "WORD";
    ck_assert(!lower_case(NULL, word));

} END_TEST

START_TEST(test_lower_null_word) {

    char l_word[LENGTH];
    ck_assert(!lower_case(l_word, NULL));

} END_TEST

START_TEST(test_lower_word) {

    char l_word[LENGTH + 1];
    char * word = "WORD";
    ck_assert(lower_case(l_word, word));
    ck_assert(strcmp(l_word, "word") == 0);

} END_TEST

// end lower_case test cases

// start split_line test cases

START_TEST(test_split_line_empty) {

    char * line = "";
    int len = 32;
    char * word_list[len];
    int count = split_line(line, word_list, len);
    bool count_correct = count == 0;
    
    ck_assert(count_correct);

} END_TEST

START_TEST(test_split_line_single) {

    char * line = "hello";
    int len = 32;
    char * word_list[len];
    int count = split_line(line, word_list, len);
    
    bool count_correct = count == 1;
    bool word_correct = (strcmp(*word_list, "hello") == 0);

    for (int i = 0; i < count; ++i) {
        free(word_list[i]);
    }

    ck_assert(count_correct);
    ck_assert(word_correct);

} END_TEST

START_TEST(test_split_line_multiple) {

    char * line = "hello world";
    int len = 32;
    char * word_list[len];
    int count = split_line(line, word_list, len);
    bool count_correct = count == 2;

    char * answers[] = { "hello","world" };
    bool word_correct = true;
    for (int i = 0; i < count; i++) {
        //printf("Word %d is: %s \n", i, word_list[i]);
        if (strcmp(word_list[i], answers[i]) != 0) {
            word_correct = false;
            break;
        }
    }

    for (int i = 0; i < count; ++i) {
        free(word_list[i]);
    }

    ck_assert(count_correct);
    ck_assert(word_correct);

} END_TEST

START_TEST (test_split_line_multi_spaces) {

    char * line = " hello  world   mate ";
    int len = 32;
    char * word_list[len];
    int count = split_line(line, word_list, len);
    bool count_correct = count == 3;

    char * answers[] = { "hello", "world", "mate" };
    bool word_correct = true;
    for (int i = 0; i < count; ++i) {
        //printf("Word %d is: %s \n", i, word_list[i]);
        if (strcmp(word_list[i], answers[i]) != 0) {
            word_correct = false;
            break;
        }
    }

    for (int i = 0; i < count; ++i) {
        free(word_list[i]);
    }

    ck_assert(count_correct);
    ck_assert(word_correct);

} END_TEST

// end split_line test cases

Suite * check_dictionary_suite(void) {
    Suite * suite;
    TCase * check_dictionary_case;
    TCase * check_dictionary_input_case;
    TCase * check_word_case;
    TCase * check_lower_case;
    TCase * check_split_line_case;

    suite = suite_create("check_dictionary");

    check_dictionary_case = tcase_create("Core");
    tcase_add_test(check_dictionary_case, test_dictionary_normal);
    suite_add_tcase(suite, check_dictionary_case);

    check_dictionary_input_case = tcase_create("Inputs");
    tcase_add_test(check_dictionary_input_case, test_dictionary_bad_hashtable);
    tcase_add_test(check_dictionary_input_case, test_dictionary_empty_filename);
    tcase_add_test(check_dictionary_input_case, test_dictionary_null_hashtable);
    suite_add_tcase(suite, check_dictionary_input_case);

    check_word_case = tcase_create("Check Word");
    tcase_add_test(check_word_case, test_check_word_empty_word);
    tcase_add_test(check_word_case, test_check_word_empty_table);
    tcase_add_test(check_word_case, test_check_word);
    suite_add_tcase(suite, check_word_case);

    check_lower_case = tcase_create("Lower Case");
    tcase_add_test(check_lower_case, test_lower_null_l_word);
    tcase_add_test(check_lower_case, test_lower_null_word);
    tcase_add_test(check_lower_case, test_lower_word);
    suite_add_tcase(suite, check_lower_case);

    check_split_line_case = tcase_create("Split Line");
    tcase_add_test(check_split_line_case, test_split_line_empty);
    tcase_add_test(check_split_line_case, test_split_line_single);
    tcase_add_test(check_split_line_case, test_split_line_multiple);
    tcase_add_test(check_split_line_case, test_split_line_multi_spaces);
    suite_add_tcase(suite, check_split_line_case);


    return suite;
}

int main(void) {
    int failed;
    Suite * suite;
    SRunner *runner;

    suite = check_dictionary_suite();
    runner = srunner_create(suite);
    srunner_set_log(runner, "test.log");
    // uncomment the next line if debugging
    // srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

bool check_bucket(hashmap_t map, char * test_val) {
    while (map->next != NULL && strcmp(test_val, map->word) != 0) {
        map = map->next;
    }
    
    return (strcmp(test_val, map->word) == 0);
}





