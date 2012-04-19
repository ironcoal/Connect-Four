#include "alllib.h"

void new_game(char choice) {
    
    /* The board */
    int board[ROW][COL];
    
    int r, c;
    int stat;
    int *won;

    /* Clear new board */
    for (r = 0; r < ROW; r++)
        for (c = 0; c < COL; c++)
            board[r][c] = EMPTY;
    
    /* If player chose to start ("yes"), let him "move" first */
    if (choice == 'y')
        move_player(board);
    
    /* nex_move fills the board with numbers which show
    the chance of winning */
    while ((stat = next_move(board, COMPUTER)) == RUNNING) {
        
        /* PC takes one of the fields with the highest number */
        mark_highest_random(board, COMPUTER);
        
        /* Has the above move of the PC changed the "winning-status"? */
        won = is_finished(board);

        if ((*won == COMPUTER) || (*won == PLAYER) || (*won == DRAW)) {
            break;
        }
                     
        /* Players turn */
        move_player(board);
    }
    
    /* Shows the final result of the game */
    paint_board(board,'e');
    if (stat == PLAYER) {
        puts("\nCongratulations! You have won!");
        paint_smiley(1);
    } 
    else
        if (stat == COMPUTER) {
            puts("\nComputer wins. Maybe next time!");
            paint_smiley(-1);
        }
        else {
            puts("Draw!");
            paint_smiley(0);
        }
}

void move_player(int board[][COL]) {
    
    char inp;

    paint_board(board,'e');
    empty_all_unoccupied(board);
    
    /* Clear the board of all numbers */
    while (1) {
        printf("\nPlease enter the number of an empty row! (h for hint)\n");
        inp = check_input_char("1234567h");
        if (inp == 'h') {
            next_move(board, PLAYER);
            mark_highest_random(board, HINT);
            paint_board(board,'e');
            empty_all_unoccupied(board);
        } else if (get_top(board, inp - '0') != -1) {
            board[get_top(board, inp - '0' - 1)][inp - '0' - 1] = PLAYER;
            break;
        } else {
            printf("Row is full!");
        }
    }
}

void mark_highest_random(int board[][COL], int sign) {
    
    int r, c;
    int highest = EMPTY + 1;
    int randint;
    
    /* Get highest number */
    for (r = 0; r < ROW; r++)
        for (c = 0; c < COL; c++)
            if (board[r][c] > highest)
                highest = board[r][c];
                                
    /* Mark random field with highest number */
    
    /* Set Seed */
    srand(time(NULL));
    
    /* Get random field-number. If field has highest 
    number, mark with player */
    do
    randint = (rand() % ROW) + 1;
    while (board[get_top(board, randint)][randint] != highest);
    
    board[get_top(board, randint)][randint] = sign;
}

void tests(const char * str) {
    printf("%s", str);
    getchar();
}
void testi(int i) {
    printf("%i", i);
    getchar();
}