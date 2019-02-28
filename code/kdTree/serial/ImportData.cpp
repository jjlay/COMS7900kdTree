//
// Standard includes
//

#include <string>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <windows.h>


//
// Local includes
//

#include "Tree.h"
#include "definitions.h"


//
// Method: ImportData()
//

double *Tree::ImportData(string filename, int *numCols, int *numRows)
{
	// Start the clock!
	auto start = std::chrono::system_clock::now();

	*numCols = _MAX_COLS_;
	*numRows = 0;

	const char *cstrFileName = filename.c_str();
	cout << "Importing " << cstrFileName << endl;

	//
	// Read in file
	//

	if (!SetCurrentDirectory("C:/Users/jj.lay/source/github/COMS7900kdTree/code/kdTree/serial"))
	{
		cout << "Unable to change directories" << endl;
		exit(_FAIL_);
	}

	FILE *inFile;
	errno_t err = fopen_s(&inFile, cstrFileName, "r");

	if (err != 0)
	{
		exit(_FAIL_);
	}

	char tempString[10000];
	double tempX = 0.0, tempY = 0.0, tempZ = 0.0;

	long unsigned int lines = 0, offset = 0;
	auto maxLen = _countof(tempString);
	int recLen = 4; // Record length

	auto index = CalculateIndex(filename);
	auto array = new double[recLen * _MAX_ROWS_];

	while (fscanf_s(inFile, "%s %lf %lf %lf\n", tempString, maxLen, &array[offset + _X_], &array[offset + _Y_], &array[offset + _Z_]) != EOF)  // Windows
	// while (fscanf(inFile, "%s %lf %lf %lf\n", tempString, &array[offset + _X_], &array[offset + _Y_], &array[offset + _Z_]) != EOF)  // Linux
	{
		array[offset + _Index_] = static_cast<double>(index);

		offset += 4;
		lines++;
		index++;
	}

	fclose(inFile);

	*numRows = lines;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << "Read " << lines << " in " << elapsed.count() << " seconds" << std::endl;

	return array;
}
