#ifndef ANALYSE_H_INCLUDED
#define ANALYSE_H_INCLUDED
    
    #include "alllib.h"
    int *is_danger(int board[][COL], int pl);
    int is_finished(int board[][COL]);
    int *check_row(int board[][COL], int player);
    int *check_column(int board[][COL], int player);
    int is_top(int board[][COL], int row, int column);
    int get_top(int board[][COL], int column);
    int *check_diagonal_down(int board[][COL], int player);
    int *check_diagonal_up(int board[][COL], int player);
    int four_row(int board[][COL]);
    int four_col(int board[][COL]);
	int four_dup(int board[][COL]);
	int four_ddn(int board[][COL]);


#endif