#include <stdio.h>
#include <stdlib.h>
#include "movement.h"
#include "extra.h"


int pawntable[8][8] = {
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 5, 10, 10,-20,-20, 10, 10,  5},
    { 5, -5,-10,  0,  0,-10, -5,  5},
    { 0,  0,  0, 20, 20,  0,  0,  0},
    { 5,  5, 10, 25, 25, 10,  5,  5},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {50, 50, 50, 50, 50, 50, 50, 50},
    { 0,  0,  0,  0,  0,  0,  0,  0}
};

int knightstable[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};

int bishopstable[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
};

int rookstable[8][8] = {
    {  0,  0,  0,  5,  5,  0,  0,  0},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    {  5, 10, 10, 10, 10, 10, 10,  5},
    {  0,  0,  0,  0,  0,  0,  0,  0}
};

int queenstable[8][8] = {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};

int kingstable[8][8] = {
    { 20, 30, 10,  0,  0, 10, 30, 20},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30}
};



int evaluate(char chess_board[8][8], char player) {
    int white_value = 0;
    int black_value = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (chess_board[i][j]) {
                case 'P':
                    white_value += 100 + pawntable[7-i][j];
                    break;
                case 'p':
                    black_value += 100 + pawntable[i][j];
                    break;
                case 'R':
                    white_value += 500 + rookstable[7-i][j];
                    break;
                case 'r':
                    black_value += 500 + rookstable[i][j];
                    break;
                case 'N':
                    white_value += 300 + knightstable[7-i][j];
                    break;
                case 'n':
                    black_value += 300 + knightstable[i][j];
                    break;
                case 'B':
                    white_value += 300 + bishopstable[7-i][j];
                    break;
                case 'b':
                    black_value += 300 + bishopstable[i][j];
                    break;
                case 'Q':
                    white_value += 900 + queenstable[7-i][j];
                    break;
                case 'q':
                    black_value += 900 + queenstable[i][j];
                    break;
                case 'K':
                    white_value += 10000 + kingstable[7-i][j];
                    break;
                case 'k':
                    black_value += 10000 + kingstable[i][j];
                    break;
            }
        }
    }
    int perspective = (player == 'w') ? 1 : -1;
    int evaluation = white_value - black_value;
    return evaluation * perspective;
}

char *convert_to_algebraic(char chess_board[8][8], int prev_i, int prev_j, int i, int j) {
    char *move = malloc(9 * sizeof(char));
    if (!move) {
        printf("Failed to allocate memory!\n");
        exit(1);
    }
    int k = 0;
    switch (chess_board[prev_i][prev_j]) {
        case 'R':
        case 'r':
            move[k++] = 'R';
            break;
        case 'N':
        case 'n':
            move[k++] = 'N';
            break;
        case 'B':
        case 'b':
            move[k++] = 'B';
            break;
        case 'Q':
        case 'q':
            move[k++] = 'Q';
            break;
        case 'K':
        case 'k':
            move[k++] = 'K';
            break;
    }
    move[k++] = 'a' + j;
    move[k++] = '0' + (8 - i);
    move[k] = '\0';
    return move;
}