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

char MS4_readSlot(MagicSquare4* square, uint8 posx, uint8 posy)
{
	// already makes sure it is within range through our matrix type
	return getElementMatrixC(&square->slots, posx, posy);
}

void MS4_printSquare(MagicSquare4* square)
{
	printMatrixC(&square->slots);
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
	if (inRangeMatrixC(src, dest->slots.nColumns, dest->slots.nRows))
	{
		fillMatrixC(&dest->slots, src);
		fillMatrixC(&dest->solution, src);
	}
}

void MS4_fromFile(MagicSquare4* square, const char* filePath)
{
}
