#ifndef __PICTURE__
#define __PICTURE__

#define PICTURE_ROWS 3
#define PICTURE_COLS 3

#include "../headers/picture.h"
#include "../headers/matrix.h"

void ninty_degree_clockwise(int* picture, const int rows, const int cols);
void rotate_ninty_degrees_recursively(int* start_index, int* end_index, const int rows, const int cols, const int cell_jump);
void ninty_degree_counter_clockwise(int* picture, const int rows, const int cols);
void rotate_counter_ninty_degrees_recursively(int* start_index, int* end_index, const int rows, const int cols, const int cell_jump);
void flip_horizontally(int* picture, const int rows, int cols);
void flip_horizontal_recursively(int* start_index, int* end_index, const int rows, const int cols);
void flip_vertically(int* picture, const int rows, const int cols);
void flip_vertically_recursively(int* start_index, int* end_index, const int rows, int cols);

#endif