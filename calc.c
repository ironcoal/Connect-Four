#include "calc.h"

int looseReturn = -1;
int winReturn = 1;

/* Returns field which has to be taken, 
the player who has won, draw, or NULL*/

int calc_move(int board[][COL], int player, int turn) {
    int *danger;
    int temp;
    int *empty;
    int copy[ROW][COL];
        
    /* Can player(computer) win with next move? */
    danger = is_finished(board);
    if (danger != NULL) {
        if (player == turn)
            return winReturn;
        else
            return looseReturn;
    }
    /* Is there only one choice for next move? */
    danger = is_danger(board, player);
    if (danger != NULL) {
        copy_board(board, copy);
        *danger = player;
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
    int *won;
    int *empty;
    int temp;
    int *danger;
    int copy[ROW][COL];
    empty_all_unoccupied(board);
    
    /* Has somebody won in this situation? */
    won = is_finished(board);
    if (won != NULL)
        return *won;
        
    /* Can player(computer) win in 1 turn? */
    danger = is_danger(board, other(turn));
    if (danger != NULL) {
        zero_all_empty(board);
        *danger = 1;
        return RUNNING;
    }
    
    /* Is there only one choice for next move? */
    danger = is_danger(board, turn);
    if (danger != NULL) {
        zero_all_empty(board);
        *danger = 1;
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
void copy_board(int old[][COL], int copy[][COL]) {
    int r, c;
    for (r = 0; r < ROW; r++)
        for (c = 0; c < COL; c++)
            copy[r][c] = old[r][c];
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
    int r, c;
    for (r = 0; r < ROW; r++)
        for (c = 0; c < COL; c++)
            if (board[r][c] == EMPTY)
                board[r][c] = 0;
}

int add_all_unoccupied(int board[][COL]) {
    int r, c;
    int sum = 0;
    for (r = 0; r < ROW; r++)
        for (c = 0; c < COL; c++)
            if ((board[r][c] != PLAYER) && (board[r][c] != COMPUTER)) {
                sum += board[r][c];
                board[r][c] = EMPTY;
            }
    return sum;
}

void empty_all_unoccupied(int board[][COL]) {
    int r, c;
    for (r = 0; r < ROW; r++)
        for (c = 0; c < COL; c++)
            if ((board[r][c] != PLAYER) && (board[r][c] != COMPUTER))
                board[r][c] = EMPTY;
}

/* Return pointer to the next empty field from the left */
int* getempty(int board[][COL]) {
    int c;
    int top;
    for (c = 0; c < COL; c++)
        if ((top = get_top(board, c)) != -1)
            return &board[top][c];
    return NULL;
}    

int is_top(int board[][COL], int row, int column) 
{
    if (board[row][column] == EMPTY) {
        /* Lowest row, or is a token under that field? */
        if ((row == ROW - 1) || (board[row + 1][column] != EMPTY))
            return 1;
    }
    return 0;
}

int get_top(int board[][COL], int column) 
{
    int r = 0;

    while (board[r][column] == EMPTY)
        r++;
        
    if (r == 0)
        return -1; /* Column is full */
    else
        return r - 1;
}