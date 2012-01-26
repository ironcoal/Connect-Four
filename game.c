#include "game.h"
#include "input.h"
#include <stdio.h>
#include "paint.h"
#include "calc.h"
#include <stdlib.h>
#include <time.h>

void new_game(char choice) {
    
    /* The board */
    int board[3][3];
    
    int i,j;
    int stat;
    int won;

    /* Clear new board */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            board[i][j] = EMPTY;
    
    /* If player chose to start ("yes"), let him "move" first */
    if (choice == 'y')
        move_player(board);
    
    /* nex_move fills the board with numbers which show
    the chance of winning */
    while ((stat = next_move(board, COMPUTER)) == RUNNING) {

        /* PC takes one of the fields with the highest number */
        mark_highest_random(board, COMPUTER);
        
        /* Has the above move of the PC changed the "winning-status"? */
        won = status(board, COMPUTER);
        if ((won == COMPUTER) || (won == PLAYER) || (won == DRAW)) {
            stat = won;
            break;
        }
                     
        /* Players turn */
        move_player(board);
    }
    
    /* Shows the final result of the game */
    paint_board(board,'e');
    if (stat == PLAYER) {
        puts("\nCongratulations! You have won!");
        paint_smiley(1);
    } 
    else
        if (stat == COMPUTER) {
            puts("\nSry, Computer wins. Maybe next time!");
            paint_smiley(-1);
        }
        else {
            puts("Draw!");
            paint_smiley(0);
        }
}

void move_player(int board[][3]) {
    
    char inp;

    paint_board(board,'e');
    empty_all_unoccupied(board);
    
    /* Clear the board of all numbers */
    while (1) {
        printf("\nPlease enter the number of an empty field! (h for hint)\n");
        inp = check_input_char("123456789h");
        if (inp == 'h') {
            next_move(board, PLAYER);
            mark_highest_random(board, HINT);
            paint_board(board,'e');
            empty_all_unoccupied(board);
        } else if (*getfield((int) inp - '0', board) == EMPTY) {
            *getfield((int) inp - '0', board) = PLAYER;
            break;
        } else {
            printf("Field is already taken\n");
        }
    }
}

void mark_highest_random(int board[][3], int sign) {
    
    int i,j;
    int highest = EMPTY + 1;
    int randint;
    
    /* Get highest number */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (board[i][j] > highest)
                highest = board[i][j];
                                
    /* Mark random field with highest number */
    
    /* Set Seed */
    srand(time(NULL));
    
    /* Get random field-number. If field has highest 
    number, mark with player */
    do
    randint = (rand() % 9) + 1;
    while (*getfield(randint, board) != highest);
    
    *getfield(randint, board) = sign;
}

/* The board is numbered after the following sheme:
    1 2 3
    4 5 6
    7 8 9
    The function returns a pointer connected to the entered number */

int *getfield(int number, int board[][3]) {
    if ((number >= 1) && (number <= 9))
        return &board[number / 3][(number % 3) - 1];
    else
        return NULL;
}

/* Returns the fieldnumber connected to the matrix-adress */
int field_number(int i, int j) {
    return (i * 3) + (j + 1);
}
