#include <stdio.h>
#include "movement.h"
#include "score.h"


int evaluate(char chess_board[8][8], char player) {
    int white_value = 0;
    int black_value = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chess_board[i][j] == '0') continue;
            switch (chess_board[i][j]) {
                case 'P':
                    white_value += 1;
                    break;
                case 'p':
                    black_value -= 1;
                    break;
                case 'R':
                    white_value += 5;
                    break;
                case 'r':
                    black_value -= 5;
                    break;
                case 'N':
                case 'B':
                    white_value += 3;
                    break;
                case 'n':
                case 'b':
                    black_value -= 3;
                    break;
                case 'Q':
                    white_value += 9;
                    break;
                case 'q':
                    black_value -= 3;
                    break;
            }
        }
    }
    int evaluation = white_value - black_value;
    int perspective = (player == 'w') ? 1 : -1;
    return evaluation * perspective;
}