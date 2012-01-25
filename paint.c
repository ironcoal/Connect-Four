#include "paint.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void paint_board_empty(double board[][3]) {
   
	int i, j;
    char *strar[9];
    char numb[9];
	
	for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            switch(board[i][j]) {
                
                case PLAYER:
                strar[i * j] = "X";
                break;
                
                case COMPUTER:
                strar[i * j] = "C";
                break;
                
                case EMPTY:
                strar[i * j] = "0";
                break;
                
                default:
                sprintf(numb,"%d",board[i][j]);
                strar[i * j] = numb;
            }
	}
	paint_board(strar);
}

void paint_board(char** par) {
    
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

void paint_board_old(double board[][3]) {
    int i;
    int j;
    printf("\n");
    puts("Gewichtung, bevor Computer setzt!");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == PLAYER) {
                printf("%8c", 'X');
            } else {
                if (board[i][j] == COMPUTER) {
                    printf("%8c", 'C');
                } else {
                    printf("%8.f", board[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n\n");
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