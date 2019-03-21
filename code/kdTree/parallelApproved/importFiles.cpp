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

#include "importData.h"

using namespace std;



//
// Function: importFiles
//

void importFiles(vector<string> files, int myRank,
	double *myData, int *rows, int *cols, const int maxRowsPerFile,
	const int arrayLimit) {

	//const string prefix = "./data/datafile";
	unsigned int arrayIndex = 0;
	*rows = 0;
		
	// loop through files to read
	for (auto f : files) {
		cout << "importFiles : Rank " << myRank << " Reading " << f << " : Rows " << *rows << " : arrayIndex " << arrayIndex 
			<< " : cols  " << *cols
			<< " : arrayLimit " << arrayLimit << endl;
		importData(&myData[arrayIndex], f, cols, rows, 
			maxRowsPerFile, arrayLimit, myRank);
		arrayIndex = *rows * *cols;
	}

	cout << "importFiles : Rank " << myRank << " finished with importFiles" << endl;
}


