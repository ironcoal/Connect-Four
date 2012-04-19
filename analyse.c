#include "analyse.h"

int *is_finished(int board[][COL]) {
    int *p;
    if (((p = check_row(board, COMPUTER)) != NULL) && (*p != EMPTY))
        return p;
    if (((p = check_row(board, PLAYER)) != NULL) && (*p != EMPTY))
        return p;
    if (((p = check_column(board, COMPUTER)) != NULL) && (*p != EMPTY))
        return p;
    if (((p = check_column(board, PLAYER)) != NULL) && (*p != EMPTY))
        return p;
    if (((p = check_diagonal_up(board, COMPUTER)) != NULL) && (*p != EMPTY))
        return p;
    if (((p = check_diagonal_up(board, PLAYER)) != NULL) && (*p != EMPTY))
        return p;
    if (((p = check_diagonal_down(board, COMPUTER)) != NULL) && (*p != EMPTY))
        return p;
    if (((p = check_diagonal_down(board, PLAYER)) != NULL) && (*p != EMPTY))
        return p;
    /* No one has won... */
    return NULL;
}

int *is_danger(int board[][COL], int pl)
{
    int *p;
    if (((p = check_row(board, pl)) != NULL) && (*p == EMPTY))
        return p;
    if (((p = check_column(board, pl)) != NULL) && (*p == EMPTY))
        return p;
    if (((p = check_diagonal_up(board, pl)) != NULL) && (*p == EMPTY))
        return p;
    if (((p = check_diagonal_down(board, pl)) != NULL) && (*p == EMPTY))
        return p;
    /* Nothing in danger ;) */
    return NULL;
}

/* Function checks, if other player has 3 in row. 
If true, pointer to field is returned */
int *check_row(int board[][COL], int player) 
{
    int r, c, z;
    int count;
    for (r = 0; r < ROW; r++) {
        for (c = 0; c < (COL - 3); c++) {
            count = 0;           
            for (z = 0; z <= 3; z++) {
                /* Count tokens of player */
                if (board[r][z + c] == other(player))
                    count++;
                /* If othere player is in that section or you can't set there, count negativ */
                else if ((board[r][z + c] == player) || !(is_top(board, r , z + c)))
                    count--;
            }
            /* If there are three in a row, return empty field */
            if (count == 3)
                for (z = 0; z < 4; z++)
                    if (board[r][z + c] == EMPTY) {
                        tests("row, 3");
                        return &board[r][z + c];
                    }
            if (count == 4)
                for (z = 0; z < 4; z++)
                    if (board[r][z + c] == EMPTY) {
                        tests("row, 4");
                        printf("\nr%i, c%i, z%i", r, c, z);
                        return &board[r][z + c];
                    }
        }
    }
    /* No danger in any row for player */
    return NULL;
}

int *check_column(int board[][COL], int player) 
{
    int c, r;
    int count;
    int top;
    
    for (c = 0; c < COL; c++) {
        count = 0;
        if (((top = get_top(board, c)) != -1) && (top < (ROW - 3)))
            for (r = 1; r < 4; r++)
                if (board[top + r][c] == other(player))
                    count++;
        if (count == 3) {
            tests("col, 3");
            return &board[get_top(board, c)][c];  
        }
        if (count == 4) {
            tests("col, 4");
            printf("\nr%i, c%i", r, c);
            getchar();
            return &board[get_top(board, c) - 1][c];
        }
    }
    /* No danger in any column for player */
    return NULL;
}

int *check_diagonal_up(int board[][COL], int player)
{
    int r, c, z;
    int count;
    for (c = 0; c < (COL - 3); c++) {
        for (r = 0; r < (ROW - 3); r++) {
            count = 0;
            if (board[r][c] == other(player)) {
                count = 1;
                for (z = 1; z <= 3; z++) {
                    if (board[r + z][c + z] == other(player)) {
                        count++;
                    }
                    else if ((board[r + z][c + z] == player) || !(is_top(board, r + z, c + z)))
                        if (count == 4)
                            tests("halt 4");
                        count--;
                }
            }
            if (count == 3)
                for (z = 1; z <= 3; z++)
                    if (board[r + z][c + z] == EMPTY) {
                        tests("du, 3");
                        return &board[r + z][c + z];
                    }
            if (count == 4) {
                printf("\nr%i, c%i", r, c);
                for (z = 1; z <= 3; z++)
                    if (board[r + z][c + z] != EMPTY) {
                        tests("du, 4");
                        getchar();
                        return &board[r + z][c + z];
                    }
            }
        }
    }
    return NULL;
}

/* Same as up, but other way around:) */
int *check_diagonal_down(int board[][COL], int player)
{
    int r, c, z;
    int count;
    for (c = COL; c > 3; c--) {
        for (r = 0; r < (ROW - 3); r++) {
            count = 0;
            if (board[r][c] == other(player)) {
                count = 1;
                for (z = 1; z <= 3; z++) {
                    if (board[r + z][c - z] == other(player))
                        count++;
                    else if ((board[r + z][c - z] == player) || !(is_top(board, r + z, c - z)))
                        count--;
                }
            }
            if (count == 3)
                for (z = 1; z <= 3; z++)
                    if (board[r + z][c - z] == EMPTY) {
                        tests("dd, 3");
                        return &board[r + z][c - z];
                    }
            if (count == 4) {
            printf("\nr%i, c%i", r, c);
                for (z = 1; z <= 3; z++)
                    if (board[r + z][c - z] != EMPTY) {
                        tests("dd, 4");
                        getchar();
                        return &board[r + z][c - z];
                    }
            }
        }
    }
    return NULL;
}