#ifndef __PUZZLE__
#define __PUZZLE__

#define PUZZLE_ROWS 3
#define PUZZLE_COLS 3

#define ZERO 0

#define SHUFFLE_COUNT 50

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

void randomize_board(int* puzzle, const int rows, const int cols);
void play(int* puzzle, const int rows, const int cols);
int find_zero_index(const int* puzzle, const int rows, const int cols);
void swap_puzzle_pieces(int* f_index, int* s_index);
int check_up(const int* puzzle, const int rows, const int cols, const int new_piece_index);
int check_right(const int* puzzle, const int rows, const int cols, const int new_piece_index);
int check_down(const int* puzzle, const int rows, const int cols, const int new_piece_index);
int check_left(const int* puzzle, const int rows, const int cols, const int new_piece_index);

#endif