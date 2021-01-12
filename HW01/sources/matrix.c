#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(const int* mat, const int rows, const int cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("%20c", 32);
        for (int j = 0; j < cols; j++)
        {
            printf("%5d", *(mat + (i * cols) + j));
        }
        printf("\n");
    }
}

void initialize_matrix_ascending_values(int* mat, const int rows, const int cols)
{
    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++, count++)
        {
            *(mat + (i * cols) + j) = count;         
        }
    }
}

void initialize_matrix_random_values(int* mat, const int rows, const int cols, const int from_num, const int to_num)
{
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(mat + (i * cols) + j) = (rand() % (to_num - from_num + 1)) + from_num;    
        }
    }
}

int get_index_by_value(const int* mat, const int size, const int num)
{
    for (int i = 0; i < size; i++)
    {
        if(*(mat + i) == num)
        {
            return i;
        }
    }
}

int check_mat_ascending(const int* mat, const int rows, const int cols)
{
    for (int i = 0; i < rows * cols - 1; i++)
    {
        if (*(mat + i) > *(mat + i + 1))
        {
            return 0;
        }
    }
    return 1;
}