#include "paint.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void paint_board(int board[][3], char choice) {
   
    int i, j;
    char** strar;
    
    strar = malloc(9 * sizeof(char));
    for (i = 0; i < 9; i++)
        strar[i] = malloc(9 * sizeof(char));
    
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
                    if (choice == 'n')
                        strar[(3 * i) + j] = "0";
                    else 
                        strar[(3 * i) + j] = " ";
                    break;
                    
                case HINT:
                        strar[(3 * i) + j] = "h";
                    break;
                
                default:
                    if (choice == 'n') {
                        sprintf(strar[(3 * i) + j], "%d", board[i][j]);
                        printf("%i",(3 * i) + j);
                    } else                       
                        strar[(3 * i) + j] = " ";
                    break;
            }
        }
    }
    
    paint(strar);
    free(strar);
}

void paint(char **par) {
    
    system("cls");
    printf(
    "-----------------------\n"
    "|   TIC - TAC - TOE   |\n"
    "-----------------------\n\n\n"
    "----------------       X = Player\n"                        
    "|%4s|%4s|%4s|       C = Computer\n"                        
    "----------------\n"        
    "|%4s|%4s|%4s|       1   2   3\n"        
    "----------------       4   5   6\n"                        
    "|%4s|%4s|%4s|       7   8   9\n"
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