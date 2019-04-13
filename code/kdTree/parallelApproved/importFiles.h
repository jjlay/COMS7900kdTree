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
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	float *myData, int *rows, int *cols, 
	int maxRowsPerFile, unsigned long int arrayLimit);

