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

char* readFileToStr(const char* path)
{
	char* buffer = 0;
	uint32 length = 0;

	// The b is just a procation to always assume 1 byte per char(portability)
	FILE* file = fopen(path, "rb");

	// If file successfully opened
	if (file)
	{
		// Go to end of file
		fseek(file, 0, SEEK_END);

		// Get the current position in the file stream
		length = ftell(file);

		// Return to the beginning
		rewind(file);

		// sizeof(char) redundant but makes it clearer
		// We add one to append \0 to indicate end of string
		buffer = malloc((length * sizeof(char)) + 1);
		
		// If memory successfully allocated
		if (buffer)
		{
			fread(buffer, sizeof(char), length, file);
			buffer[length] = '\0';
		}

		fclose(file);
	}

	return buffer;
}
