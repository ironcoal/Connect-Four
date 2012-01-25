#include "calc.h"
#include "game.h"
#include "paint.h"
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

int diff_player = -1;
int diff_pc = 1;

/* Returns field which has to be taken, 
the player who has won, draw, or NULL*/
int status(int board[][3], int pl) {
    
    int won, count;
    int temp = 0;
    int i, j, z;
    int otherpl = other(pl);
    int copy[3][3];
    
    /* Check in rows */
    for (i = 0; i < 3; i++) {
        count = 0;
        won = 0;
        for (j = 0; j < 3; j++) {
            if (board[i][j] == otherpl)
                count++;
            if (board[i][j] == pl)
                won++;    
        }
        if (won == 3)
            return pl;
        if (count == 3)
            return otherpl;
        if (count == 2)
            for (z = 0; z < j; z++)
                if ((board[i][z] != pl) && (board[i][z] != otherpl))
                    temp = field_number(i,z);
    }
    if (temp != 0) 
        return temp;
        
    /* Check in columns */
    for (i = 0; i < 3; i++) {
        won = 0;
        count = 0;
        for (j = 0; j < 3; j++) {
            if (board[j][i] == otherpl)
                count++;
            if (board[j][i] == pl)
                won++;    
        }
        if (won == 3)
            return pl;
        if (count == 3)
            return otherpl;
        if (count == 2)
            for (z = 0; z < j; z++)
                if ((board[z][i] != pl) && (board[z][i] != otherpl))
                    temp = field_number(z,i);
    }
    if (temp != 0)
        return temp;

    /* Check diagonal down */
    count = 0;
    won = 0;
    for (i = 0; i < 3; i++) {
        if (board[i][i] == otherpl)
            count++;
        if (board[i][i] == pl)
            won++;    
    }
    if (won == 3)
        return pl;
    if (count == 3)
        return otherpl;
    if (count == 2)
        for (i = 0; i < 3; i++)
            if ((board[i][i] != pl) && (board[i][i] != otherpl))
                return field_number(i,i);
    
    /* Check diagonal up */
    count = 0;
    won = 0;
    for (i = 0, j = 2; i < 3; i++, j--) {
        if (board[j][i] == otherpl)
            count++;
        if (board[j][i] == pl)
            won++;    
        }
    if (won == 3)
        return pl;
    if (count == 3)
        return otherpl;
    if (count == 2)
        for (i = 0, j = 2; i < 3; i++, j--)
            if ((board[j][i] != pl) && (board[j][i] != otherpl))
                return field_number(j,i);
    
    /* draw? */
    copy_board(board, copy);
    empty_all_unoccupied(board);
    if (getempty(board) == NULL) {
        copy_board(copy, board);
        return DRAW;
    }
    copy_board(copy, board);
    
    /* Nothing of the above: free choice! */
    return 0;
}

int calc_move(int board[][3], int player) {
    int stat;
    int temp;
    int *empty;
    int copy[3][3];
        
    /* Can player(computer) win with next move? */
    stat = status(board, other(player));
    if (stat > 0) {
        if (player == COMPUTER)
            return diff_pc;
        else
        if (player == PLAYER)
            return diff_player;
    }
    /* Is there only one choice for next move? */
    stat = status(board, player);
    if (stat > 0) {
        copy_board(board, copy);
        *getfield(stat, board) = player;
        empty_all_unoccupied(board);       
        temp = calc_move(board, other(player));
        copy_board(copy, board);
        return temp;
    }
    
    /* Else get first empty field, fill it with player 
    and call function calc_move recursiv */
    
    copy_board(board, copy);
    while ((empty = getempty(board)) != NULL) {
        copy_board(board, copy);
        *empty = player;
        empty_all_unoccupied(board); 
        temp = calc_move(board, other(player));
        copy_board(copy, board);
        *empty = temp;
    }

    temp = add_all_unoccupied(board);
    copy_board(copy, board);
    
    
    return temp;
}   

/* Almost identical to the above "main" calc-function... 
but it saves the calculatet numbers on the board, so the 
PC can later choose the highest */
int next_move(int board[][3], int player) {
    int stat = status(board, player);
    int* empty;
    int temp;
    int copy[3][3];
    empty_all_unoccupied(board);
    
    /* Has somebody won in this situation? */
    if (stat <= EMPTY)
        return stat;
        
    /* Can player(computer) win in 1 turn? */
    stat = status(board, other(player));
    if (stat > 0) {
        zero_all_empty(board);
        *getfield(stat, board) = 1;
        return RUNNING;
    }
    
    /* Is there only one choice for next move? */
    stat = status(board, player);
    if (stat > 0) {
        zero_all_empty(board);
        *getfield(stat, board) = 1;
        return RUNNING;
    }
    
    /* Fill all empty fields with return value of calc_next */
    while ((empty = getempty(board)) != NULL) {
        copy_board(board, copy);
        empty_all_unoccupied(board);
        *empty = player;
        temp = calc_move(board, other(player));
        empty_all_unoccupied(board);
        copy_board(copy, board);
        *empty = temp;

    }
   
    return RUNNING;
}

/* Set difficulty of PC */
void set_difficulty(int number) {
    diff_player = (-1) * number * 2;
    diff_pc = 10 / number;
}

/* Copy content of the two boards */
void copy_board(int old[][3], int copy[][3]) {
    int i,j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            copy[i][j] = old[i][j];
}

/* Give other player */
int other(int pl) {
    if (pl == PLAYER)
        return COMPUTER;
    else
        return PLAYER;
}

/* Set all empty fields to zero. Useful if there
is only one reasonable choice for the PC */
void zero_all_empty(int board[][3]) {
    int i,j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                board[i][j] = 0;
}

int add_all_unoccupied(int board[][3]) {
    int i,j;
    int sum = 0;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if ((board[i][j] != PLAYER) && (board[i][j] != COMPUTER)) {
                sum += board[i][j];
                board[i][j] = EMPTY;
            }
    return sum;
}

void empty_all_unoccupied(int board[][3]) {
    int i,j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if ((board[i][j] != PLAYER) && (board[i][j] != COMPUTER))
                board[i][j] = EMPTY;
}

/* Return pointer to the next empty field, counted from
top left to bottom right */
int* getempty(int board[][3]) {
    int i,j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return &board[i][j];
    return NULL;
}    