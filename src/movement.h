void valid_moves(char[8][8], char);
void pawn_movement(char[8][8], int, int, char);
void rook_movement(char[8][8], int, int, char);
int basic_movement(char[8][8], int, int, int, int, char);
void bishop_movement(char[8][8], int, int, char);
int is_enemy(char[8][8], int, int, char);
void make_move(char[8][8], int, int, int, int);
void swap(char *, char *);