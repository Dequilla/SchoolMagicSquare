#include "Utility.h"

void strToLowerCase(char* str)
{
	int x = sizeof(str);
	for (int i = 0; str[i] != '\0'; i++)
		str[i] = tolower(str[i]); --> TODO
}

Bool withinRange1D(uint32 posx, uint32 range)
{
	return (posx >= 0 && posx <= range);
}

Bool withinRange2D(uint32 posx, uint32 posy, uint32 range)
{
	return (withinRange1D(posx, range) && withinRange1D(posy, range));
}

Bool isValidCharacter(char character, char* validCharacters)
{
	character = tolower(character);
	strToLowerCase(validCharacters);

	for (int i = 0; validCharacters[i] != '\0'; i++)
	{
		if (character == validCharacters[i])
			return TRUE;
	}
	return FALSE;
}
