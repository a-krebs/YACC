#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Hash.h"



void dumpSymbolTable() {
    struct hashElement *element;

    printf("\n\nDUMPING HASH:\n");

    for ( int i = 0; i < TABLE_SIZE; ++i) {
        if ( symbolTable[i] != NULL ) {
            element = symbolTable[i];

            printf("Element: %d:\n", i);
            
            for (; element != NULL; element = element->next) {
                printf("\tKey: %s\n", element->key);
                printf("\tValue: %d\n", element->value);
                printf("\tElement Pointer: %p\n", element);
                printf("\tPrev pointer: %p\n", element->prev);
                printf("\tNext pointer: %p\n\n", element->next);
            }
        }
    }

    printf("DUMP COMPLETE.\n\n");
}