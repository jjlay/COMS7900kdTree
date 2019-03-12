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
#include <stdio.h>
#include <chrono>


//
// Local includes
//
//

#include "definitions.h"
#include "Data.h"


using namespace std;


//
// Prototypes
//

unsigned long int CalculateIndex(string filename, unsigned long int maxRows);



//
// Function: importFiles
//

void importFiles(string path, vector<string> files, int myRank,
	double *myData, int *rows, int *cols, int maxRows) {

	cout << "importFiles: Rank " << myRank << " looking in " << path << endl;

	*cols = _ROW_WIDTH_;
	*rows = 0;
	int recLen = *cols; // Record length

	unsigned long int lines = 0;
	long unsigned int offset = 0;

	const int maxLen = 10000;
	char tempString[maxLen];

	// loop through files to read
	for (auto f : files) {

		const char *cstrFileName = f.c_str();
		cout << "importFiles: Rank " << myRank << " importing " << cstrFileName << endl;

		// Open the file
		FILE *inFile;

		inFile = fopen(cstrFileName, "r");

		if (inFile == NULL)
		{
			cout << "Failed to open file: " << f << endl;
			exit(_FAIL_);
		}

		auto index = CalculateIndex(f, maxRows);
		double dblIndex = static_cast<double>(index);

		//
		// Read in each row of the file and parse it.
		// We ignore the index column since it is corrupted, but instead
		// calculate the index based on the filename
		//

		while (fscanf(inFile, "%s %lf %lf %lf\n", tempString, &myData[offset + _X_], &myData[offset + _Y_], &myData[offset + _Z_]) != EOF)  // Linux
		{
			myData[offset] = dblIndex;

			offset += recLen;
			lines++;
			dblIndex++;
		}

		fclose(inFile);
	}

	*rows = lines;

	cout << "importFiles: Rank " << myRank << " read " << lines << endl;
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

unsigned long int CalculateIndex(string filename, unsigned long int maxRows)
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
	unsigned long int r = maxRows * n;

	return r;
}
