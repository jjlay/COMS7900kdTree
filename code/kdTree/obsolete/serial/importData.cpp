//
// Standard includes
//

#include <string>
#include <chrono>
#include <iostream>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;


//
// Local includes
//

#include "definitions.h"


// 
// Prototypes
//

unsigned long int CalculateIndex(string filename);




//
// Method: ImportData()
//
// Parameters:
//    filename - File to be imported
//    *numCols - Location to store the number of columns in the file
//    *numRows - Location to store the number of rows in the file
//
// Returns:
//    Pointer to a 1D array containing the data from the file
//
// Description:
//
// Imports the ASCII data from the requested file and stores it in an
// array. The array is a 1D array with each row located every _MAX_COLS_
// apart.
//

double *importData(string filename, int *numCols, int *numRows)
{
	// Start the clock!
	auto start = std::chrono::system_clock::now();

	*numCols = _MAX_COLS_;
	*numRows = 0;

	//
	// Read in file
	//

	const char *home;

	home = getenv("HOME");
	string strHome(home);

	cout << "Home: " << strHome << endl;
	auto fullPath = strHome + "/localstorage/public/coms7900-data/" + filename;

	const char *cstrFileName = fullPath.c_str();
	cout << "Importing " << cstrFileName << endl;

	// Open the file
	FILE *inFile;

	inFile = fopen(cstrFileName, "r");

	if (inFile == NULL)
	{
		cout << "Failed to open file: " << filename << endl;
		exit(_FAIL_);
	}

	const int maxLen = 10000;
	char tempString[maxLen];
	double tempX = 0.0, tempY = 0.0, tempZ = 0.0;

	long unsigned int lines = 0, offset = 0;
	int recLen = 4; // Record length

	auto index = CalculateIndex(filename);
	auto array = new double[recLen * _MAX_ROWS_];

	//
	// Read in each row of the file and parse it.
	// We ignore the index column since it is corrupted, but instead
	// calculate the index based on the filename
	//

	while (fscanf(inFile, "%s %lf %lf %lf\n", tempString, &array[offset + _X_], &array[offset + _Y_], &array[offset + _Z_]) != EOF)  // Linux
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

	cout << "Read " << lines << " in " << elapsed.count() << " seconds" << endl;

	return array;
}


//
// Method: CalculateIndex()
//
// Parameters:
//    filename - The filename to be imported
//
// Returns:
//    Starting index of first row
//
// Description:
//
// This function extracts the numeric part of the file name and
// calculates the starting index of the first row in the file.
//

unsigned long int CalculateIndex(string filename)
{
	string prefix = "datafile";
	string suffix = ".txt";

	// How many characters is the numeric portion?
	auto len = filename.length() - prefix.length() - suffix.length();

	// Extract the numeric string
	auto s = filename.substr(prefix.length(), len);

	// Convert it to an integer. Filenames start with 1.
	auto n = stoi(s) - 1;

	// Figure out the starting index
	unsigned long int r = _MAX_ROWS_ * n;

	return r;
}
