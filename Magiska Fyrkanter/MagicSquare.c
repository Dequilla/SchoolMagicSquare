#include "MagicSquare.h"
#include <stdlib.h>

Bool MS4_isValidCharacter(char character)
{
	char* validCharacters = "0123456789abcdf\0";
	return isValidCharacter(character, validCharacters);
}

void MS4_initSquare(MagicSquare4* square)
{
	// TODO: Write generalised 2D array initializer?
	square->slots = (char**)malloc(MAGIC_SQUARE4_SIZE * sizeof(char*));
	for (int i = 0; i < MAGIC_SQUARE4_SIZE; i++)
		square->slots[i] = (char*)malloc(MAGIC_SQUARE4_SIZE * sizeof(char));
}

void MS4_destroySquare(MagicSquare4* square)
{
	// TODO: Write generalised 2D array destroyer?
	for (int i = 0; i < MAGIC_SQUARE4_SIZE; i++)
		free(square->slots[i]);
	free(square->slots);
}

void MS4_setSlot(MagicSquare4* square, uint8 posx, uint8 posy, char slot)
{
	if (withinRange2D(posx, posy, MAGIC_SQUARE4_SIZE) &&
		MS4_isValidCharacter(slot))
	{
		square->slots[posx][posy] = slot;
	}
}
