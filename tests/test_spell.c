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

Suite * check_dictionary_suite(void) {
    Suite * suite;
    TCase * check_dictionary_case;
    TCase * check_dictionary_input_case;

    suite = suite_create("check_dictionary");

    check_dictionary_case = tcase_create("Core");
    tcase_add_test(check_dictionary_case, test_dictionary_normal);
    suite_add_tcase(suite, check_dictionary_case);

    check_dictionary_input_case = tcase_create("Inputs");
    tcase_add_test(check_dictionary_input_case, test_dictionary_bad_hashtable);
    tcase_add_test(check_dictionary_input_case, test_dictionary_empty_filename);
    tcase_add_test(check_dictionary_input_case, test_dictionary_null_hashtable);
    suite_add_tcase(suite, check_dictionary_input_case);

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





