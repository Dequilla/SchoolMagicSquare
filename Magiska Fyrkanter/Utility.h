#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef unsigned int	uint32;
typedef unsigned short	uint16;
typedef unsigned char	uint8;

typedef int		int32;
typedef short	int16;
typedef char	int8;

typedef enum 
{
	FALSE = 0,
	TRUE = 1
} Bool;
/*
* \breif Completely changes input string to lowercase
* @param str The input string to lowercase
*/
void strToLowerCase(char* str);

/*
* \brief Returns true if posx is within 0 to range
* @param posx The variable to be checked
* @param range The highest value posx can be and still return true
*/
Bool withinRange1D(uint32 posx, uint32 range);

/*
* \brief Returns true if posx and posy is within 0 to range
* @param posx The first variable to be checked
* @param posy The second variable to be checked
* @param range The highest value posx and posy can be and still return true
*/
Bool withinRange2D(uint32 posx, uint32 posy, uint32 range);

/*
* \breif Returns true if character is also in the validCharacters string
* @param character The character being checked if valid
* @param validCharacters The string containing all valid characters 
*/
Bool isValidCharacter(char character, char* validCharacters);