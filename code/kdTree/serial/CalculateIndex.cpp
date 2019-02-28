//
// Standard includes
//

#include <string>
#include <iostream>
#include "definitions.h"

using namespace std;


//
// Local includes
//

#include "Tree.h"


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

unsigned long int Tree::CalculateIndex(string filename)
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
