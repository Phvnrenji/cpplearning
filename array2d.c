#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
//#include “Array.h”

int **Make2DArray(int row, int col);
void Diliver2DArray(int **a, int row);

void main(void)
{
	int i, j, c = 0;
	int row = 3, col = 4, **a;
	a = Make2DArray(row, col);
	for (i = 0; i < row; i++)
	{
		
        for (j = 0; j < col; j++) {
            c = rand() % 10;
            a[i][j] = c;}
	}
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)     printf("%5d", a[i][j]);
		printf("\n");
	}
//	system("pause");
	Diliver2DArray(a, row);
}

int **Make2DArray(int row, int col)
{
	int **a, i;
	a = (int **)malloc(row * sizeof(int *));
	for (i = 0; i < row; i++)
		a[i] = (int *)malloc(col * sizeof(int));
	return a;
}

void Diliver2DArray(int **a, int row)
{
	int i;
	for (i = 0; i < row; i++)
		free(a[i]);
	free(a);
}
