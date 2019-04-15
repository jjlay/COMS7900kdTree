//
// importFiles
//

//
// STL includes
//

#include <vector>


//
// Standard includes
//

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>


//
// Local includes
//
//

#include "definitions.h"

using namespace std;


// 
// Prototypes
//

float CalculateIndex(string filename);



//
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	float *myData, int *rows, int *cols, 
	int maxRowsPerFile, unsigned long int arrayLimit) {

	*cols = _ROW_WIDTH_;

	unsigned int arrayIndex = 0;
	*rows = 0;
		
	// Debug
	float minX = 9999, maxX = -9999, minY = 9999, maxY = -9999, minZ = 9999, maxZ = -9999;

	// loop through files to read
	for (auto f : files) {
		//
		// Read in file
		//

		const char *cstrFileName = f.c_str();

		// Open the file
		FILE *inFile;

		inFile = fopen(cstrFileName, "r");

		if (inFile == NULL)
		{
			cout << "40000 : importFiles : Worker " << myRank << " failed to open file: " << f << endl;
			exit(_FAIL_);
		}

		const int maxFilenameLen = 10000;
		char tempString[maxFilenameLen];

		long unsigned int lines = 0;

		auto index = CalculateIndex(f);

		//
		// Read in each row of the file and parse it.
		// We ignore the index column since it is corrupted, but instead
		// calculate the index based on the filename
		//

		while ((fscanf(inFile, "%s %f %f %f\n", tempString, &myData[arrayIndex + _X_], 
			&myData[arrayIndex + _Y_], &myData[arrayIndex + _Z_]) != EOF) &&
			(lines < maxRowsPerFile) &&
			(arrayIndex < arrayLimit-4) &&
			(lines <_MAX_ROWS_))
		{
			if (myData[arrayIndex + _X_] < minX)
				minX = myData[arrayIndex + _X_];

			if (myData[arrayIndex + _X_] > maxX)
				maxX = myData[arrayIndex + _X_];

			if (myData[arrayIndex + _Y_] < minY)
				minY = myData[arrayIndex + _Y_];

			if (myData[arrayIndex + _Y_] > maxY)
				maxY = myData[arrayIndex + _Y_];

			if (myData[arrayIndex + _Z_] < minZ)
				minZ = myData[arrayIndex + _Z_];

			if (myData[arrayIndex + _Z_] > maxZ)
				maxZ = myData[arrayIndex + _Z_];

			myData[arrayIndex + _INDEX_] = index;

			arrayIndex += 4;
			lines++;
			index++;
			(*rows)++;
		}

		fclose(inFile);
	}

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

float CalculateIndex(string filename)
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
	float r = static_cast<float>(_MAX_ROWS_) * n;

	return r;
}

