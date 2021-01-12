#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/puzzle.h"
#include "../headers/matrix.h"

void randomize_board(int* puzzle, const int rows, const int cols)
{
    int zero_index , new_zero_index;
    srand(time(NULL));
    zero_index = find_zero_index((const int*)puzzle, rows, cols);
    for (int i = 0; i < SHUFFLE_COUNT; i++)
    {
        switch (rand() % 4 + 1)
        {
        case UP:
            new_zero_index = zero_index - cols;
            if (check_up((const int*)puzzle, rows, cols, new_zero_index))
            {
                swap_puzzle_pieces(puzzle + zero_index, puzzle + new_zero_index);
                zero_index = new_zero_index;
            }
            break;
        case RIGHT:
            new_zero_index = zero_index + 1;
            if (check_right((const int*)puzzle, rows, cols, new_zero_index))
            {
                swap_puzzle_pieces(puzzle + zero_index, puzzle + new_zero_index);
                zero_index = new_zero_index;
            }
            break;
        case DOWN:
            new_zero_index = zero_index + cols;
            if (check_down((const int*)puzzle, rows, cols, new_zero_index))
            {
                swap_puzzle_pieces((const int*)puzzle + zero_index, puzzle + new_zero_index);
                zero_index = new_zero_index;
            }
            break;
        case LEFT:
            new_zero_index = zero_index - 1;
            if (check_left((const int*)puzzle, rows, cols, new_zero_index))
            {
                swap_puzzle_pieces(puzzle + zero_index, puzzle + new_zero_index);
                zero_index = new_zero_index;
            }
            break;
        default:
            break;
        }
    }
}

void play(int* puzzle, const int rows, const int cols)
{
    int step ,zero_index, new_index;
    initialize_matrix_ascending_values(puzzle, rows, cols);
    do
    {
        randomize_board(puzzle, rows, cols);
    } while(check_mat_ascending((const int*)puzzle, rows, cols));
    zero_index = find_zero_index((const int*)puzzle, rows, cols);
    while(1)
    {
        print_matrix((const int*)puzzle, rows, cols);
        printf("\n");
        printf("Your step: ");
        scanf("%d", &step);
        if (step < 0 || step > rows * cols - 1)
        {
            printf("Invalid step\n\n");
            continue;
        }
        else
        {
            int wanted_index = get_index_by_value((const int*)puzzle, (rows * cols), step);
            if (wanted_index == zero_index - cols)
            {
                if (check_up(puzzle, rows, cols, wanted_index))
                {
                    swap_puzzle_pieces(puzzle + zero_index, puzzle + wanted_index);
                    zero_index = wanted_index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else if (wanted_index == zero_index + 1)
            {
                if (check_right(puzzle, rows, cols, wanted_index))
                {
                    swap_puzzle_pieces(puzzle + zero_index, puzzle + wanted_index);
                    zero_index = wanted_index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else if (wanted_index == zero_index + cols)
            {
                if (check_down(puzzle, rows, cols, wanted_index))
                {
                    swap_puzzle_pieces(puzzle + zero_index, puzzle + wanted_index);
                    zero_index = wanted_index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else if (wanted_index == zero_index - 1)
            {
                if (check_left(puzzle, rows, cols, wanted_index))
                {
                    swap_puzzle_pieces(puzzle + zero_index, puzzle + wanted_index);
                    zero_index = wanted_index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else
            {
                printf("Invalid step\n\n");
                continue;
            }
            if (check_mat_ascending((const int*)puzzle, rows, cols))
            {
                printf("You win! The game is over!\n");
                exit(0);
            }
        }  
    }
}

int find_zero_index(const int* puzzle, const int rows, const int cols)
{
    for (int i = 0; i < rows * cols - 1; i++)
    {
        if (*(puzzle + i) == 0)
        {
            return i;
        }
    }
}

void swap_puzzle_pieces(int* f_index, int* s_index)
{
    int temp = *f_index;
    *f_index = *s_index;
    *s_index = temp;
}

int check_up(const int* puzzle, const int rows, const int cols, const int new_piece_index)
{
    int flag = new_piece_index;
    if (flag >= 0)
    {
        return 1;
    }
    return 0;
}

int check_right(const int* puzzle, const int rows, const int cols, const int new_piece_index)
{
    int flag = (new_piece_index) % cols;
    if ((new_piece_index != (cols * rows)) && flag)
    {
        return 1;
    }
    return 0;
}

int check_down(const int* puzzle, const int rows, const int cols, const int new_piece_index)
{
    int flag = new_piece_index;
    if (flag <= (rows * cols) - 1)
    {
        return 1;
    }
    return 0;
}

int check_left(const int* puzzle, const int rows, const int cols, const int new_piece_index)
{
    int flag = (new_piece_index + 1) % cols;
    if (flag > 0)
    {
        return 1;
    }
    return 0;
}