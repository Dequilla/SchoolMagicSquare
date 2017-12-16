#include "MSCreate.h"

char** createHexRows(int n, int sum, int* nrOfRows)
{
	*nrOfRows = 0;
	char** result = createCArray2D(n, 1000);

	// IDEA: (does not work) let each slot have their own "part" of 16 so x1 = 0-3; x2 = 4-7; x3 = 8-11; x4 = 12-15;
	// This means we ONLY get permutations and not combinations
	for (int x1 = 0; x1 < 16; x1++)
	{
		for (int x2 = 0; x2 < 16; x2++)
		{
			for (int x3 = 0; x3 < 16; x3++)
			{
				for (int x4 = 0; x4 < 16; x4++)
				{
					// is it 30?
					if ((x1 + x2 + x3 + x4) == sum)
					{
						// TODO: check if a version of this already exists

						char row[4];
						row[0] = intToHex(x1);
						row[1] = intToHex(x2);
						row[2] = intToHex(x3);
						row[3] = intToHex(x4);
						
						// We got another match
						result[0][*nrOfRows] = row[0];
						result[1][*nrOfRows] = row[1];
						result[2][*nrOfRows] = row[2];
						result[3][*nrOfRows] = row[3];
						
						*nrOfRows += 1;
					}

				}
			}
		}
	}

	return result;
}

Bool existHexRow(char * row, uint32 length, char ** array2D, uint32 array2DLength)
{
	// Every row of array2D
	for (int a2d = 0; a2d < array2DLength; a2d++)
	{
		Bool existsInOther[4] = { DEQ_FALSE, DEQ_FALSE, DEQ_FALSE, DEQ_FALSE };

		for (int outer = 0; outer < length; outer++) // row
		{
			for (int inner = 0; inner < length; inner++) // array2D
			{
				if (row[outer] == array2D[a2d][inner])
				{
					existsInOther[outer] = DEQ_TRUE; // Exists in both
					break; // optimization
				}
			}

			// Optimization
			if (!existsInOther[outer])
				break; // This row is clean
		}

		if (existsInOther[0] == DEQ_TRUE &&
			existsInOther[1] == DEQ_TRUE &&
			existsInOther[2] == DEQ_TRUE &&
			existsInOther[3] == DEQ_TRUE)
		{
			return DEQ_TRUE;
		}
	}

	return DEQ_FALSE;
}
