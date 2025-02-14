#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "extra.h"


int generate_index(char *fen, char *moves) {
    int i;

    char chess_board[8][8];
    char best_move[9];
    int check = 0;
    int row = 0;
    int column = 0;

    while (*fen != ' ') {
        if (*fen == '/') {
            column = 0;
            row++;
            fen++;
            continue;
        }

        if (row >= 8 || column >= 8) {
            return 0;
        }
        
        if (*fen >= '0' && *fen <= '8') {
            for (i = column; i < column + (*fen - '0'); i++) {
                if (i >= 8) {
                    return 0;
                }
                chess_board[row][i] = '0';
            }
            column = i;
            fen++;
            continue;
        }

        chess_board[row][column] = *fen;
        column++;
        fen++;
    }

    while (*fen == ' ') fen++;

    char player = *fen;

    fen++;
    while (*fen == ' ') fen++;

    /*
    int white_castle_kingside = 0;
    int white_castle_queenside = 0;
    int black_castle_kingside = 0;
    int black_castle_queenside = 0;
    for (i = 0; i <= 3; i++) {
        if (*(fen+i) == ' ') break;
        switch (*(fen+i)) {
            case 'K':
                white_castle_kingside = 1;
                break;
            case 'Q':
                white_castle_queenside = 1;
                break;
            case 'k':
                black_castle_kingside = 1;
                break;
            case 'q':
                black_castle_queenside = 1;
                break;
        }
    }
    printf("\nK: %d\n", white_castle_kingside);
    printf("Q: %d\n", white_castle_queenside);
    printf("k: %d\n", black_castle_kingside);
    printf("q: %d\n", black_castle_queenside);

    fen += i;
    while (*fen == ' ') fen++;

    char en_passant[9];
    i = 0;
    while (*fen != ' ' && i<8) {
        en_passant[i] = *fen;
        i++;
        fen++;
    }
    en_passant[i] = '\0';
    printf("\nen passant: %s\n", en_passant);

    fen += i;
    while (*fen == ' ') fen++;

    int halfmoves = atoi(fen);
    printf("\nhalfmoves: %d\n", halfmoves);

    while (*fen != ' ') fen++;
    while (*fen == ' ') fen++;

    int fullmoves = atoi(fen);
    printf("\nfullmoves: %d\n\n", fullmoves);
    */

    valid_moves(chess_board, player, 0, check, best_move);
    i = 0;

    char *move;
    move = strtok(moves, " ");  
    while (move != NULL) {
        if (strcmp(best_move, move) == 0) {
            return i; 
        }
        i++;
        move = strtok(NULL, " ");
    }
    return 0;
}


int choose_move(char *fen, char *moves) {
    return generate_index(fen, moves);
}


int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Usage: %s <FEN> <possible_moves> <time_limit>\n", argv[0]);
        return 1;
    }

    char *fen = argv[1];
    char *moves = argv[2];
    //int timeout = atoi(argv[3]);

    printf("%d\n", generate_index(fen, moves));
    return 0;
}