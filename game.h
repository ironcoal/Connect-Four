#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

    void new_game(char choice);
    void move_player(int board[][COL]);
    int* getfield(int number, int board[][COL]);
    int field_number(int i, int j);
    void mark_highest_random(int board[][COL], int player);

#endif