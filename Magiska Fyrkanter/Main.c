#include <stdio.h>

#include "MagicSquare.h"

int main(int argc, char** argv)
{
	// COLUMNS AND ROWS ARE SWITCHED UP SOMEWHERE; 
	// PROB IN READ AND PUT FUNCTIONS OR IN READING FROM FILE
	// Or in print? prob not doe
	// TODO: FIX (Program still works doe)

	MagicSquare4 ms;
	MS4_initSquare(&ms);

	MS4_fromFile(&ms, "test_success.txt");
	MS4_printSquare(&ms);
	printf_s("Square is MAGIC: %s\n", (MS4_isSolved(&ms)) ? "TRUE" : "FALSE");

	system("PAUSE");
	MS4_destroySquare(&ms);
	return 0;
}