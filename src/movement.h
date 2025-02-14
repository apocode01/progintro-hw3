void valid_moves(char[8][8], char, int);
void pawn_movement(char[8][8], int, int, char, int);
void rook_movement(char[8][8], int, int, char, int);
int basic_movement(char[8][8], int, int, int, int, char, int);
void bishop_movement(char[8][8], int, int, char, int);
int is_enemy(char[8][8], int, int, char);
void make_move(char[8][8], int, int, int, int, char, int);
int in_check(char[8][8], char);