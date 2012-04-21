#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

    #include "alllib.h"
    void new_game(char choice);
    void move_player(int board[][COL]);
    void mark_highest_random(int board[][COL], int player);
    void tests(const char * str, int i);

#endif