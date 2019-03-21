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

double CalculateIndex(string filename);




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
// array. The array is a 1D array with each row located every _ROW_WIDTH_
// apart.
//

void importData(double *data, string filename, int *numCols, int *numRows, 
	const int maxRowsPerFile, const int arrayLimit, int myRank)
{
	//
	// Read in file
	//

	const char *cstrFileName = filename.c_str();
	cout << "importData : Importing " << cstrFileName << endl;

	// Open the file
	FILE *inFile;

	inFile = fopen(cstrFileName, "r");

	if (inFile == NULL)
	{
		cout << "importData : Failed to open file: " << filename << endl;
		exit(_FAIL_);
	}

	const int maxLen = 10000;
	char tempString[maxLen];
	double tempX = 0.0, tempY = 0.0, tempZ = 0.0;

	long unsigned int lines = 0, offset = 0;

	auto index = CalculateIndex(filename);
	cout << "importData : Rank " << myRank << " Index is " << index << endl;

	//
	// Read in each row of the file and parse it.
	// We ignore the index column since it is corrupted, but instead
	// calculate the index based on the filename
	//

	while ((fscanf(inFile, "%s %lf %lf %lf\n", tempString, &data[offset + _X_], 
		&data[offset + _Y_], &data[offset + _Z_]) != EOF) &&
		(lines < maxRowsPerFile))
	{
		data[offset + _INDEX_] = index;

		offset += 4;
		lines++;
		index++;
	}

	fclose(inFile);

	cout << "importData : Rank " << myRank << " Done with while loop" << endl;

	*numRows += lines;

	cout << "importData : Rank " << myRank << " Finished " << cstrFileName << endl;
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

double CalculateIndex(string filename)
{
	const string prefix = "datafile";
	const string suffix = ".txt";
	const int digitsInName = 5;
	
	int filenameLength = prefix.length() + digitsInName + suffix.length();
	int pathLength = filename.length() - filenameLength;

	string justName = filename.substr(pathLength, filenameLength);

	// How many characters is the numeric portion?
	auto len = justName.length() - prefix.length() - suffix.length();

	// Extract the numeric string
	auto s = justName.substr(prefix.length(), len);

	// Convert it to an integer. Filenames start with 1.
	auto n = stod(s) - 1;

	// Figure out the starting index
	double r = static_cast<double>(_MAX_ROWS_) * n;

	// cout << "File " << filename << " : " << s << " : " << justName << " : " << n << " : " << r << endl;

	return r;
}
