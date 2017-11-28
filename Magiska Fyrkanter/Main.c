#include <stdio.h>

#include "MagicSquare.h"

int main(int argc, char** argv)
{
	MagicSquare4 ms;
	MS4_initSquare(&ms);

	//MS4_manualFill(&ms);

	char* file = readFileToStr("test.txt");
	printf_s("FILE:\n%s", file);

	system("PAUSE");
	MS4_destroySquare(&ms);
	return 0;
}