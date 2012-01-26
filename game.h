#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

    #define EMPTY -10000
    #define PLAYER (EMPTY - 1)
    #define COMPUTER (EMPTY - 2)
    #define DRAW (EMPTY - 3)
    #define RUNNING (EMPTY - 4)
    #define HINT (EMPTY - 5)

    void new_game(char choice);
    void move_player(int board[][3]);
    int* getfield(int number, int board[][3]);
    int field_number(int i, int j);
    void mark_highest_random(int board[][3], int player);
    void show_highest(int board[][3]);

#endif