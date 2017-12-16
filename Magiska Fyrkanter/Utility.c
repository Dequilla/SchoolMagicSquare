#include "Utility.h"

void intToStr(char* dest, int src)
{
	sprintf(dest, "%d", src);
}

int32 randomInt(int32 min, int32 max)
{
	return rand() % (max - min + 1) + min;
}

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

void copyCArray2D(char** dest, char** src, uint32 nrCols, uint32 nrRows)
{
	for (int col = 0; col < nrCols; col++)
	{
		for (int row = 0; row < nrRows; row++)
		{
			dest[col][row] = src[col][row];
		}
	}
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
		else
		{
			fclose(file);
			return NULL;
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
		return hex - '0'; // Ex med ’1’ = 49 i ASCII: 49 – 48 = 1  
	else if (isalpha(hex) && tolower(hex) >= 'a' && tolower(hex) <= 'f')
		return hex - 'a' + 10; // Ex med ’b’ = 98 i ASCII: 98 – 97 + 10 = 11
	
	return -1;
}

char intToHex(uint8 i)
{
	if (i > 15 || i < 0)
		return '?';
	else
	{
		
		if (i < 10) // 0-9
			return '0' + i; // 0 is at 48: ex: i = 5; 48 + 5 = 53 = '5'
		else if (i > 9) // 10-15
			return 'a' + (i - 10); // a is at 97: ex: i = 13; 97 + (13 - 10) = 97 + 3 = 100 = 'd'
	}
}
