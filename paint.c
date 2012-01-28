#include "paint.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void paint_board(int board[][3], char choice) {
   
    int i, j;
    char*** strar;
    
    strar = malloc(9 * sizeof(char*));
    for (i = 0; i < 9; i++)
        strar[i] = malloc(15 * sizeof(char*));
    for (i = 0; i < 9; i++)
        strar[i][i] = malloc(15 * sizeof(char));
    
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            
            switch(board[i][j]) {
                
                case PLAYER:
                    strar[i][j] = "X";
                    break;
                
                case COMPUTER:
                    strar[i][j] = "C";
                    break;
                
                case EMPTY:
                    if (choice == 'n')
                        strar[i][j] = "0";
                    else 
                        strar[i][j] = " ";
                    break;
                    
                case HINT:
                        strar[i][j] = "+";
                    break;
                
                default:
                    if (choice == 'n') {
                        sprintf(strar[i][j], "%d", board[i][j]);
                    } else                       
                        strar[i][j] = " ";
                    break;
            }
        }
    }
    
    paint(strar);
    free(strar);
}

void paint(char ***p) {
    
    system("cls");
    printf(
    "-----------------------\n"
    "|   CONNECT FOUR   |\n"
    "-----------------------\n\n\n"
    "----------------------------\n     X = Player\n"                        
    "|%4s|%4s|%4s|%4s|%4s|%4s|%4s|      C = Computer\n"                        
    "----------------------------\n"
    "|%4s|%4s|%4s|%4s|%4s|%4s|%4s|"        
    "----------------------------\n"        
    "|%4s|%4s|%4s|%4s|%4s|%4s|%4s|"    
    "----------------------------\n"        
    "|%4s|%4s|%4s|%4s|%4s|%4s|%4s|"
    "----------------------------\n"
    "|%4s|%4s|%4s|%4s|%4s|%4s|%4s|"
    "----------------------------\n"     
    "|%4s|%4s|%4s|%4s|%4s|%4s|%4s|"
    "----------------------------\n"    
    "|%4s|%4s|%4s|%4s|%4s|%4s|%4s|", 
    p[0][0], p[0][1], p[0][2], p[0][3], p[0][4], p[0][5], p[0][6],
    p[1][0], p[1][1], p[1][2], p[1][3], p[1][4], p[1][5], p[1][6],
    p[2][0], p[2][1], p[2][2], p[2][3], p[2][4], p[2][5], p[2][6],
    p[3][0], p[3][1], p[3][2], p[3][3], p[3][4], p[3][5], p[3][6],
    p[4][0], p[4][1], p[4][2], p[4][3], p[4][4], p[4][5], p[4][6],
    p[5][0], p[5][1], p[5][2], p[5][3], p[5][4], p[5][5], p[5][6],
    p[6][0], p[6][1], p[6][2], p[6][3], p[6][4], p[6][5], p[6][6],
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