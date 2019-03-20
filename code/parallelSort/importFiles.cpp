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
#include "Data.h"
#include "importData.h"

using namespace std;



//
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	double *myData, int *rows, int *cols, const int maxRowsPerFile,
	const int arrayLimit) {

	*cols = _ROW_WIDTH_;

	std::string homeDir = getenv("HOME");
	std::string prefix = homeDir + "/localstorage/public/coms7900-data/datafile";
	//const string prefix = "./data/datafile";
	const string suffix = ".txt";
	const double rowsPerFile = maxRowsPerFile;
	unsigned int arrayIndex = 0;
	
	// loop through files to read
	for (auto f : files) {
		
	}

	*rows = arrayIndex;
}


