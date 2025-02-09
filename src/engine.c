#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <FEN> <possible_moves> <time_limit>\n", argv[0]);
        return 1;
    }

    int i, j;

    char chess_board[8][8];
    char *FEN = argv[1];
    int row = 0;
    int column = 0;

    while (*FEN != ' ' && *FEN != '\0') {
        if (*FEN == '/') {
            column = 0;
            row++;
            FEN++;
            continue;
        }

        if (row >= 8 || column >= 8) {
            fprintf(stderr, "Invalid FEN\n");
            return 1;
        }

        if (*FEN >= '0' && *FEN <= '8') {
            for (i = column; i < column + (*FEN - '0'); i++) {
                if (i >= 8) {
                    fprintf(stderr, "Invalid FEN\n");
                    return 1;
                }
                chess_board[row][i] = '0';
            }
            column = i;
            FEN++;
            continue;
        }

        chess_board[row][column] = *FEN;
        column++;
        FEN++;
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%c\t", chess_board[i][j]);
        }
        printf("\n");
    }

    return 0;
}