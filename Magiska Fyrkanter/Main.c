/**
* @file Main.c
* @author Edwin "Dequilla" Wallin
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "MagicSquare.h"
#include "Game.h"	

/////////////////////
// Menu Functions
/////////////////////
void manualFill(MagicSquare4* main);
void saveToFile(MagicSquare4* main);
void readFromFile(MagicSquare4* main);
void playGame(MagicSquare4* main);
void loadRandomSquare(MagicSquare4* main);
void printFAQ(void);
void printMenu(void);

int main(int argc, char** argv)
{
	MS4_init();

	MagicSquare4 mainSquare;
	MS4_initSquare(&mainSquare);

	int selection = -1;
	while (selection != 0)
	{
		
		CLEAR_CONSOLE();
		printMenu();
		printf("ENTER: ");
		scanf("%d", &selection);
		clearInputBuffer();

		switch (selection)
		{
		case 1:
			manualFill(&mainSquare);
			break;
		case 2:
			saveToFile(&mainSquare);
			break;
		case 3:
			readFromFile(&mainSquare);
			break;
		case 4:
			playGame(&mainSquare);
			break;
		case 5:
			CLEAR_CONSOLE();
			printf("Your currently loaded magic square: \n");
			MS4_printSquare(&mainSquare);
			PAUSE_CONSOLE();
			break;
		case 6:
			loadRandomSquare(&mainSquare);
			break;
		case 7:
			printFAQ();
			break;
		case 0: break;
		default:
			printf("Invalid selection -> ");
			PAUSE_CONSOLE();
		}
	}

	MS4_destroySquare(&mainSquare);
	MS4_quit();
	return 0;
}

void manualFill(MagicSquare4* main)
{
	CLEAR_CONSOLE();
	MagicSquare4 testSquare;
	MS4_initSquare(&testSquare);

	MS4_manualFill(&testSquare);

	if (MS4_solutionIsValid(&testSquare))
	{
		MS4_fill(main, &testSquare.slots);
	}
	else
	{
		printf("Invalid square. Please retry.\n");
		printf("ERROR: %s\n", MS4_getErrorString());
		PAUSE_CONSOLE();
	}

	MS4_destroySquare(&testSquare);
}

void saveToFile(MagicSquare4* main)
{
	CLEAR_CONSOLE();
	char filePath[256] = "";
	char cOverwrite = 'n';
	Bool bOverwrite = DEQ_FALSE;
	Bool success = DEQ_TRUE;

	do
	{
		CLEAR_CONSOLE();
		

		printf("Please enter the path to save to:\n(MAX: 255 characters, type \"quit\" to exit without saving)\nENTER: ");
		scanf("%s", &filePath);
		clearInputBuffer();

		if (filePath[0] == 'q' && filePath[1] == 'u' && filePath[2] == 'i' && filePath[3] == 't')
			break;

		printf("Do you want to overwrite \"%s\" if it exists?(Write y or Y for yes)\nENTER: ", filePath);
		scanf("%c", &cOverwrite);
		clearInputBuffer(); 

		bOverwrite = (tolower(cOverwrite) == 'y');

		MS4_toFile(main, filePath, bOverwrite);
		if (!success)
		{
			printf("Failed saving, either the path is taken or file could not open.\n");
			PAUSE_CONSOLE();
		}
	} while (success == DEQ_FALSE);

	PAUSE_CONSOLE();
}

void readFromFile(MagicSquare4* main)
{
	CLEAR_CONSOLE();
	MagicSquare4 testSquare;
	MS4_initSquare(&testSquare);

	char filePath[256] = "";
	
	Bool success = DEQ_FALSE;

	do
	{
		CLEAR_CONSOLE();
		printf("Please enter the path to the file:\n(MAX: 255 characters, type \"quit\" to exit without loading)\nENTER: ");
		scanf("%s", &filePath);
		clearInputBuffer();

		if (filePath[0] == 'q' && filePath[1] == 'u' && filePath[2] == 'i' && filePath[3] == 't')
			break;

		success = MS4_fromFile(&testSquare, filePath);
	} while (success == DEQ_FALSE);

	if (MS4_solutionIsValid(&testSquare))
	{
		MS4_fill(main, &testSquare.slots);
	}
	else if(filePath[0] != 'q' && filePath[1] != 'u' && filePath[2] != 'i' && filePath[3] != 't')
	{
		printf("Invalid square. Please load another file.\n");
		printf("ERROR: %s\n", MS4_getErrorString());
		PAUSE_CONSOLE();
	}

	MS4_destroySquare(&testSquare);
}

void playGame(MagicSquare4* main)
{
	CLEAR_CONSOLE();
	MS4_gameStart(main);
}

void loadRandomSquare(MagicSquare4* main)
{
	// Loads a random square from our squares folder
	MagicSquare4 testSquare;
	MS4_initSquare(&testSquare);

	uint8 squareNumber = randomInt(1, 11);

	char* path[20];
	char* number[21];
	intToStr(number, squareNumber);
	
	path[0] = '\0';
	strcat(path, "squares/sq");
	strcat(path, number);
	strcat(path, ".txt");

	MS4_fromFile(&testSquare, path);
	
	if (MS4_solutionIsValid(&testSquare))
	{
		MS4_fill(main, &testSquare.slots);

		printf("Loaded random square successfully!\n");
		PAUSE_CONSOLE();
	}
	else
	{
		printf("Failed to load a random square!\n");
		PAUSE_CONSOLE();
	}

	MS4_destroySquare(&testSquare);
}

void printFAQ(void)
{
	CLEAR_CONSOLE();
	printf(" --------------------- FAQ --------------------- \n");
	printf(" Q: What is a magic square? \n");
	printf(" A: A magic square is a square of which every\n");
	printf("    hexadecimal number only appears once and \n");
	printf("    where the columns, rows and long diagonals\n");
	printf("    are each summed to 30.\n");
	printf(" Q: What kind of magic square is this?\n");
	printf(" A: This program only supports 4x4 squares.\n");
	printf(" Q: Who made this?\n");
	printf(" A: A genius by the name of Edwin \"Dequilla\" Wallin.\n");
	printf("    (If a program says it, it must be true!)\n");
	printf(" --------------------- FAQ --------------------- \n");
	PAUSE_CONSOLE();
}

void printMenu(void)
{
	printf("Welcome to Edwin Wallins magic square program!\n");
	printf("Please choose what you want to do: (Select by entering a valid number)\n");
	printf("1. Enter a magic square manually.\n");
	printf("2. Save magic square to file.\n");
	printf("3. Read magic square from file.\n");
	printf("4. Play magic square game.\n");
	printf("5. Print currently loaded square.\n");
	printf("6. Load a random square.\n");
	printf("7. FAQ - What is a magic square?\n");
	printf("0. Quit!\n");
}