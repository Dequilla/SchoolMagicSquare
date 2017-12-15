/**
* @file Utility.h
* @author Edwin "Dequilla" Wallin
*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

// For access() and sleep()
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <io.h>
#include <Windows.h>
#endif

//////////////////////
// Type definitions
//////////////////////

typedef unsigned int	uint32;
typedef unsigned short	uint16;
typedef unsigned char	uint8;

typedef int		int32;
typedef short	int16;
typedef char	int8;

typedef enum 
{
	DEQ_FALSE = 0,
	DEQ_TRUE = 1
} Bool;

//////////////////////
// Helper functions
//////////////////////

#ifdef _WIN32
#define CLEAR_CONSOLE() system("cls")
#elif __linux__
#define CLEAR_CONSOLE() system("clear")
#else
#define CLEAR_CONSOLE() printf("\n\n")
#endif

#define PAUSE_CONSOLE() printf("Press \"Enter\" to continue..."); while(getchar() != '\n')

#ifdef _WIN32
#define SLEEP_CONSOLE(seconds) Sleep(seconds * 1000)
#elif __linux__
#define SLEEP_CONSOLE(seconds) sleep(seconds)
#else
#define SLEEP_CONSOLE(seconds) // Do nothing
#endif

/*
* \brief converts a int into a string
* IMPORTANT: Make sure the string you send in is longer than atleast 21 characters
* @param dest Destination string
* @param src Source integer
*/
void intToStr(char* dest, int src);

/*
* \brief Returns a random integer between min and max
* @param min Minimum value
* @param max Maximum value
*/
int32 randomInt(int32 min, int32 max);

/*
* \brief Returns true if specified file exists AND has read and write permissions
* @param filePath the path to the file
*/
Bool fileExists(char* filePath);

/*
* \brief Clears the input buffer of leftovers
*/
void clearInputBuffer(void);

/*
* \breif Completely changes input string to lowercase
* @param str The input string to lowercase
*/
void strToLowerCase(char* str); // May not need?

/*
* \brief Returns true if posx is within 0 - range
* @param posx The variable to be checked
* @param range The highest value posx can be and still return true
*/
Bool withinRange1D(uint32 posx, uint32 range);

/*
* \brief Returns true if posx and posy is within 0 - range
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

/*
* \brief Creates and returns a 2D array for chars
* @param sizex The number of columns
* @param sizey The number of rows
*/
char** createCArray2D(uint32 sizex, uint32 sizey); // Create one not based on type?

/*
* \brief Free memory of a 2D array for chars
* @param warray Array to be worked on
* @param sizex The number of columns
*/
void destroyCArray2D(char** warray, uint32 sizex);

/*
* \brief Copies src to dest
* IMPORTANT: It is fine if dest is bigger than src but not the other way around
* @param dest Destination array
* @param src Source array
* @param nrCols Number of columns in src
* @param nrRows Number of rows in src
*/
void copyCArray2D(char** dest, char** src, uint32 nrCols, uint32 nrRows);

/*
* \brief Reads a file into a c-styled string ending with \0
* IMPORTANT: Don't forget to free() the returned char* when you are done with it.
* @param path Path to the file that should be read
*/
char* readFileToStr(const char* path);

/*
* \brief Interprets a char as a integer
* IMPORTANT: Only does positive integers, returns -1 on failure
* @param in The character to be interpreted
*/
int charToInt(char in);

/*
* \brief Interprets a char as a hexadecimal and returns it as a normal integer
* IMPORTANT: Only does positive integers, returns -1 on failure
* @param hex The hexadecimal character
*/
int charhexToInt(char hex);

/*
* \brief converts an integer to a hexadecimal number
* Supports from 0-15 only, returns '?' on failure
* @param i The integer to convert
*/
char intToHex(uint8 i);

