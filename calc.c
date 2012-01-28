#include "alllib.h"

int looseReturn = -1;
int winReturn = 1;

/* Returns field which has to be taken, 
the player who has won, draw, or NULL*/

int calc_move(int board[][COL], int player, int turn) {
    int stat;
    int temp;
    int *empty;
    int copy[7][7];
        
    /* Can player(computer) win with next move? */
    stat = status(board, other(player));
    if (stat > 0) {
        if (player == turn)
            return winReturn;
        else
            return looseReturn;
    }
    /* Is there only one choice for next move? */
    stat = status(board, player);
    if (stat > 0) {
        copy_board(board, copy);
        *getfield(stat, board) = player;
        empty_all_unoccupied(board);       
        temp = calc_move(board, other(player), turn);
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
        temp = calc_move(board, other(player), turn);
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
int next_move(int board[][COL], int turn) {
    int stat = status(board, turn);
    int* empty;
    int temp;
    int copy[7][7];
    empty_all_unoccupied(board);
    
    /* Has somebody won in this situation? */
    if (stat <= EMPTY)
        return stat;
        
    /* Can player(computer) win in 1 turn? */
    stat = status(board, other(turn));
    if (stat > 0) {
        zero_all_empty(board);
        *getfield(stat, board) = 1;
        return RUNNING;
    }
    
    /* Is there only one choice for next move? */
    stat = status(board, turn);
    if (stat > 0) {
        zero_all_empty(board);
        *getfield(stat, board) = 1;
        return RUNNING;
    }
    
    /* Fill all empty fields with return value of calc_next */
    while ((empty = getempty(board)) != NULL) {
        copy_board(board, copy);
        empty_all_unoccupied(board);
        *empty = turn;
        temp = calc_move(board, other(turn), turn);
        empty_all_unoccupied(board);
        copy_board(copy, board);
        *empty = temp;

    }
   
    return RUNNING;
}

/* Set difficulty of PC */
void set_difficulty(int number) {
    looseReturn = (-1) * number * 2;
    winReturn = 10 / number;
}

/* Copy content of the two boards */
void copy_board(int old[][3], int copy[][3]) {
    int i,j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
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
void zero_all_empty(int board[][COL]) {
    int i,j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            if (board[i][j] == EMPTY)
                board[i][j] = 0;
}

int add_all_unoccupied(int board[][COL]) {
    int i,j;
    int sum = 0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            if ((board[i][j] != PLAYER) && (board[i][j] != COMPUTER)) {
                sum += board[i][j];
                board[i][j] = EMPTY;
            }
    return sum;
}

void empty_all_unoccupied(int board[][COL]) {
    int i,j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            if ((board[i][j] != PLAYER) && (board[i][j] != COMPUTER))
                board[i][j] = EMPTY;
}

/* Return pointer to the next empty field, counted from
top left to bottom right */
int* getempty(int board[][COL]) {
    int i,j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            if (board[i][j] == EMPTY)
                return &board[i][j];
    return NULL;
}    