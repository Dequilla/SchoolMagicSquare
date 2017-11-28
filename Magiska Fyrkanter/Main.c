#include <stdio.h>

#include "MagicSquare.h"

int main(int argc, char** argv)
{
	MagicSquare4 ms;
	MS4_initSquare(&ms);

	MS4_manualFill(&ms);

	system("PAUSE");
	MS4_destroySquare(&ms);
	return 0;
}