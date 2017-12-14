#include "MagicSquare.h"
#include <stdlib.h>
#include <stdio.h>

Bool MS4_isValidCharacter(char character)
{
	const char* validCharacters = "0123456789abcdef";
	return isValidCharacter(character, validCharacters);
}

void MS4_init(void)
{
	srand(time(NULL)); // Seed rand
	__MS4_errorString = calloc(MS4_ERROR_STRING_SIZE, sizeof(char) * MS4_ERROR_STRING_SIZE);
}

void MS4_quit(void)
{
	free(__MS4_errorString);
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
	if (MS4_isValidCharacter(slot))
	{
		setElementMatrixC(&square->slots, posx, posy, slot);
	}
}

void MS4_setSlotAndSol(MagicSquare4* square, uint8 posx, uint8 posy, char slot)
{
	if (MS4_isValidCharacter(slot))
	{
		setElementMatrixC(&square->slots, posx, posy, slot);
		setElementMatrixC(&square->solution, posx, posy, slot);
	}
}

char MS4_readSlot(MagicSquare4* square, uint8 posx, uint8 posy)
{
	return getElementMatrixC(&square->slots, posx, posy);
}

char MS4_readSol(MagicSquare4 * square, uint8 posx, uint8 posy)
{
	return getElementMatrixC(&square->solution, posx, posy);
}

void MS4_printSquare(MagicSquare4* square)
{
	printf("Magic Square: ");
	printf("\n0-9 and -> A = 10, B = 11, C = 12, D = 13, E = 14, F = 15\n");
	printMatrixC(&square->slots);
}

void MS4_printSolution(MagicSquare4* square)
{
	printf("Magic Square recommended solution: ");
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

				printf("Please enter appropriate hex-number(0-F)\nfor column %d, row %d: ", col + 1, row + 1);
				scanf("%c", &input);
				clearInputBuffer();

				if (!MS4_isValidCharacter(input))
					printf("Invalid input!\n");
			} 
			while (!MS4_isValidCharacter(input));

			MS4_setSlotAndSol(square, col, row, input);
		}
	}
	
	CLEAR_CONSOLE();
	MS4_printSquare(square);
}

void MS4_fill(MagicSquare4* dest, MatrixC* src)
{
	if (inRangeMatrixC(src, dest->slots.nColumns - 1, dest->slots.nRows - 1))
	{
		fillMatrixC(&dest->slots, src);
		fillMatrixC(&dest->solution, src);
	}
}

Bool MS4_fromFile(MagicSquare4* square, const char* filePath)
{
	char* file = readFileToStr(filePath);

	if(file != NULL)
	{
		// Interpret file
		uint8 column = 0;
		uint8 row = 0;
		for (uint32 counter = 0; file[counter] != '\0'; counter++)
		{
			char ele = file[counter];

			if (MS4_isValidCharacter(ele))
			{
				MS4_setSlotAndSol(square, column, row, ele);

				row++;

				// Col: 0,1,2,3,0,1,2,3
				if (0 == (row % MAGIC_SQUARE4_SIZE))
				{
					row = 0;
					column++;
					if (column >= 4)
					{
						// It is done
						break;
					}
				}
			}
		}
		free(file);
		return DEQ_TRUE;
	}
	else
	{
		free(file);
		return DEQ_FALSE;
	}
}

void MS4_toString(MagicSquare4* square, char* dest)
{
	int counter = 0;
	for (int col = 0; col < square->slots.nColumns; col++)
	{
		for (int row = 0; row < square->slots.nRows; row++)
		{
			dest[counter] = MS4_readSlot(square, col, row);
			counter++;

			if(counter % 5 == 4 && counter != 19) // 4, 9, 14
			{
				dest[counter] = '|'; // Just for nicer formatting
				counter++;
			}
		}
	}
	dest[19] = '\0'; // Finnish string
}

Bool MS4_toFile(MagicSquare4* square, const char * filePath, Bool overwrite)
{
	Bool fileExist = fileExists(filePath);

	if (!overwrite && fileExist)
	{
		return DEQ_FALSE;
	}
	
	FILE* file = fopen(filePath, "w");

	if (file != NULL)
	{
		char* matrix[20];
		MS4_toString(square, matrix);
		fputs(matrix, file);
		fclose(file);
	}
	else
	{
		return DEQ_FALSE; // Could not open file
	}

	return DEQ_TRUE;
}

Bool MS4_isValidMatrixC(MatrixC* mat)
{
	// Checks if this is a valid magic square matrix

	// Make sure every character only appears ONCE
	// For how the for-loop works check a ASCII table out
	for (char test = '0'; test <= '9'; test++)
	{
		// Handles both if too many and too little
		if (countMatrixC(mat, test) > 1 || countMatrixC(mat, test) < 1)
		{
			__MS4_errorString[1] = '\0'; // Reset string
			__MS4_errorString[0] = test;
			strcat(__MS4_errorString, " <- Appears too many or too few times.");
			return DEQ_FALSE;
		}
	}

	for (char test = 'a'; test <= 'f'; test++)
	{
		// Handles both if too many and too little
		if (countMatrixC(mat, test) > 1 || countMatrixC(mat, test) < 1)
		{
			__MS4_errorString[1] = '\0'; // Reset string
			__MS4_errorString[0] = test;
			strcat(__MS4_errorString, " <- Appears too many or too few times.");
			return DEQ_FALSE;
		}
	}

	// Diagonals
	if (sumMainDiagonalAsHex(mat) != 30)
	{
		__MS4_errorString[0] = '\0'; // Reset string
		strcat(__MS4_errorString, "Main diagonal's sum is too big."); // Max 49 chars
		return DEQ_FALSE;
	}
	if (sumSecondDiagonalAsHex(mat) != 30)
	{
		__MS4_errorString[0] = '\0'; // Reset string
		strcat(__MS4_errorString, "Second diagonal's sum is too big."); // Max 49 chars
		return DEQ_FALSE;
	}

	// Columns
	for (int col = 0; col < mat->nColumns; col++)
	{
		if (sumColumnAsHex(mat, col) != 30)
		{
			__MS4_errorString[0] = '\0'; // Reset string
			strcat(__MS4_errorString, "One of the columns sum is bigger than 30."); // Max 49 chars
			return DEQ_FALSE;
		}
	}

	// Rows
	for (int row = 0; row < mat->nRows; row++)
	{
		if (sumRowAsHex(mat, row) != 30)
		{
			__MS4_errorString[0] = '\0'; // Reset string
			strcat(__MS4_errorString, "One of the rows sum is bigger than 30."); // Max 49 chars
			return DEQ_FALSE;
		}
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

char* MS4_getErrorString(void)
{
	return __MS4_errorString;
}
