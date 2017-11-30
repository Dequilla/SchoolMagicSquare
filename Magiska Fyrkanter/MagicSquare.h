#pragma once
#include "Utility.h"
#include "Matrix.h"

#include <stdio.h>

#define MAGIC_SQUARE4_SIZE 4

// 4x4 magic square
typedef struct
{
	MatrixC slots;	  // Our 4x4 matrix which we work on
	MatrixC solution; // Our 4x4 matrix recommended solution
} MagicSquare4;

/*
* \brief Checks wether or not character is valid in this kind of magic square
* Valid characters are "0123456789ABCDEF"
* This function is NOT case sensetive
* @param character The char to check
*/
Bool MS4_isValidCharacter(char character);

/*
* \brief Initializes a magic square(4x4 matrix)
* @param square The magic square to initialize
*/
void MS4_initSquare(MagicSquare4* square);

/*
* \brief Destroys and frees memory of a magic square(4x4 matrix)
* @param square The magic square to destroy
*/
void MS4_destroySquare(MagicSquare4* square);

/*
* \brief Sets one of the values in this square to the char of slot
* @param square The magic square to work on
* @param posx The column to act upon (0 - 3)
* @param posy The row to act upon (0 - 3)
* @param slot The character to add to the slot
*/
void MS4_setSlot(MagicSquare4* square, uint8 posx, uint8 posy, char slot);

/*
* \brief Sets one of the values in this square to the char of slot on BOTH the internal matricies
* @param square The magic square to work on
* @param posx The column to act upon (0 - 3)
* @param posy The row to act upon (0 - 3)
* @param slot The character to add to the slots
*/
void MS4_setSlotAndSol(MagicSquare4* square, uint8 posx, uint8 posy, char slot);

/*
* \brief Reads and returns a character in slot [posx][posy] on success, '?' on failure
* @param square The magic square to work on
* @param posx The column to act upon (0 - 3)
* @param posy The row to act upon (0 - 3)
*/
char MS4_readSlot(MagicSquare4* square, uint8 posx, uint8 posy);

/*
* \brief Prints our magic square
* @param square The magic square to work on
*/
void MS4_printSquare(MagicSquare4* square);

/*
* \brief Prints our magic square's recommended solution
* @param square The magic square to work on
*/
void MS4_printSolution(MagicSquare4* square);

/*
* \brief Manually prompts user for values to enter into the square
* @param square The magic square to work on
*/
void MS4_manualFill(MagicSquare4* square);

/*
* \brief Fills the square with values from a matrix (both slots and solution)
* @param dest The magic square to work on
* @param src The matrix to pick elements from
*/
void MS4_fill(MagicSquare4* dest, MatrixC* src);

/*
* \brief Reads magic square from file(only reads one of the squares, if  you have multiple it is the last one)
* @param square The magic square to work on
* @param filePath The path to the file to read
*/
int MS4_fromFile(MagicSquare4* square, const char* filePath);

/*
* \brief Checks if a matrix is a valid hexadecimal magic square
* @param mat The matrix to check
*/
Bool MS4_isValidMatrixC(MatrixC* mat);

/*
* \brief Checks if a magic square is solved
* @param square The square to check
*/
Bool MS4_isSolved(MagicSquare4* square); 

/*
* \brief Checks if this squares solution is valid
* @param square The square to check
*/
Bool MS4_solutionIsValid(MagicSquare4* square);
