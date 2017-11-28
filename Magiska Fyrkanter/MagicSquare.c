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
	square->slots = createCArray2D(MAGIC_SQUARE4_SIZE, MAGIC_SQUARE4_SIZE);
	square->solution = createCArray2D(MAGIC_SQUARE4_SIZE, MAGIC_SQUARE4_SIZE);
}

void MS4_destroySquare(MagicSquare4* square)
{
	destroyCArray2D(square->slots, MAGIC_SQUARE4_SIZE);
	destroyCArray2D(square->solution, MAGIC_SQUARE4_SIZE);
}

void MS4_setSlot(MagicSquare4* square, uint8 posx, uint8 posy, char slot)
{
	// MAGIC_SQUARE4_SIZE - 1 since arrays go from 0 (0-3)
	if (withinRange2D(posx, posy, MAGIC_SQUARE4_SIZE - 1) &&
		MS4_isValidCharacter(slot))
	{
		square->slots[posx][posy] = tolower(slot);
	}
}

char MS4_readSlot(MagicSquare4* square, uint8 posx, uint8 posy)
{
	// MAGIC_SQUARE4_SIZE - 1 since arrays go from 0 (0-3)
	if(withinRange2D(posx, posy, MAGIC_SQUARE4_SIZE - 1))
		return square->slots[posx][posy];
	return '?';
}

void MS4_printSquare(MagicSquare4* square)
{
	printf_s("\n  .-------. \n");
	for (int col = 0; col < MAGIC_SQUARE4_SIZE; col++)
	{
		printf_s(" | ");
		
		for(int row = 0; row < MAGIC_SQUARE4_SIZE; row++)
		{ 
			printf_s("%c ", square->slots[col][row]);
		}
		
		printf_s("| \n");
	}

	printf_s("  '-------' \n\n");
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

void MS4_fromFile(MagicSquare4 * square, const char * filePath)
{

}
