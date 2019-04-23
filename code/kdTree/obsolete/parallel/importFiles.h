#pragma once

//
// importFiles
//


#undef _DEBUG_


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

//Data_COMS* importFiles(std::vector<std::string> files, int myRank);
void importFiles(string path, vector<string> files, int myRank,
	double *array, int *rows, int *cols, int maxRows);
	

