#include <stdio.h>
#include "movement.h"


void valid_moves(char chess_board[8][8], char player) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (is_enemy(chess_board, i, j, player)) continue;
            switch (chess_board[i][j]) {
                case 'P':
                case 'p':
                    pawn_movement(chess_board, i, j, player);
                    break;
                case 'R':
                case 'r':
                    rook_movement(chess_board, i, j, player);
                    break;
                case 'N':
                case 'n':
                    basic_movement(chess_board, i - 1, j - 2, player);
                    basic_movement(chess_board, i - 1, j + 2, player);
                    basic_movement(chess_board, i - 2, j - 1, player);
                    basic_movement(chess_board, i - 2, j + 1, player);
                    basic_movement(chess_board, i + 1, j - 2, player);
                    basic_movement(chess_board, i + 1, j + 2, player);
                    basic_movement(chess_board, i + 2, j - 1, player);
                    basic_movement(chess_board, i + 2, j + 1, player);
                    break;
                case 'B':
                case 'b':
                    bishop_movement(chess_board, i, j, player);
                    break;
                case 'Q':
                case 'q':
                    rook_movement(chess_board, i, j, player);
                    bishop_movement(chess_board, i, j, player);
                    break;
                case 'K':
                case 'k':
                    basic_movement(chess_board, i - 1, j, player);
                    basic_movement(chess_board, i + 1, j, player);
                    basic_movement(chess_board, i, j - 1, player);
                    basic_movement(chess_board, i, j + 1, player);
                    basic_movement(chess_board, i + 1, j + 1, player);
                    basic_movement(chess_board, i + 1, j - 1, player);
                    basic_movement(chess_board, i - 1, j + 1, player);
                    basic_movement(chess_board, i - 1, j - 1, player);
            }
        }
    }
}


void pawn_movement(char chess_board[8][8], int i, int j, char player) {
    int n1, n2; 
    int special_row;
    if (player == 'b') {
        n1 = 1;
        n2 = 2;
        special_row = 1;
    }
    else {
        n1 = -1;
        n2 = -2;
        special_row = 6;
    }

    // Single-step forward
    if (0 <= i + n1 && i + n1 <= 7 && chess_board[i + n1][j] == '0')
        printf("%d-%d\n", i + n1, j);
    // Two-step forward from special row
    if (0 <= i + n2 && i + n2 <= 7 && i == special_row && chess_board[i + n1][j] == '0' && chess_board[i + n2][j] == '0')
        printf("%d-%d\n", i + n2, j);
    // Diagonal left capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j - n1 && j - n1 <= 7 && is_enemy(chess_board, i + n1, j - n1, player))
        printf("%d-%d\n", i + n1, j - n1);
    // Diagonal right capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j + n1 && j + n1 <= 7 && is_enemy(chess_board, i + n1, j + n1, player))
        printf("%d-%d\n", i + n1, j + n1);
}


int basic_movement(char chess_board[8][8], int i, int j, char player) {
    // Ensure that position is within bounds
    if (i < 0 || i >= 8 || j < 0 || j >= 8) return 0;

    // If the square is empty, allow movement
    if (chess_board[i][j] == '0') {
        printf("%d-%d\n", i, j);
        return 1;
    }

    // If the square has an opponent piece, allow capture and stop further movement
    if (is_enemy(chess_board, i, j, player)) {
        printf("%d-%d\n", i, j);
        return 0;
    }

    // If it's a teammate piece, block movement
    return 0;
}


void rook_movement(char chess_board[8][8], int i, int j, char player) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i - a, j, player)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i + a, j, player)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j - a, player)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j + a, player)) break;
}


void bishop_movement(char chess_board[8][8], int i, int j, char player) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i + a, j + a, player)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i + a, j - a, player)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i - a, j + a, player)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i - a, j - a, player)) break;
}


int is_enemy(char chess_board[8][8], int i, int j, char player) {
    int flag1 = chess_board[i][j] != '0';
    int flag2 = chess_board[i][j] >= 'A' && chess_board[i][j] <= 'Z' && player == 'b';
    int flag3 = chess_board[i][j] >= 'a' && chess_board[i][j] <= 'z' && player == 'w';

    return flag1 && (flag2 || flag3);
}