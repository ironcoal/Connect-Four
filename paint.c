#include "paint.h"

void paint_board(int board[][COL], char choice) {
   
    int i, j;
    char*** strar;

    strar = malloc(ROW * sizeof(char*));
    for (i = 0; i < ROW; i++)
        strar[i] = malloc(COL * sizeof(char*));
    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            strar[i][j] = malloc(15 * sizeof(char));
    
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            
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
                        sprintf(strar[i][j], "%d", -1);
                        tests("davor", 2);
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

void paint(char*** p) {
    int r, c;
    printf(
    "     ----------------------\n"
    "     |    CONNECT FOUR    |\n"
    "     ----------------------\n\n\n");
    printf("\n   -----------------------------\n");
    for (r = 0; r < ROW; r++) {
        printf("   |");
        for (c = 0; c < COL; c++) {
            printf("%2s |", p[r][c]);
        }
        printf("\n   -----------------------------\n");
    }
    getchar();
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