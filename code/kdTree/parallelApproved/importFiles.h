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


using namespace std;



//
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	double *myData, int *rows, int *cols, int maxRows);

