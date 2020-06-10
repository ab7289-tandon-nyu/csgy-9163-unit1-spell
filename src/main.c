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
    
    printf("arg0 %s \n", argv[0]);
    printf("arg1 %s \n", argv[1]);
    printf("arg2 %s \n", argv[2]);

    return spell_check(argv[1], argv[2]);
}