#pragma once

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

using namespace std;


//
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	double *myData, int *rows, int *cols, const int maxRowsPerFile,
	const int arrayLimit);




