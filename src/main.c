//
//  main.c
//  csgy-9163-unit1-spell
//
//  Created by Alex Biehl on 5/28/20.
//  Copyright © 2020 Alex Biehl. All rights reserved.
//
#include "spell.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World2!\n");
    hashmap_t map[HASH_SIZE];
    bool loaded = load_dictionary("/Users/alexbiehl/dev/workspace/NYU/tandon_mscs/csgy9163_ApplicationSecurity/csgy-9163-unit1-spell/res/test_wordlist.txt", map);

    return (loaded == true ? 0 : 1);
}