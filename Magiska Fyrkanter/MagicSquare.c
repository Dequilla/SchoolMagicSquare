#include "MagicSquare.h"
#include <stdlib.h>
#include <stdio.h>

Bool MS4_isValidCharacter(char character)
{
	const char* validCharacters = "0123456789abcdef";
	return isValidCharacter(character, validCharacters);
}

void MS4_initSquare(MagicSquare4* square)
{
	initMatrixC(&square->slots, MAGIC_SQUARE4_SIZE, MAGIC_SQUARE4_SIZE);
	initMatrixC(&square->solution, MAGIC_SQUARE4_SIZE, MAGIC_SQUARE4_SIZE);
}

void MS4_destroySquare(MagicSquare4* square)
{
	destroyMatrixC(&square->slots);
	destroyMatrixC(&square->solution);
}

void MS4_setSlot(MagicSquare4* square, uint8 posx, uint8 posy, char slot)
{
	// already makes sure it is within range through our matrix type
	if (MS4_isValidCharacter(slot))
	{
		setElementMatrixC(&square->slots, posx, posy, slot);
	}
}

void MS4_setSlotAndSol(MagicSquare4 * square, uint8 posx, uint8 posy, char slot)
{
	// already makes sure it is within range through our matrix type
	if (MS4_isValidCharacter(slot))
	{
		setElementMatrixC(&square->slots, posx, posy, slot);
		setElementMatrixC(&square->solution, posx, posy, slot);
	}
}

char MS4_readSlot(MagicSquare4* square, uint8 posx, uint8 posy)
{
	// already makes sure it is within range through our matrix type
	return getElementMatrixC(&square->slots, posx, posy);
}

void MS4_printSquare(MagicSquare4* square)
{
	printMatrixC(&square->slots);
}

void MS4_printSolution(MagicSquare4* square)
{
	printMatrixC(&square->solution);
}

void MS4_manualFill(MagicSquare4* square)
{
	char input = '?';
	for (int col = 0; col < MAGIC_SQUARE4_SIZE; col++)
	{
		for (int row = 0; row < MAGIC_SQUARE4_SIZE; row++)
		{
			do
			{
				CLEAR_CONSOLE();

				MS4_printSquare(square);

				printf_s("Please enter appropriate hex-number(0-F)\nfor column %d, row %d: ", col + 1, row + 1);
				scanf_s("%c", &input);
				clearInputBuffer();

				if (!MS4_isValidCharacter(input))
					printf_s("Invalid input!\n");
			} 
			while (!MS4_isValidCharacter(input));

			MS4_setSlot(square, col, row, input);
		}
	}
	
	CLEAR_CONSOLE();
	MS4_printSquare(square);
}

void MS4_fill(MagicSquare4* dest, MatrixC* src)
{
	// Make sure size is valid
	if (inRangeMatrixC(src, dest->slots.nColumns - 1, dest->slots.nRows - 1))
	{
		fillMatrixC(&dest->slots, src);
		fillMatrixC(&dest->solution, src);
	}
}

void MS4_fromFile(MagicSquare4* square, const char* filePath)
{
	char* file = readFileToStr(filePath); // Slaps a \0 to the end so we gucci

	// Interpret file
	uint8 column = 0;
	uint8 row = 0;
	for (uint32 counter = 0; file[counter] != '\0'; counter++)
	{
		char ele = file[counter];
		
		// aslong as ele is valid
		if (MS4_isValidCharacter(ele))
		{
			// Its valid, lets enter it!
			MS4_setSlotAndSol(square, column, row, ele);

			column++;
			// Col: 0,1,2,3,0,1,2,3
			if (0 == (column % MAGIC_SQUARE4_SIZE))
			{
				column = 0;
				row++;
				if (row >= 4)
				{
					// It is done
					break;
				}
			}
		}
	}

	free(file);
}

Bool MS4_isValidMatrixC(MatrixC* mat)
{
	// Checkes if this is a valid magic square matrix

	// Diagonals
	if (sumMainDiagonalAsHex(mat) != 30)
		return DEQ_FALSE;
	if (sumSecondDiagonalAsHex(mat) != 30)
		return DEQ_FALSE;

	// Columns
	for (int col = 0; col < mat->nColumns; col++)
	{
		if (sumColumnAsHex(mat, col) != 30)
			return DEQ_FALSE; // It failed
	}

	// Rows
	for (int row = 0; row < mat->nRows; row++)
	{
		if (sumRowAsHex(mat, row) != 30)
			return DEQ_FALSE; // It failed
	}

	return DEQ_TRUE; // It passed!
}

Bool MS4_isSolved(MagicSquare4* square)
{
	return MS4_isValidMatrixC(&square->slots);
}

Bool MS4_solutionIsValid(MagicSquare4* square)
{
	return MS4_isValidMatrixC(&square->solution);
}
