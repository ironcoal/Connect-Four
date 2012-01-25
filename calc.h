#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

int status(double board[][3], int pl);
int calc_move(double board[][3], int player);
int next_move(double board[][3], int player);
int other(int pl);
void zero_all_empty(double board[][3]);
int add_all_unoccupied(double board[][3]);
double* getempty(double board[][3]);
void empty_all_unoccupied(double board[][3]);
void copy_board(double old[][3], double copy[][3]);
void set_difficulty(int number);

#endif