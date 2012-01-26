#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "game.h"
#include "calc.h"

int main(void) {
    
    int i = 0;
    char input;
    system("cls");
    puts("Welcome to TicTacToe 0.5!");
    
    while (1) {
        puts("To start a new game, press \"n\", to "
        "exit, press \"e\"!");
       
        /* New game or exit? */
        input = check_input_char("ne");

        /* Exit on command */
        if (input == 'e')
            return 0;
        
        /* Set difficulty */
        puts("Choose the difficulty! [1-5]");
        input = check_input_char("12345");
        set_difficulty(input - '0');
        
        /* Choose player */
        puts("Do you want to begin [y, n]?");
        input = check_input_char("yn");
        
        /* Start game as chosen player */
        new_game(input);
        printf("\n\n");
    }
    return 0;
}


     
        