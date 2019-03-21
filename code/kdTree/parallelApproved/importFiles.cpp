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


//
// Local includes
//
//

#include "definitions.h"

using namespace std;


// 
// Prototypes
//

double CalculateIndex(string filename);



//
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	double *myData, int *rows, int *cols, const int maxRowsPerFile,
	const int arrayLimit) {

	unsigned int arrayIndex = 0;
	*rows = 0;
		
	// loop through files to read
	for (auto f : files) {
		cout << "importFiles : Rank " << myRank << " Reading " << f << " : Rows " << *rows << " : arrayIndex " << arrayIndex 
			<< " : cols  " << *cols
			<< " : arrayLimit " << arrayLimit << endl;

		//
		// Read in file
		//

		const char *cstrFileName = f.c_str();
		cout << "importFiles : Importing " << cstrFileName << endl;

		// Open the file
		FILE *inFile;

		inFile = fopen(cstrFileName, "r");

		if (inFile == NULL)
		{
			cout << "importFiles : Failed to open file: " << f << endl;
			exit(_FAIL_);
		}

		const int maxFilenameLen = 10000;
		char tempString[maxFilenameLen];
		//double tempX = 0.0, tempY = 0.0, tempZ = 0.0;

		long unsigned int lines = 0;

		auto index = CalculateIndex(f);
		cout << "importFiles : Rank " << myRank << " Index is " << index << endl;

		//
		// Read in each row of the file and parse it.
		// We ignore the index column since it is corrupted, but instead
		// calculate the index based on the filename
		//

		while ((fscanf(inFile, "%s %lf %lf %lf\n", tempString, &myData[arrayIndex + _X_], 
			&myData[arrayIndex + _Y_], &myData[arrayIndex + _Z_]) != EOF) &&
			(lines < maxRowsPerFile) &&
			(arrayIndex < arrayLimit))
		{
			myData[arrayIndex + _INDEX_] = index;

			arrayIndex += 4;
			lines++;
			index++;
			(*rows)++;
		}

		fclose(inFile);

		cout << "importData : Rank " << myRank << " Finished " << cstrFileName << endl;
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
