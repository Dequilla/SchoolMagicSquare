#include "Matrix.h"

Bool inRangeMatrixC(MatrixC * mat, uint32 col, uint32 row)
{
	// If col is BETWEEN -1 and nr of columns AND
	//    row is BETWEEN -1 and nr of rows
	return ((col >= 0 && col <= mat->nColumns - 1) &&
		   ( row >= 0 && row <= mat->nRows - 1));
}

Bool isSquareMatrixC(MatrixC * mat)
{
	return (mat->nRows == mat->nColumns);
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
	if (inRangeMatrixC(matDest, matSrc->nColumns - 1, matSrc->nRows - 1))
		memcpy(matDest, matSrc, (sizeof(uint32) * 2) + (sizeof(char) * matDest->nColumns * matDest->nRows));
		//						 nColumns + nRows + the actual matrix
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

uint32 sumColumnAsHex(MatrixC* mat, uint32 col)
{
	uint32 result = 0;
	for (int row = 0; row < mat->nRows; row++)
	{
		int temp = charhexToInt(getElementMatrixC(mat, col, row));
		if (temp != -1)
			result += temp;
	}
	return result;
}

uint32 sumRowAsHex(MatrixC* mat, uint32 row)
{
	uint32 result = 0;
	for (int col = 0; col < mat->nColumns; col++)
	{
		int temp = charhexToInt(getElementMatrixC(mat, col, row));
		if(temp != -1)
		{
			result += temp;
		}
	}
	return result;
}

uint32 sumMainDiagonalAsHex(MatrixC* mat)
{
	uint32 result = 0;
	if (isSquareMatrixC(mat))
	{
		for(int i = 0; i < mat->nRows; i++)
		{
			int temp = charhexToInt(getElementMatrixC(mat, i, i));
			if (temp != -1)
				result += temp;
		}
	}
	return result;
}

uint32 sumSecondDiagonalAsHex(MatrixC* mat)
{
	uint32 result = 0;
	int col = (mat->nColumns - 1);
	if (isSquareMatrixC(mat))
	{
		for (int i = 0; i < mat->nRows; i++)
		{
			// Col counts backwards whilst row counts normally
			int temp = charhexToInt(getElementMatrixC(mat, col - i, i));
			if (temp != -1)
				result += temp;
		}
	}
	return result;;
}
