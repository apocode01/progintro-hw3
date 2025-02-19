#include <stdio.h>
#include <string.h>
#include "movement.h"

// Global variables to control disambiguating moves when converting to the algebraic notation format
int brow;
char bcol;

// Declare generate_index function that handles user input and returns the index of a good next chess move 
int generate_index(char *fen, char *moves) {
    
    int i;
    char chess_board[8][8]; // Stores the current state of the chess board
    char best_move[9];      // Stores the "best" next move in algebraic notation format
    int row = 0;
    int column = 0;

    // Handle the first part of the FEN (where each piece is)
    while (*fen != ' ') {
        if (*fen == '/') {
            column = 0;
            row++;
            fen++;
            continue;
        }

        // Invalid FEN (results to doing the first possible move)
        if (row >= 8 || column >= 8) {
            return 0;
        }
        
        // Clear the number of squares based on the number encountered
        if (*fen >= '0' && *fen <= '8') {
            for (i = column; i < column + (*fen - '0'); i++) {
                // Invalid FEN (results to doing the first possible move)
                if (i >= 8) {
                    return 0;
                }
                chess_board[row][i] = '0';
            }
            column = i;
            fen++;
            continue;
        }

        // Store the current selected piece in the calculated row and column of the chess board
        chess_board[row][column] = *fen;
        column++;
        fen++;
    }

    while (*fen == ' ') fen++; // Skip whitespaces

    // Handle the second part of the FEN (whose turn it is) 
    char player = *fen;

    // If a possible move includes the '#' character (which means checkmate), store that
    // move in the checkmate variable and skip the process of finding the next "best" move 
    char *checkmate = strchr(moves, '#');
    if (checkmate) {
        while (*(checkmate-1) != ' ') checkmate--;
    }
    // Otherwise, calculate a good next move using the valid_moves function (from "movement.h")
    else {
        valid_moves(chess_board, player, 0, best_move); 
    }
    
    i = 0;                  // Index of the next "best" move
    char best_move_copy[9]; // Copy of the best_move
    char *move;             // Stores the current possible move

    // Separate all possible moves given from the user
    move = strtok(moves, " ");  
    while (move != NULL) {
        // If we already found that a move results to a checkmate, only search for that move
        if (checkmate) {
            if (strcmp(checkmate, move) == 0) return i;
        }
        // Otherwise, keep looking for the calculated next "best" move
        else if (strcmp(best_move, move) == 0) {
            return i; 
        }
        // In case the calculated "best" move is a disambiguating move, 
        // check for more detailed algebraic notation formats
        else {
            strncpy(best_move_copy, best_move, 8);
            int N = strlen(best_move);
            best_move_copy[N] = ' ';
            for (int j = N; j > 1; j--) {
                best_move_copy[j] = best_move_copy[j-1];
            }
            best_move_copy[1] = brow; // Include the file of departure
            if (strcmp(best_move_copy, move) == 0) return i;
            else {
                best_move_copy[1] = bcol; // Include the rank of departure
                if (strcmp(best_move_copy, move) == 0) return i;
            }
        }
        i++;
        move = strtok(NULL, " ");
    }

    // If the process failed, return the index of the first move
    return 0;
}


// Function for the Web Assembly interface
int choose_move(char *fen, char *moves, int timeout) {
    (void)timeout;
    return generate_index(fen, moves);
}


int main(int argc, char *argv[]) {

    // Check if the user has provided 4 arguments (including program name)
    if (argc != 4) {
        printf("Usage: %s <FEN> <possible_moves> <time_limit>\n", argv[0]);
        return 1;
    }

    char *fen = argv[1];
    char *moves = argv[2];

    printf("%d\n", generate_index(fen, moves));
    return 0;
}