#include "analyse.h"

int is_finished(int board[][COL]) 
{
    int p;
    
    if ((p = four_row(board)) != 0)
        return p;
    if ((p = four_col(board)) != 0)
        return p;
    if ((p = four_ddn(board)) != 0)
        return p;
    if ((p = four_dup(board)) != 0)
        return p;
    
    /* No one has won... */
    return 0;
}

/* Are there four in a row? Returns winning player or 0 */
int four_row(int board[][COL]) 
{
    int r, c;
    int count;
    for (r = 0; r < ROW; r++) {

        /* Reset counter every new row */
        count = 0;   
        for (c = 0; c < COL; c++) {

            /* PC is counted upwards, player down. An empty field 
            counts in opposite direction */   
            if (board[r][c] == COMPUTER)
                count++;
            
            else if (board[r][c] == PLAYER) 
                count--;
            
            else if (board[r][c] >= EMPTY)
                if (count > 0)
                    count--;
                else if (count < 0)
                    count++;


            /* Has PC or player won? */
            if (count >= 4)
                return COMPUTER;
            else if (count <= -4)
                return PLAYER;
        }
    }

    /* Nobody has won! */
    return 0;
}

/* Are there four in a column? Returns winning player or 0 */
int four_col(int board[][COL]) 
{
    int r, c;
    int count;
    for (c = 0; c < COL; c++) {
        
        /* Reset counter every new column */
        count = 0;   
        for (r = 0; r < ROW; r++) {

            /* PC is counted upwards, player down. An empty field 
            counts in opposite direction */   
            if (board[r][c] == COMPUTER)
                count++;
            
            else if (board[r][c] == PLAYER) 
                count--;

            else if (board[r][c] >= EMPTY)
                if (count > 0)
                    count--;
                else if (count < 0)
                    count++;

            /* Has PC or player won? */
            if (count >= 4)
                return COMPUTER;
            else if (count <= -4)
                return PLAYER;
        }
    }

    /* Nobody has won! */
    return 0;
}

/* Are there four diagonally up? Returns winning player or 0 */
int four_dup(int board[][COL])
{
    int r, c, z;
    int count;
    for (c = 0; c < (COL - 4); c++) {
        for (r = 3; r < ROW; r++) {
            count = 0;
            for (z = 0; z <= 3; z++) {

            if (board[r - z][c + z] == COMPUTER)
                count++;
            
            else if (board[r - z][c + z] == PLAYER) 
                count--;

            else if (board[r - z][c + z] >= EMPTY)
                if (count > 0)
                    count--;
                else if (count < 0)
                    count++;
            }

            /* Has PC or player won? */
            if (count >= 4)
                return COMPUTER;
            else if (count <= -4)
                return PLAYER;  
        }
    }

    /* Nobody has won! */
    return 0;        
}

/* Are there four diagonally down? Returns winning player or 0 */
int four_ddn(int board[][COL])
{
    int r, c, z;
    int count;
    for (c = COL - 1; c >= 3; c--) {        
        for (r = 3; r < ROW; r++) {
            count = 0;
            for (z = 0; z <= 3; z++) {

            if (board[r - z][c - z] == COMPUTER)
                count++;
            
            else if (board[r - z][c - z] == PLAYER) 
                count--;

            else if (board[r - z][c - z] >= EMPTY)
                if (count > 0)
                    count--;
                else if (count < 0)
                    count++;
            }

            /* Has PC or player won? */
            if (count >= 4)
                return COMPUTER;
            else if (count <= -4)
                return PLAYER;  
        }
    }

    /* Nobody has won! */
    return 0;        
}

int *is_danger(int board[][COL], int pl)
{
    int *p;
    if ((p = check_row(board, pl)) != NULL) {
        return p;
    }    
    if ((p = check_column(board, pl)) != NULL) {
        return p;
    }   
     if ((p = check_diagonal_up(board, pl)) != NULL) {
        return p;
    }
    if ((p = check_diagonal_down(board, pl)) != NULL) {
        return p;
    }
    /* Nothing in danger ;) */
    return NULL;
}

/* Function checks if other player has 3 in a row. 
If true, pointer to field is returned, otherwise NULL */
int *check_row(int board[][COL], int player) 
{
    int r, c, z;
    int count;
    for (r = 0; r < ROW; r++) {
        for (c = 0; c < (COL - 3); c++) {
            count = 0;           
            for (z = 0; z <= 3; z++) {
                /* Count tokens of player */
                if (board[r][z + c] == other(player)) {
                    count++;
                }
                /* If other player is in that section or you can't set there, count negativ */
                else if ((board[r][z + c] == player) || !(is_top(board, r , z + c)))  {
                    count--;
                }
            }
            /* If there are three in a row, return empty field */
            if (count == 3)
                for (z = 0; z <= 3; z++)
                    if (board[r][z + c] == EMPTY) {
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
            return &board[get_top(board, c)][c];  
        }
    }

    /* No danger in any column for player */
    return NULL;
}

int *check_diagonal_up(int board[][COL], int player)
{
    int r, c, z;
    int count;
    for (c = 0; c < (COL - 4); c++) {
        
        for (r = 3; r < ROW; r++) {
            count = 0;  

            for (z = 0; z <= 3; z++) {

            if (board[r - z][c + z] == other(player))
                count++;
            
            else if ((board[r - z][c + z] == player) || !(is_top(board, r - z, c + z)))
                count--;

            if (count == 3)
                for (z = 0; z <= 3; z++)
                    if (board[r - z][c + z] == EMPTY) {
                        return &board[r - z][c + z];
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
    for (c = COL - 1; c >= 3; c--) {        
        for (r = 3; r < ROW; r++) {
            count = 0;
            for (z = 0; z <= 3; z++) {

            if (board[r - z][c - z] == other(player)) {
                count++;
            }
            else if ((board[r - z][c - z] == player) || !(is_top(board, r - z, c - z)))
                count--;

            if (count == 3)
                for (z = 0; z <= 3; z++)
                    if (board[r - z][c - z] == EMPTY) {
                        return &board[r - z][c - z];
                    }
            }
        }
    }
    return NULL;
}