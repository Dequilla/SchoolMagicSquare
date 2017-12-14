/**
* @file Matrix.h
* @author Edwin "Dequilla" Wallin
*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS

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

/*
* \brief Checks if specified column and specified row is within this matrix's bounds
* @param mat The matrix to check
* @param column The column index to check
* @param row The row index to check
*/
Bool inRangeMatrixC(MatrixC* mat, uint32 col, uint32 row);

/*
* \brief Checks if the number of columns is equal to the number of rows
* @param mat The matrix to check
*/
Bool isSquareMatrixC(MatrixC* mat);

/*
* \brief Initializes and gets the memory needed to a specified matrix
* @param mat The matrix to initialize
*/
void initMatrixC(MatrixC* mat, uint32 nColumns, uint32 nRows);

/*
* \brief Destroys and frees the memory of specified matrix
* @param mat The matrix to destroy
*/
void destroyMatrixC(MatrixC* mat);

/*
* \brief Sets an element of a matrix and makes sure it is within the bounds
* returns DEQ_FALSE if it fails, DEQ_TRUE otherwise
* @param mat The matrix to set the element in
* @param col The column to set
* @param row The row to set
* @param element The element to set the spot to
*/
Bool setElementMatrixC(MatrixC* mat, uint32 col, uint32 row, char element);

/*
* \brief Gets an element from a matrix and makes sure it is within the bounds of the matrix
* returns -1(as in the integer) if it fails otherwise it returns it's contents
* @param mat The matrix to retrieve from
* @param col The column to retrieve from
* @param row The row to retrieve from
*/
char getElementMatrixC(MatrixC* mat, uint32 col, uint32 row);

/*
* \brief Copies the contents of matSrc to matDest
* @param matDest The destination matrix
* @param matSrc The source matrix
*/
void fillMatrixC(MatrixC* matDest, MatrixC* matSrc);

/*
* \brief Prints the matrix in a pretty format
* @param mat The matrix to print
*/
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