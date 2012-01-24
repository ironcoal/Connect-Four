#include "paint.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void paint_board(char par[][3]) {
    
    system("cls");
    printf(
    "-----------------------\n"
    "|   TIC - TAC - TOE   |\n"
    "-----------------------\n\n\n"
	"----------------       X = Player\n"						
	"|  %c |  %c |  %c |       C = Computer\n"						
	"----------------\n"		
	"|  %c |  %c |  %c |       1   2   3\n"		
	"----------------       4   5   6\n"						
	"|  %c |  %c |  %c |       7   8   9\n"
	"----------------\n\n"
	, par[0][0], par[0][1], par[0][2], 
	par[1][0], par[1][1], par[1][2], 
	par[2][0], par[2][1], par[2][2]);
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