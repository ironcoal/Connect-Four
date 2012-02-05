#include "input.h"

void clearbuf(void);
char check_input_char(char* allowed);

void clearbuf(void) {
    while (getchar() != '\n')
        ;
}

/* Reads a char which is part of the string passed */
char check_input_char(char *allowed) {
    char inp;
    int i;
    
    while (1) {
        inp = getchar();
        clearbuf();
        for (i = 0; allowed[i] != 0; i++)
            if (inp == allowed[i])
                return inp;
        printf("Input not allowed. Please enter one of"
        "the following letters: %s\n", allowed);      
    }
}