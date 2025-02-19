#include <string.h>
#include "movement.h"
#include "extra.h"

int check;          // Tracks whether the king is in check (0 for not in check, 1 for in check)
int max = -99999;   // Stores the calculated evaluation of the best move

// Variables from "engine.c"
extern int brow;
extern int bcol;

// Function that generates all possible moves
// If only_check is 1, then its purpose is to find whether the king is in check
void valid_moves(char chess_board[8][8], char player, int only_check, char best_move[9]) {

    // Initialize variables depending on the purpose of the call
    if (only_check) check = 0;
    else max = -99999;

    // Go though the entire board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Skip empty and enemy pieces
            if (is_enemy(chess_board, i, j, player)) continue;
            // Generate moves depending on the piece selected
            switch (chess_board[i][j]) {
                case 'P':
                case 'p':
                    pawn_movement(chess_board, i, j, player, only_check, best_move);
                    break;
                case 'R':
                case 'r':
                    rook_movement(chess_board, i, j, player, only_check, best_move);
                    break;
                case 'N':
                case 'n':
                    basic_movement(chess_board, i, j, i - 1, j - 2, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i - 1, j + 2, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i - 2, j - 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i - 2, j + 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j - 2, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j + 2, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i + 2, j - 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i + 2, j + 1, player, only_check, best_move);
                    break;
                case 'B':
                case 'b':
                    bishop_movement(chess_board, i, j, player, only_check, best_move);
                    break;
                case 'Q':
                case 'q':
                    rook_movement(chess_board, i, j, player, only_check, best_move);
                    bishop_movement(chess_board, i, j, player, only_check, best_move);
                    break;
                case 'K':
                case 'k':
                    basic_movement(chess_board, i, j, i - 1, j, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i, j - 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i, j + 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j + 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i + 1, j - 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i - 1, j + 1, player, only_check, best_move);
                    basic_movement(chess_board, i, j, i - 1, j - 1, player, only_check, best_move);
                    break;
            }
            if (only_check && check == 1) return;
        }
    }
}


// Function for generating possible moves for pawns
void pawn_movement(char chess_board[8][8], int i, int j, char player, int only_check, char best_move[9]) {
    int n1;             // 1 step forward (direction based on player)
    int n2;             // 2 steps forward (direction based on player)
    int special_row;    // Row which allows double movement
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
        make_move(chess_board, i, j, i + n1, j, player, only_check, best_move);
    // Two-step forward from special row
    if (0 <= i + n2 && i + n2 <= 7 && i == special_row && chess_board[i + n1][j] == '0' && chess_board[i + n2][j] == '0') {
        make_move(chess_board, i, j, i + n2, j, player, only_check, best_move);
    }
    // Diagonal left capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j - 1 && j - 1 <= 7 && is_enemy(chess_board, i + n1, j - 1, player))
        make_move(chess_board, i, j, i + n1, j - 1, player, only_check, best_move);
    // Diagonal right capture
    if (0 <= i + n1 && i + n1 <= 7 && 0 <= j + 1 && j + 1 <= 7 && is_enemy(chess_board, i + n1, j + 1, player))
        make_move(chess_board, i, j, i + n1, j + 1, player, only_check, best_move);
}


// Function for enabling movement on the selected square
// Returns 0 if movement should be stopped or 1 if movement can continue
int basic_movement(char chess_board[8][8], int prev_i, int prev_j, int i, int j, char player, int only_check, char best_move[9]) {
    // Ensure that position is within bounds
    if (i < 0 || i >= 8 || j < 0 || j >= 8) return 0;

    // If the square is empty, allow movement
    if (chess_board[i][j] == '0') {
        make_move(chess_board, prev_i, prev_j, i, j, player, only_check, best_move);
        return 1;
    }

    // If the square has an opponent piece, allow capture and stop further movement
    if (is_enemy(chess_board, i, j, player)) {
        make_move(chess_board, prev_i, prev_j, i, j, player, only_check, best_move);
        return 0;
    }

    // If it's a teammate piece, block movement
    return 0;
}


// Function for generating possible moves for rooks
void rook_movement(char chess_board[8][8], int i, int j, char player, int only_check, char best_move[9]) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j, player, only_check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j, player, only_check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i, j - a, player, only_check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i, j + a, player, only_check, best_move)) break;
}


// Function for generating possible moves for bishops
void bishop_movement(char chess_board[8][8], int i, int j, char player, int only_check, char best_move[9]) {
    int a;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j + a, player, only_check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i + a, j - a, player, only_check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j + a, player, only_check, best_move)) break;
    for (a = 1; a < 8; a++)
        if (! basic_movement(chess_board, i, j, i - a, j - a, player, only_check, best_move)) break;
}


// Function that returns 1 if the selected square is empty or occupied by the enemy player
int is_enemy(char chess_board[8][8], int i, int j, char player) {
    int flag1 = chess_board[i][j] != '0';
    int flag2 = chess_board[i][j] >= 'A' && chess_board[i][j] <= 'Z' && player == 'b';
    int flag3 = chess_board[i][j] >= 'a' && chess_board[i][j] <= 'z' && player == 'w';

    return flag1 && (flag2 || flag3);
}


// Executes a move, processes the updated chess board state, and then reverts the move
void make_move(char chess_board[8][8], int prev_i, int prev_j, int i, int j, char player, int only_check, char best_move[9]) {

    // If function is called with only_check == 1 and a king is captured, update check to 1
    if (only_check) {
        if (chess_board[i][j] == 'k' || chess_board[i][j] == 'K') {
            check = 1;
        }
        return;
    }

    char move[9];   // Current move in algebraic notation format
    int k = 0;

    // Convert move to the algebraic notation format      
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
        case 'P':
        case 'p':
            if (chess_board[i][j] != '0') move[k++] = 'a' + prev_j;
            break;
    }
    if (chess_board[i][j] != '0') move[k++] = 'x';
    move[k++] = 'a' + j;
    move[k++] = '0' + (8 - i);

    // Update variables in case of disambiguating moves
    brow = 'a' + prev_j;
    bcol = '0' + (8 - prev_i);

    // Make the move
    char current = chess_board[i][j];
    chess_board[i][j] = chess_board[prev_i][prev_j];
    char prev = chess_board[prev_i][prev_j];
    chess_board[prev_i][prev_j] = '0'; 

    // Algebraic notation for pawn promotion
    if ((chess_board[i][j] == 'p' || chess_board[i][j] == 'P') && (i == 0 || i == 7)) {
        move[k++] = '=';
        move[k++] = 'Q';
    }

    // Algebraic notation for moves resulting to check of the opponent's king
    char opponent = (player == 'w') ? 'b' : 'w';
    if (in_check(chess_board, opponent, best_move)) move[k++] = '+'; 
    move[k] = '\0';

    // If the move is valid (doesn't result to check for the current player's king),
    // find its evaluation and check if it is larger than previous moves
    if (!in_check(chess_board, player, best_move)) {
        int value = evaluate(chess_board, player);
        if (value > max) {
            max = value;
            strncpy(best_move, move, 8); // Update best_move
        }
    }

    // Undo the move
    chess_board[prev_i][prev_j] = prev;
    chess_board[i][j] = current;
}


// Function that checks if a move results to a check
int in_check(char chess_board[8][8], char player, char best_move[9]) {
    char opponent = (player == 'w') ? 'b' : 'w';
    // Re-call valid_moves but only for check purposes
    valid_moves(chess_board, opponent, 1, best_move);
    if (check == 1) return 1;
    return 0;
}