#pragma once

#include <string>

using namespace std;


void importData(double *data, string filename, int *numCols, int *numRows, 
	const int maxRowsPerFile, const int arrayLimit);


