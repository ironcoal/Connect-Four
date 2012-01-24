#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

    #define RUNNING 1
    #define EMPTY -10000
	#define PLAYER (EMPTY - 1)
    #define COMPUTER (EMPTY - 2)
    #define DRAW 0

    void new_game(char choice);
    void move_player(double board[][3]);
    double* getfield(int number, double board[][3]);
    int field_number(int i, int j);
    void mark_highest(double board[][3], int player);
    void mark_highest_random(double board[][3], int player);

#endif