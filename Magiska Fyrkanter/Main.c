#include <stdio.h>

#include "MagicSquare.h"

void printFAQ(void);

int main(int argc, char** argv)
{
	// COLUMNS AND ROWS ARE SWITCHED UP SOMEWHERE; 
	// PROB IN READ AND PUT FUNCTIONS OR IN READING FROM FILE
	// Or in print? prob not doe
	// TODO: FIX (Program still works doe)
	// ALSO ADD SAVE TO FILE FEATURE'
	// ADD TO SOLUTION: SAME DIGITS CANNOT APPEAR MULTIPLE TIMES IN THE SQUARE

	MagicSquare4 mainSquare;
	MagicSquare4 testSquare;
	MS4_initSquare(&mainSquare);
	MS4_initSquare(&testSquare);

	char filePath[256] = "";

	int selection = -1;
	while (selection != 0)
	{
		int success = 0;
		filePath[3] = 0; // This is just to make sure loading files doesn't automaticly just quit
		
		CLEAR_CONSOLE();
		printf_s("Welcome to Edwin Wallins magic square program!\n");
		printf_s("Please choose what you want to do: (Select by entering a valid number)\n");
		printf_s("1. Enter a magic square manually.\n");
		printf_s("2. Save magic square to file.\n");
		printf_s("3. Read magic square from file.\n");
		printf_s("4. Play magic square game.\n");
		printf_s("5. Print currently loaded square.\n");
		printf_s("6. FAQ - What is a magic square?\n");
		printf_s("0. Quit!\n");
		printf_s("ENTER: ");
		scanf_s("%d", &selection);
		clearInputBuffer(); // Don't want to leave garbage behind

		switch (selection)
		{
		case 1:
			MS4_manualFill(&testSquare);
			
			if (MS4_solutionIsValid(&testSquare))
			{
				MS4_fill(&mainSquare, &testSquare.slots);
			}
			else
			{
				printf_s("Invalid square. Please retry.\n");
				system("PAUSE");
			}
			break;
		case 2:
			CLEAR_CONSOLE();
			printf_s("Too be implemented.\n");
			system("PAUSE");
			break;
		case 3:
			do
			{
				// TODO: Make sure it is a valid magic square(load to copy, don't overload mainSquare)
				CLEAR_CONSOLE();
				printf_s("Please enter the path to the file:\n(MAX: 255 characters, type \"quit\" to exit without loading)\nENTER: ");
				scanf_s("%s", &filePath, sizeof(char) * 255);
				clearInputBuffer(); // Don't want to leave garbage behind
				success = MS4_fromFile(&testSquare, filePath);
			} while (success == -1 && filePath[0] != 'q' && filePath[1] != 'u' && filePath[2] != 'i' && filePath[2] != 't');
			
			if (MS4_solutionIsValid(&testSquare))
			{
				MS4_fill(&mainSquare, &testSquare.slots);
			}
			else
			{
				printf_s("Invalid square. Please load another file.\n");
				system("PAUSE");
			}

			break;
		case 4:
			CLEAR_CONSOLE();
			printf_s("Too be implemented.\n");
			system("PAUSE");
			break;
		case 5:
			CLEAR_CONSOLE();
			MS4_printSquare(&mainSquare);
			system("PAUSE");
			break;
		case 6:
			printFAQ();
			break;
		case 0: break;
		default:
			printf_s("Invalid selection -> ");
			system("PAUSE");
		}
	}
	return 0;
}

void printFAQ(void)
{
	CLEAR_CONSOLE();
	printf_s(" --------------------- FAQ --------------------- \n");
	printf_s(" Q: What is a magic square? \n");
	printf_s(" A: A magic square is a square of which every\n");
	printf_s("    hexadecimal number only appears once and \n");
	printf_s("    where the columns, rows and long diagonals\n");
	printf_s("    are each summed to 30.\n");
	printf_s(" Q: What kind of magic square is this?\n");
	printf_s(" A: This program only supports 4x4 squares.\n");
	printf_s(" Q: Who made this?\n");
	printf_s(" A: A genius by the name of Edwin \"Dequilla\" Wallin.\n");
	printf_s("    (If a program says it, it must be true!)\n");
	printf_s(" --------------------- FAQ --------------------- \n");
	system("PAUSE");
}
