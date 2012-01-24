#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "game.h"

int main(void) {
    
    char input;
    system("cls");
    puts("Welcome to TicTacToe 0.5!");
    
    for (;;) {
        puts("To start a new game, press \"n\", to "
        "exit, press \"e\"!");
       
        /* New game or exit? */
        input = check_input_char("ne");

        /* Exit on command */
        if (input == 'e')
            return 0;
            
        /* Choose player */
        puts("Do you want to begin [y, n]?");
        input = check_input_char("yn");
        
        /* Start game as chosen player */
        new_game(input);
        printf("\n\n");
    }
    return 0;
}


     
        