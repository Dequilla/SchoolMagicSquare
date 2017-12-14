#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <time.h>

#include "Utility.h"
#include "MagicSquare.h"

#define MIN_REMOVED 1
#define MAX_REMOVED 8

/////////////////////
// Menu Items
/////////////////////

#define MENU_QUIT_GAME 0
#define MENU_ENTER_NUM 1
#define MENU_GET_HINT 2

#define MENU_LAST MENU_GET_HINT

/////////////////////
// Game Functions
/////////////////////

/*
* \brief The main loop and start of the game of magic squares
* @param square The square of which to play a game on
*/
void MS4_gameStart(MagicSquare4* square);

/*
* \brief Removes up to 8 diffrent numbers from the square
* @param square The square to remove numbers from (sets each selected slot to \0)
*/
void MS4_removeRandomNumbers(MagicSquare4* square);

/*
* \brief Prints the menu for this particular square (for use outside of game see function MS4_printSquare())
* @param sqaure The square which this game operates on
* @return Returns an integer that represents a selection in the menu
*/
int MS4_gameMenu(MagicSquare4* square);

/*
* \brief Prompts the user for two coordinates (returns DEQ_FALSE if it fails, ex: coordinates outside bounds)
* @param square The square to operate on
* @param column The column (x)
* @param row The row	   (y)
*/
Bool MS4_gameGetCoords(MagicSquare4* square, uint32* column, uint32* row);

/*
* \brief Prompts the user for which spot (x and y value) and what to enter into that spot
* @param square The square this game operates on
*/
void MS4_gameEnterNum(MagicSquare4* square);

/*
* \brief Prompts the user for what hint he/she wants and add's it to the square
* @param square The square this game operates on
*/
void MS4_gameGetHint(MagicSquare4* square);