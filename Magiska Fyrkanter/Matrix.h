#pragma once
#include <stdlib.h>
#include <string.h>

#include "Utility.h"

// Matrix of bytes(chars)
typedef struct
{
	char** matrix;
	uint32 nColumns;
	uint32 nRows;
} MatrixC;

Bool inRangeMatrixC(MatrixC* mat, uint32 col, uint32 row);

void initMatrixC(MatrixC* mat, uint32 nColumns, uint32 nRows);
void destroyMatrixC(MatrixC* mat);

void setElementMatrixC(MatrixC* mat, uint32 col, uint32 row, char element);
char getElementMatrixC(MatrixC* mat, uint32 col, uint32 row);

void fillMatrixC(MatrixC* matDest, MatrixC* matSrc);

void printMatrixC(MatrixC* mat);