#include <stdio.h>
#include "movement.h"
#include "score.h"


extern int en_passant_row;
extern int en_passant_col;
extern int max;
extern int max_i;
extern int max_j;
extern int check;
extern int count;


void valid_moves(char chess_board[8][8], char player, int only_check) {
    if (only_check) check = 0;
    else count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (is_enemy(chess_board, i, j, player)) continue;
            switch (chess_board[i][j]) {
                case 'P':
                case 'p':
                    pawn_movement(chess_board, i, j, player, only_check);
                    break;
                case 'R':
                case 'r':
                    rook_movement(chess_board, i, j, player, only_check);
                    break;
                case 'N':
                case 'n':
                    basic_movement(chess_board, i, j, i - 1, j - 2, player, only_check);
                    basic_movement(chess_board, i, j, i - 1, j + 2, player, only_check);
                    basic_movement(chess_board, i, j, i - 2, j - 1, player, only_check);
                    basic_movement(chess_board, i, j, i - 2, j + 1, player, only_check);
                    basic_movement(chess_board, i, j, i + 1, j - 2, player, only_check);
                    basic_movement(chess_board, i, j, i + 1, j + 2, player, only_check);
                    basic_movement(chess_board, i, j, i + 2, j - 1, player, only_check);
                    basic_movement(chess_board, i, j, i + 2, j + 1, player, only_check);
                    break;
                case 'B':
                case 'b':
                    bishop_movement(chess_board, i, j, player, only_check);
                    break;
                case 'Q':
                case 'q':
                    rook_movement(chess_board, i, j, player, only_check);
                    bishop_movement(chess_board, i, j, player, only_check);
                    break;
                case 'K':
                case 'k':
                    basic_movement(chess_board, i, j, i - 1, j, player, only_check);
                    basic_movement(chess_board, i, j, i + 1, j, player, only_check);
                    basic_movement(chess_board, i, j, i, j - 1, player, only_check);
                    basic_movement(chess_board, i, j, i, j + 1, player, only_check);
                    basic_movement(chess_board, i, j, i + 1, j + 1, player, only_check);
                    basic_movement(chess_board, i, j, i + 1, j - 1, player, only_check);
                    basic_movement(chess_board, i, j, i - 1, j + 1, player, only_check);
                    basic_movement(chess_board, i, j, i - 1, j - 1, player, only_check);
                    break;
            }
            if (only_check && check == 1) return;
        }
    }
    
}


void pawn_movement(char chess_board[8][8], int i, int j, char player, int only_check) {
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
        make_move(chess_board, i, j, i + n1, j, player, 0, only_check);
    // Two-step forward from special row
    if (0 <= i + n2 && i + n2 <= 7 && i == special_row && chess_board[i + n1][j] == '0' && chess_board[i + n2][j] == '0') {
        make_move(chess_board, i, j, i + n2, j, player, 0, only_check);
        en_passant_row = i + n1;
        en_passant_col = j;
    }
    // Diagonal left capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j - 1 && j - 1 <= 7 && is_enemy(chess_board, i + n1, j - 1, player))
        make_move(chess_board, i, j, i + n1, j - 1, player, 0, only_check);
    // Diagonal right capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j + 1 && j + 1 <= 7 && is_enemy(chess_board, i + n1, j + 1, player))
        make_move(chess_board, i, j, i + n1, j + 1, player, 0, only_check);
    // En passant left capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j - 1 && j - 1 <= 7 && j - 1 == en_passant_col && i + n1 == en_passant_row) {
        make_move(chess_board, i, j, i + n1, j - 1, player, 1, only_check);
    }
    // En passant right capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j + 1 && j + 1 <= 7 && j + 1 == en_passant_col && i + n1 == en_passant_row) {
        make_move(chess_board, i, j, i + n1, j + 1, player, 1, only_check);
    }
}


int basic_movement(char chess_board[8][8], int prev_i, int prev_j, int i, int j, char player, int only_check) {
    // Ensure that position is within bounds
    if (i < 0 || i >= 8 || j < 0 || j >= 8) return 0;

    // If the square is empty, allow movement
    if (chess_board[i][j] == '0') {
        make_move(chess_board, prev_i, prev_j, i, j, player, 0, only_check);
        return 1;
    }

    // If the square has an opponent piece, allow capture and stop further movement
    if (is_enemy(chess_board, i, j, player)) {
        make_move(chess_board, prev_i, prev_j, i, j, player, 0, only_check);
        return 0;
    }

    // If it's a teammate piece, block movement
    return 0;
}


void rook_movement(char chess_board[8][8], int i, int j, char player, int only_check) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j, player, only_check)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j, player, only_check)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i, j - a, player, only_check)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i, j + a, player, only_check)) break;
}


void bishop_movement(char chess_board[8][8], int i, int j, char player, int only_check) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j + a, player, only_check)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j - a, player, only_check)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j + a, player, only_check)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j - a, player, only_check)) break;
}


int is_enemy(char chess_board[8][8], int i, int j, char player) {
    int flag1 = chess_board[i][j] != '0';
    int flag2 = chess_board[i][j] >= 'A' && chess_board[i][j] <= 'Z' && player == 'b';
    int flag3 = chess_board[i][j] >= 'a' && chess_board[i][j] <= 'z' && player == 'w';

    return flag1 && (flag2 || flag3);
}


void make_move(char chess_board[8][8], int prev_i, int prev_j, int i, int j, char player, int en_passant, int only_check) {
    // Clear the en passant target after every move
    en_passant_row = -1;
    en_passant_col = -1;

    if (only_check) {
        if (chess_board[i][j] == 'k' || chess_board[i][j] == 'K') {
            check = 1;
        }
        return;
    }

    char current = chess_board[i][j];
    chess_board[i][j] = chess_board[prev_i][prev_j];
    char prev = chess_board[prev_i][prev_j];
    chess_board[prev_i][prev_j] = '0'; 
    char prev2;
    if (en_passant) {
        prev2 = chess_board[prev_i][j];
        chess_board[prev_i][j] = '0'; 
    }

    int value;
    if (!in_check(chess_board, player)) {
        value = evaluate(chess_board, player);
        if (value > max) {
            max = value;
            max_i = i;
            max_j = j;
        }
        count++;
    }

    chess_board[prev_i][prev_j] = prev;
    chess_board[i][j] = current;
    if (en_passant) {
        chess_board[prev_i][j] = prev2; 
    }
}

int in_check(char chess_board[8][8], char player) {
    if (player == 'w') {
        valid_moves(chess_board, 'b', 1);
    }
    else if (player == 'b') {
        valid_moves(chess_board, 'w', 1);
    }
    if (check == 1) return 1;
    return 0;
}