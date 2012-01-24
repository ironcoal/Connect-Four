#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

    #define RUNNING -2
    #define PLAYER -10000
    #define COMPUTER -10001
    #define EMPTY -10002
	#define DRAW -7

    void new_game(char choice);
    void move_player(double board[][3]);
    double* getfield(int number, double board[][3]);
    int field_number(int i, int j);
    void mark_highest(double board[][3], int player);
    void mark_highest_random(double board[][3], int player);

#endif