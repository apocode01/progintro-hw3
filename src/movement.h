void valid_moves(char[8][8], char, int, char[9]);
void pawn_movement(char[8][8], int, int, char, int, char[9]);
void rook_movement(char[8][8], int, int, char, int, char[9]);
int basic_movement(char[8][8], int, int, int, int, char, int, char[9]);
void bishop_movement(char[8][8], int, int, char, int, char[9]);
int is_enemy(char[8][8], int, int, char);
void make_move(char[8][8], int, int, int, int, char, int, char[9]);
int in_check(char[8][8], char, char[9]);