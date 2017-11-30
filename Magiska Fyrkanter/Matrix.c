#include "Matrix.h"

Bool inRangeMatrixC(MatrixC * mat, uint32 col, uint32 row)
{
	// If col is BETWEEN -1 and nr of columns AND
	//    row is BETWEEN -1 and nr of rows
	return ((col >= 0 && col <= mat->nColumns - 1) &&
		   ( row >= 0 && row <= mat->nRows - 1));
}

void initMatrixC(MatrixC* mat, uint32 nColumns, uint32 nRows)
{
	mat->nColumns = nColumns;
	mat->nRows = nRows;
	mat->matrix = createCArray2D(nColumns, nRows);
}

void destroyMatrixC(MatrixC* mat)
{
	destroyCArray2D(mat->matrix, mat->nColumns);
}

void setElementMatrixC(MatrixC* mat, uint32 col, uint32 row, char element)
{
	if(inRangeMatrixC(mat, col, row))
	{
		mat->matrix[col][row] = element;
	}
}

char getElementMatrixC(MatrixC* mat, uint32 col, uint32 row)
{
	if (inRangeMatrixC(mat, col, row))
	{
		return mat->matrix[col][row];
	}
	return '?';
}

void fillMatrixC(MatrixC* matDest, MatrixC* matSrc)
{
	// Make sure we are in-bounds
	if (inRangeMatrixC(matDest, matSrc->nColumns, matSrc->nRows))
		memcpy(matDest, matSrc, sizeof(char) * matDest->nColumns * matDest->nRows);
}

void printMatrixC(MatrixC* mat)
{
	printf_s("\n  .-------. \n");
	for (int col = 0; col < mat->nColumns; col++)
	{
		printf_s(" | ");

		for (int row = 0; row < mat->nRows; row++)
		{
			printf_s("%c ", mat->matrix[col][row]);
		}

		printf_s("| \n");
	}

	printf_s("  '-------' \n\n");
}
