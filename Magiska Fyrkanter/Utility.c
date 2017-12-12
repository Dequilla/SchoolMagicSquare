#include "Utility.h"

Bool fileExists(char * filePath)
{
// returns 0 on success which equals false so lets reverse that
#ifdef _WIN32
	return !_access(filePath, 6);
#elif __linux__
	return !access(filePath, R_OK | W_OK);
#else
	return DEQ_FALSE;
#endif
}

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
			return DEQ_TRUE;

	return DEQ_FALSE;
}

char** createCArray2D(uint32 sizex, uint32 sizey)
{
	char** warray;
	warray = (char**)calloc(sizex, sizex * sizeof(char*));
	for (int i = 0; i < sizex; i++)
		warray[i] = (char*)calloc(sizey, sizey * sizeof(char));
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
	else
	{
		return NULL;
	}

	return buffer;
}

int charToInt(char in)
{
	if (isdigit(in))
	{
		// the char 0 starts at spot 48, so if we remove it from the char
		// We should according to the C standard get the number
		// Example: in = '1' = 49
		//			return 49 - 48 = 1;
		return in - '0';
	}

	return -1;
}

int charhexToInt(char hex)
{
	if (isdigit(hex))
	{
		return charToInt(hex);
	}
	else if (isalpha(hex))
	{
		hex = tolower(hex);
		switch (hex)
		{
		case 'a':
			return 10;
		case 'b':
			return 11;
		case 'c':
			return 12;
		case 'd':
			return 13;
		case 'e':
			return 14;
		case 'f':
			return 15;
		}
	}
	else
	{
		return -1;
	}
}