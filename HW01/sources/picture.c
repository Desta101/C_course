#include "../headers/picture.h"
#include "../headers/matrix.h"

void ninty_degree_clockwise(int* picture, const int rows, const int cols)
{
    rotate_ninty_degrees_recursively(picture, picture + (rows * cols) - 1, rows, cols, cols);
}

void rotate_ninty_degrees_recursively(int* start_index, int* end_index, const int rows, const int cols, const int cell_jump)
{
    if (rows <= 1 && cols <= 1)
    {
        return;
    }
    else
    {
        int* p1 = start_index, *p2 = start_index + (cols - 1), *p3 = end_index, *p4 = end_index - (cols - 1);
        for (int i = 0; i < rows - 1; i++, p1++, p2 += cell_jump, p3--, p4 -= cell_jump)
        {
            int temp = *(p1);
            *(p1) = *(p4);
            *(p4) = *(p3);
            *(p3) = *(p2);
            *(p2) = temp;
        }
        rotate_ninty_degrees_recursively(start_index + cols + 1, end_index - (cols + 1), rows - 2, cols - 2, cols);
    }
}

void ninty_degree_counter_clockwise(int* picture, const int rows, const int cols)
{
    rotate_counter_ninty_degrees_recursively(picture, picture + (rows * cols) - 1, rows, cols, cols);
}

void rotate_counter_ninty_degrees_recursively(int* start_index, int* end_index, const int rows, const int cols, const int cell_jump)
{
    if (rows <= 1 && cols <= 1)
    {
        return;
    }
    else
    {
        int* p1 = start_index, *p2 = start_index + (cols - 1), *p3 = end_index, *p4 = end_index - (cols - 1);
        for (int i = 0; i < rows - 1; i++, p1++, p2 += cell_jump, p3--, p4 -= cell_jump)
        {
            int temp = *(p1);
            *(p1) = *(p2);
            *(p2) = *(p3);
            *(p3) = *(p4);
            *(p4) = temp;
        }
        rotate_counter_ninty_degrees_recursively(start_index + cols + 1, end_index - (cols + 1), rows - 2, cols - 2, cols);
    }
}

void flip_horizontally(int* picture, const int rows, const int cols)
{
    flip_horizontal_recursively(picture, picture + (rows * (cols - 1)), cols, rows);
}

void flip_horizontal_recursively(int* start_index, int* end_index, const int cells_in_row, const int rows)
{
    if (rows <= 1)
    {
        return;
    }
    else
    {
        int* p1 = start_index, *p2 = end_index;
        for (int i = 0; i < cells_in_row; i++, p1++, p2++)
        {
            int temp = *(p1);
            *(p1) = *(p2);
            *(p2) = temp;
        }
        flip_horizontal_recursively(start_index + cells_in_row, end_index - cells_in_row, cells_in_row, rows - 2);
    }
}

void flip_vertically(int* picture, const int rows, const int cols)
{
    flip_vertically_recursively(picture, picture + (cols - 1), cols, cols);
}

void flip_vertically_recursively(int* start_index, int* end_index, const int cells_in_col, int cols)
{
    if (cols <= 1)
    {
        return;
    }
    else
    {
        int* p1 = start_index, *p2 = end_index;
        for (int i = 0; i < cells_in_col; i++, p1 += cells_in_col, p2 += cells_in_col)
        {
            int temp = *(p1);
            *(p1) = *(p2);
            *(p2) = temp;
        }
        flip_vertically_recursively(start_index + 1, end_index - 1, cells_in_col, cols - 2);
    }
}