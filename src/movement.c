#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "extra.h"


void valid_moves(char chess_board[8][8], char player, int only_check, int check, char best_move[9]) {
    if (only_check) check = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (is_enemy(chess_board, i, j, player)) continue;
            switch (chess_board[i][j]) {
                case 'P':
                case 'p':
                    pawn_movement(chess_board, i, j, player, only_check, check, best_move);
                    break;
                case 'R':
                case 'r':
                    rook_movement(chess_board, i, j, player, only_check, check, best_move);
                    break;
                case 'N':
                case 'n':
                    basic_movement(chess_board, i, j, i - 1, j - 2, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i - 1, j + 2, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i - 2, j - 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i - 2, j + 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j - 2, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j + 2, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i + 2, j - 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i + 2, j + 1, player, only_check, check, best_move);
                    break;
                case 'B':
                case 'b':
                    bishop_movement(chess_board, i, j, player, only_check, check, best_move);
                    break;
                case 'Q':
                case 'q':
                    rook_movement(chess_board, i, j, player, only_check, check, best_move);
                    bishop_movement(chess_board, i, j, player, only_check, check, best_move);
                    break;
                case 'K':
                case 'k':
                    basic_movement(chess_board, i, j, i - 1, j, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i, j - 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i, j + 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j + 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j - 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i - 1, j + 1, player, only_check, check, best_move);
                    basic_movement(chess_board, i, j, i - 1, j - 1, player, only_check, check, best_move);
                    break;
            }
            if (only_check && check == 1) return;
        }
    }
}


void pawn_movement(char chess_board[8][8], int i, int j, char player, int only_check, int check, char best_move[9]) {
    int n1, n2, special_row;
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
        make_move(chess_board, i, j, i + n1, j, player, only_check, check, best_move);
    // Two-step forward from special row
    if (0 <= i + n2 && i + n2 <= 7 && i == special_row && chess_board[i + n1][j] == '0' && chess_board[i + n2][j] == '0') {
        make_move(chess_board, i, j, i + n2, j, player, only_check, check, best_move);
    }
    // Diagonal left capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j - 1 && j - 1 <= 7 && is_enemy(chess_board, i + n1, j - 1, player))
        make_move(chess_board, i, j, i + n1, j - 1, player, only_check, check, best_move);
    // Diagonal right capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j + 1 && j + 1 <= 7 && is_enemy(chess_board, i + n1, j + 1, player))
        make_move(chess_board, i, j, i + n1, j + 1, player, only_check, check, best_move);
}


int basic_movement(char chess_board[8][8], int prev_i, int prev_j, int i, int j, char player, int only_check, int check, char best_move[9]) {
    // Ensure that position is within bounds
    if (i < 0 || i >= 8 || j < 0 || j >= 8) return 0;

    // If the square is empty, allow movement
    if (chess_board[i][j] == '0') {
        make_move(chess_board, prev_i, prev_j, i, j, player, only_check, check, best_move);
        return 1;
    }

    // If the square has an opponent piece, allow capture and stop further movement
    if (is_enemy(chess_board, i, j, player)) {
        make_move(chess_board, prev_i, prev_j, i, j, player, only_check, check, best_move);
        return 0;
    }

    // If it's a teammate piece, block movement
    return 0;
}


void rook_movement(char chess_board[8][8], int i, int j, char player, int only_check, int check, char best_move[9]) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j, player, only_check, check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j, player, only_check, check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i, j - a, player, only_check, check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i, j + a, player, only_check, check, best_move)) break;
}


void bishop_movement(char chess_board[8][8], int i, int j, char player, int only_check, int check, char best_move[9]) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j + a, player, only_check, check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j - a, player, only_check, check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j + a, player, only_check, check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j - a, player, only_check, check, best_move)) break;
}


int is_enemy(char chess_board[8][8], int i, int j, char player) {
    int flag1 = chess_board[i][j] != '0';
    int flag2 = chess_board[i][j] >= 'A' && chess_board[i][j] <= 'Z' && player == 'b';
    int flag3 = chess_board[i][j] >= 'a' && chess_board[i][j] <= 'z' && player == 'w';

    return flag1 && (flag2 || flag3);
}


void make_move(char chess_board[8][8], int prev_i, int prev_j, int i, int j, char player, int only_check, int check, char best_move[9]) {

    static int max = -99999;

    if (only_check) {
        if (chess_board[i][j] == 'k' || chess_board[i][j] == 'K') {
            check = 1;
        }
        return;
    }

    char *move = convert_to_algebraic(chess_board, prev_i, prev_j, i, j);

    char current = chess_board[i][j];
    chess_board[i][j] = chess_board[prev_i][prev_j];
    char prev = chess_board[prev_i][prev_j];
    chess_board[prev_i][prev_j] = '0'; 

    if (!in_check(chess_board, player, check, best_move)) {
        int value = evaluate(chess_board, player);
        if (value > max) {
            max = value;
            strncpy(best_move, move, 8);
        }  
    }

    free(move);

    chess_board[prev_i][prev_j] = prev;
    chess_board[i][j] = current;
}

int in_check(char chess_board[8][8], char player, int check, char best_move[9]) {
    if (player == 'w') {
        valid_moves(chess_board, 'b', 1, check, best_move);
    }
    else if (player == 'b') {
        valid_moves(chess_board, 'w', 1, check, best_move);
    }
    if (check == 1) return 1;
    return 0;
}