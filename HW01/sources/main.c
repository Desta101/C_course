#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> 


#define N  8
#define DIAG  (N*2 - 1)
#define BOARD_SIDE 8

void SolutionsFinder(int board[N], int column, bool used[3][DIAG]);
void SolutionPrint(int board[N], int size);
void UsedAdd(bool used[3][DIAG], int row, int column);
void UsedRemove(bool used[3][DIAG], int row, int column);
bool Legal(bool used[3][DIAG], int row, int column);

int main()
{
	int board[N];
	int used[3][DIAG]; // row, up-diag, down-diag

	//Initializing used arrays. Note that there are
	//only N rows so the remaining elements
	//in used[0] will be discarded.

	for (int i = 0; i < DIAG; i++)
		used[0][i] = used[1][i] = used[2][i] = false;

	printf("Solving the %d Queens Problem\n\n", N);
	SolutionsFinder(board, 0, used);
	printf("\nDone!\n");

	return 0;
}


void SolutionsFinder(int board[N], int column, bool used[3][DIAG])
{
	if (column >= N) {
		SolutionPrint(board, N);
		return;
	}

	for (int row = 0; row < N; row++) {
		if (!Legal(used, row, column))
			continue;
		board[column] = row;
		UsedAdd(used, row, column);
		SolutionsFinder(board, column + 1, used);
		UsedRemove(used, row, column);
	}

	return;
}

bool Legal(int used[3][DIAG], int r, int c)
{
	return  !used[0][r]
		&& !used[1][r + c]
		&& !used[2][N - 1 + r - c];
}

void UsedMark(int used[3][DIAG], bool mark, int r, int c)
{
	used[0][r] = mark;
	used[1][r + c] = mark;
	used[2][BOARD_SIDE - 1 + r - c] = mark;
}

void UsedAdd(int used[3][DIAG], int r, int c)
{
	UsedMark(used, true, r, c);
}

void UsedRemove(int used[3][DIAG], int r, int c)
{
	UsedMark(used, false, r, c);
}

void SolutionPrint(int board[N], int size)
{
	static int solution_number; /* statics are initialized
								   to zero */
	printf("Solution number %d:\n\t", ++solution_number);
	for (int i = 0; i < size; i++)
		printf("%d ", board[i] + 1);
	putchar('\n');
}
