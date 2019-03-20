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
#include <iostream>
#include <fstream>

using namespace std;


//
// Local includes
//
//

#include "definitions.h"
#include "Data.h"


//
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	double *myData, int *rows, int *cols, const int maxRowsPerFile,
	const int arrayLimit);

