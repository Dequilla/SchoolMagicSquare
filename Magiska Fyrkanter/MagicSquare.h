#pragma once
#include "Utility.h"

#include <stdio.h>

#define MAGIC_SQUARE4_SIZE 4

// 4x4 magic square
typedef struct
{
	char** slots;
} MagicSquare4;

Bool MS4_isValidCharacter(char character);

void MS4_initSquare(MagicSquare4* square);
void MS4_destroySquare(MagicSquare4* square);
void MS4_setSlot(MagicSquare4* square, uint8 posx, uint8 posy, char slot);
