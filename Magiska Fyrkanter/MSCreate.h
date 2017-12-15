#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Utility.h"

////////////////////////////////////
// Create part of all magic squares
////////////////////////////////////

// I did sadly not have time to  finnish this :(

/*
* \brief Creates a 2D array and fills it with every n-long array of combinations of hexadecimal numbers that add up to 30
* @param n The length of the arrays
* @param sum The sum which each row needs to be equal to
* @param nrOfRows to retrieve the number of rows it eventually outputs
*/
char** createHexRows(int n, int sum, int* nrOfRows);

/*
* \brief Checks if row exists in array2D without consideration for order so fff1 == 1fff
* IMPORTANT: Make sure your row length is equal to the number of columns in array2D
* @param row the row of length characters to be checked for
* @param length the length of the row ex: ffff = 4
* @param array2D The 2D array to go through and check for row
* @param array2DLength The number of rows of array2D
*/
Bool existHexRow(char* row, uint32 length, char** array2D, uint32 array2DLength);