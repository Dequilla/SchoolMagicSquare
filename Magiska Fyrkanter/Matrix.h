/**
* @file Matrix.h
* @author Edwin "Dequilla" Wallin
*/
#pragma once
#include <stdlib.h>
#include <string.h>

#include "Utility.h"

// Matrix of bytes(chars)
typedef struct
{
	char** matrix;	 /**< Our 4x4 matrix which we work on */
	uint32 nColumns; /**< The number of columns on this matrix */
	uint32 nRows;    /**< The number of rows on this matrix */
} MatrixC;

Bool inRangeMatrixC(MatrixC* mat, uint32 col, uint32 row);
Bool isSquareMatrixC(MatrixC* mat);

void initMatrixC(MatrixC* mat, uint32 nColumns, uint32 nRows);
void destroyMatrixC(MatrixC* mat);

void setElementMatrixC(MatrixC* mat, uint32 col, uint32 row, char element);
char getElementMatrixC(MatrixC* mat, uint32 col, uint32 row);

void fillMatrixC(MatrixC* matDest, MatrixC* matSrc);

void printMatrixC(MatrixC* mat);

/*
* \brief Interprets and sums the specified column as hexadecimal numbers
* @param mat The matrix to sum
* @param col The column to sum
*/
uint32 sumColumnAsHex(MatrixC* mat, uint32 col);

/*
* \brief Interprets and sums the specified row as hexadecimal numbers
* @param mat The matrix to sum
* @param row The row to sum
*/
uint32 sumRowAsHex(MatrixC* mat, uint32 row);

/*
* \brief Interprets and sums the second diagonal(left to right, top to bottom) as hexadecimal numbers
* @param mat The matrix to sum
*/
uint32 sumMainDiagonalAsHex(MatrixC* mat);

/*
* \brief Interprets and sums the second diagonal(right to left, top to bottom) as hexadecimal numbers
* @param mat The matrix to sum
*/
uint32 sumSecondDiagonalAsHex(MatrixC* mat);

/*
* \brief Counts the amount of times char c appears in this matrix
* @param mat The matrix to count the appearences in
* @param c The character to look for
*/
uint32 countMatrixC(MatrixC* mat, char c);