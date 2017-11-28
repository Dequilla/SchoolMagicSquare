#include "Utility.h"

void clearInputBuffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

void strToLowerCase(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
		str[i] = (char)tolower(str[i]);
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
	
	for (int i = 0; validCharacters[i] != '\0'; i++)
		if (character == validCharacters[i])
			return TRUE;

	return FALSE;
}

char** createCArray2D(uint32 sizex, uint32 sizey)
{
	char** warray;
	warray = (char**)malloc(sizex * sizeof(char*));
	for (int i = 0; i < sizex; i++)
		warray[i] = (char*)malloc(sizey * sizeof(char));
	return warray;
}

void destroyCArray2D(char** warray, uint32 sizex)
{
	for (int i = 0; i < sizex; i++)
		free(warray[i]);
	free(warray);
}
