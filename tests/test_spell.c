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
#include <check.h>
#include "../src/spell.h"

#define DICTIONARY "../res/wordlist.txt"
#define TESTDICT "../res/test_wordlist.txt"

// TODO add tests


START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
}
END_TEST

Suite * check_dictionary_suite(void) {
    Suite * suite;
    TCase * check_dictionary_case;
    suite = suite_create("check_dictionary");
    check_dictionary_case = tcase_create("Core");
    tcase_add_test(check_dictionary_case, test_dictionary_normal);
    suite_add_tcase(suite, check_dictionary_case);

    return suite;
}

int main(void) {
    int failed;
    Suite * suite;
    SRunner *runner;

    suite = check_dictionary_suite();
    runner = srunner_create(suite);
    srunner_set_log(runner, "test.log");
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}





