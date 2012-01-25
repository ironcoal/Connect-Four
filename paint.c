#include "paint.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void paint_board_empty(int board[][3]) {
   
    int i, j;
    char *strar[9];
    char numb[9];
    
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            printf("feld: %i\n", board[i][j]);
    
    for (i = 0; i < 9; i++)
        strar[i] = calloc(9, sizeof(char));
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            
            switch(board[i][j]) {
                
                case PLAYER:
                    strar[(3 * i) + j] = "X";
                    break;
                
                case COMPUTER:
                    strar[(3 * i) + j] = "C";
                    break;
                
                case EMPTY:
                    strar[(3 * i) + j] = "0";
                    break;
                
                default:
                    sprintf(numb, "%d", board[i][j]);
                    strar[(3 * i) + j] = numb;
                    break;
            }
            printf("vorher: %i: %s\n", (3 * i) + j, strar[(3 * i) + j]);
            printf("0: %s\n", strar[0]);
        }
    }
    for (i = 0; i < 9; i++)
        printf("nachher: %i: %s\n", i, strar[i]);

    getchar();
    paint_board(strar);
}

void paint_board(char *par[9]) {
    
    system("cls");
    printf(
    "-----------------------\n"
    "|   TIC - TAC - TOE   |\n"
    "-----------------------\n\n\n"
    "----------------       X = Player\n"                        
    "|  %s |  %s |  %s |       C = Computer\n"                        
    "----------------\n"        
    "|  %s |  %s |  %s |       1   2   3\n"        
    "----------------       4   5   6\n"                        
    "|  %s |  %s |  %s |       7   8   9\n"
    "----------------\n\n"
    , par[0], par[1], par[2], 
    par[3], par[4], par[5], 
    par[6], par[7], par[8]);
}

void paint_smiley(int look) {
    printf(
    "   _______\n"
    "  /       \\\n"
    " /  O   O  \\\n"
    "|           |\n"
    " \\  %s  /\n"
    "  \\_______/\n\n"
    , ((look > -1) ? ((look > 0) ? "\\___/" : "-----") : "/---\\"));
}