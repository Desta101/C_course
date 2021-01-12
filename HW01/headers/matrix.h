#ifndef __MATRIX__
#define __MATRIX__

void print_matrix(const int* mat, const int rows, const int cols);
void initialize_matrix_ascending_values(int* mat, const int rows, const int cols);
void initialize_matrix_random_values(int* mat, const int rows, const int cols, const int from_num, const int to_num);
int get_index_by_value(const int* mat, const int size, const int num);
int check_mat_ascending(const int* mat, const int rows, const int cols);

#endif