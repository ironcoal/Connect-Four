#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

int status(int board[][3], int pl);
int calc_move(int board[][3], int player);
int next_move(int board[][3], int player);
int other(int pl);
void zero_all_empty(int board[][3]);
int add_all_unoccupied(int board[][3]);
int* getempty(int board[][3]);
void empty_all_unoccupied(int board[][3]);
void copy_board(int old[][3], int copy[][3]);
void set_difficulty(int number);

#endif