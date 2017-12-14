#include "Game.h"

void MS4_gameStart(MagicSquare4* square)
{
	// Make sure we have a playable square
	if (!MS4_solutionIsValid(square) && !MS4_isSolved(square))
	{
		printf("The loaded square is not a magic square!\nPlease load a proper magic square to play the game!\n");
		PAUSE_CONSOLE();
		CLEAR_CONSOLE();
		return;
	}

	printf("    Welcome to my magic square game!    \n");
	printf("----------------------------------------\n");
	printf("    We will now remove a random amount \n    of numbers from your previously \n    chosen square and you will have \n    to fill them in!\n\n");
	printf("             Good luck!\n\n");

	// First make a copy so we don't edit the one we have loaded in the main menu
	MagicSquare4 gameSquare;
	MS4_initSquare(&gameSquare);
	MS4_fill(&gameSquare, &square->slots);

	MS4_removeRandomNumbers(&gameSquare);
	PAUSE_CONSOLE();
	
	Bool running = DEQ_TRUE;
	while (running)
	{
		int selection = MS4_gameMenu(&gameSquare);

		switch (selection)
		{
		case MENU_QUIT_GAME:
			running = DEQ_FALSE;
			break;
		case MENU_ENTER_NUM:
			MS4_gameEnterNum(&gameSquare);
			break;
		case MENU_GET_HINT:
			MS4_gameGetHint(&gameSquare);
			break;
		}

		if (MS4_isSolved(&gameSquare))
		{
			CLEAR_CONSOLE();
			printf("Wohoooo! You solved it, congratulations!\n");
			SLEEP_CONSOLE(2);
			printf("Now to your price...\n");
			SLEEP_CONSOLE(2);
			printf("Drumrolls please...\n");
			SLEEP_CONSOLE(3);
			printf("You won: \n");
			SLEEP_CONSOLE(1);
			printf(".");
			SLEEP_CONSOLE(1);
			printf(".");
			SLEEP_CONSOLE(1);
			printf(".\n");
			SLEEP_CONSOLE(1);

			printf("The honor of solving this incredibly(not really) difficult puzzle!\n");
			SLEEP_CONSOLE(2);

			PAUSE_CONSOLE();

			running = DEQ_FALSE;
		}
	}

	MS4_destroySquare(&gameSquare);
}

void MS4_removeRandomNumbers(MagicSquare4* square)
{
	uint8 nrToRemove = randomInt(MIN_REMOVED, MAX_REMOVED);
	for (int i = 0; i < nrToRemove; i++)
	{
		uint8 col = randomInt(0, MAGIC_SQUARE4_SIZE - 1);
		uint8 row = randomInt(0, MAGIC_SQUARE4_SIZE - 1);

		setElementMatrixC(&square->slots, col, row, '\0');
	}
}

int MS4_gameMenu(MagicSquare4* square)
{
	int selection;
	do
	{
		CLEAR_CONSOLE();
		printf("Your current square contains %d holes!\n\n", countMatrixC(&square->slots, '\0'));
		MS4_printSquare(square);

		printf("What would you like to do?\n");
		printf("1. Enter a number\n");
		printf("2. Get a hint\n");
		printf("0. Quit game\n");
		printf("ENTER: ");
		scanf("%d", &selection);
		clearInputBuffer();
	} while (selection < 0 || selection > MENU_LAST);

	return selection;
}

Bool MS4_gameGetCoords(MagicSquare4* square, uint32* column, uint32* row)
{
	MS4_printSquare(square);

	uint32 tcolumn, trow;
	printf("What column? (1-4)\nENTER: ");
	scanf("%d", &tcolumn);
	clearInputBuffer();

	printf("What row? (1-4)\nENTER: ");
	scanf("%d", &trow);
	clearInputBuffer();

	if (!inRangeMatrixC(&square->slots, tcolumn - 1, trow - 1))
	{
		printf("You entered coordinates outside of the matrix. (%d, %d) does not exist in a 4x4 matrix.\n", tcolumn, trow);
		PAUSE_CONSOLE();
		return DEQ_FALSE;
	}
	else
	{
		*column = tcolumn;
		*row = trow;
		return DEQ_TRUE;
	}
}

void MS4_gameEnterNum(MagicSquare4* square)
{
	uint32 column, row;
	char c;

	CLEAR_CONSOLE();
	
	// If coordinates fail to be retrieved
	if (!MS4_gameGetCoords(square, &column, &row))
		return;

	do
	{
		printf("What hexadecimal number do you want to enter into (%d, %d)? (0-F)\nENTER: ", column, row);
		scanf("%c", &c);
		clearInputBuffer();
	} while (!MS4_isValidCharacter(c));

	char edit = 'y';
	if (MS4_readSlot(square, column - 1, row - 1) != '\0')
	{
		printf("(%d, %d) is not an empty slot, are you sure you want to edit it? (y/n)\nENTER: ", column, row);
		scanf("%c", &edit);
		clearInputBuffer();
	}

	if(edit == 'y' || edit == 'Y')
		MS4_setSlot(square, column - 1, row - 1, c);
}

void MS4_gameGetHint(MagicSquare4* square)
{
	uint32 column, row;
	char edit = 'y';

	CLEAR_CONSOLE();

	// If fails to get coordinates
	if (!MS4_gameGetCoords(square, &column, &row))
		return;

	// 1-4 (0-3)
	if (MS4_readSlot(square, column - 1, row - 1) != '\0')
	{
		printf("The slot you selected is already filled in.\nAre you sure you want a hint for that slot? (y/n)\nENTER: ");
		scanf("%c", &edit);
		clearInputBuffer();
	}

	if (edit == 'y' || edit == 'Y')
	{
		// 1-4 (0-3)
		char fromSolution = MS4_readSol(square, column - 1, row - 1);
		printf("The recommended solution for slot (%d, %d) is \"%c\"\n", column, row, fromSolution);
		printf("Do you want to use this hint? (y/n)\nENTER: ");
		scanf("%c", &edit);
		clearInputBuffer();
		
		if (edit == 'y' || edit == 'Y')
		{
			MS4_setSlot(square, column - 1, row - 1, fromSolution);
		}
	}
}
