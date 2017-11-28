#include <stdio.h>

#include "MagicSquare.h"

int main(int argc, char** argv)
{

	MagicSquare4 ms;
	MS4_initSquare(&ms);

	MS4_setSlot(&ms, 0, 0, 'f');

	printf_s("%c \n", ms.slots[0][0]);

	system("PAUSE");
	MS4_destroySquare(&ms);
	return 0;
}