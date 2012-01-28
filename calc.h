#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

int status(int board[][COL], int pl);
int calc_move(int board[][COL], int player, int turn);
int next_move(int board[][COL], int turn);
int other(int pl);
void zero_all_empty(int board[][COL]);
int add_all_unoccupied(int board[][COL]);
int* getempty(int board[][COL]);
void empty_all_unoccupied(int board[][COL]);
void copy_board(int old[][3], int copy[][3]);
void set_difficulty(int number);

#endif