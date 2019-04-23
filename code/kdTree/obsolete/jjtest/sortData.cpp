//
// Local includes
//

#include "definitions.h"


//
// Standard includes
//

#include <iostream>
#include <chrono>
#include <string>

using namespace std;


//
// Prototypes
//

int compareIndex(const void *a, const void *b);
int compareX(const void *a, const void *b);
int compareY(const void *a, const void *b);
int compareZ(const void *a, const void *b);


//
// Method: SortData()
//
// Parameters:
//    data - Array of data to be sorted
//    numCols - Number of columns in each row
//    numRows - Number of rows in the data
//    dimension - Dimension to be sorted on (see definions.h)
//
// Returns:
//    The data is sorted in place in the data array
//
// Description:
//
// This method uses the qsort function and depends on the four
// comparison methods (compareX, compareY, compareZ, compareIndex).
//

void sortData(float *data, int numCols, int numRows, int dimension)
{
	// auto start = std::chrono::system_clock::now();

	switch (dimension)
	{
	case _X_:
		qsort(data, numRows, numCols * sizeof(float), compareX);
		break;

	case _Y_:
		qsort(data, numRows, numCols * sizeof(float), compareY);
		break;

	case _Z_:
		qsort(data, numRows, numCols * sizeof(float), compareZ);
		break;

	case _INDEX_:
		qsort(data, numRows, numCols * sizeof(float), compareIndex);
		break;

	default:
		cout << "Invalid dimenion " << to_string(dimension) << endl;
		exit(_FAIL_);
	}

	// auto end = std::chrono::system_clock::now();
	// std::chrono::duration<float> elapsed = end - start;

	// std::cout << "Sorted " << numRows << " rows in " << elapsed.count() << " seconds" << std::endl;

}



//
// Function: compareX()
//
// Parameters:
//    a - First value to compare
//    b - Second value to compare
//
// Returns:
//    Returns -1 if a < b
//             0 if a = b
//             1 if a > b
//

int compareX(const void *a, const void *b)
{
	if (static_cast<const float *>(a)[_X_] < static_cast<const float *>(b)[_X_])
		return -1;

	if (static_cast<const float *>(a)[_X_] == static_cast<const float *>(b)[_X_])
		return 0;

	if (static_cast<const float *>(a)[_X_] > static_cast<const float *>(b)[_X_])
		return 1;

	return 0;
}




//
// Method: compareIndex()
//
// Parameters:
//    a - First value to compare
//    b - Second value to compare
//
// Returns:
//    Returns -1 if a < b
//             0 if a = b
//             1 if a > b
//

int compareIndex(const void *a, const void *b)
{
	if (static_cast<const float *>(a)[_INDEX_] < static_cast<const float *>(b)[_INDEX_])
		return -1;

	if (static_cast<const float *>(a)[_INDEX_] == static_cast<const float *>(b)[_INDEX_])
		return 0;

	if (static_cast<const float *>(a)[_INDEX_] > static_cast<const float *>(b)[_INDEX_])
		return 1;
	
	return 0;
}



//
// Function: compareZ()
//
// Parameters:
//    a - First value to compare
//    b - Second value to compare
//
// Returns:
//    Returns -1 if a < b
//             0 if a = b
//             1 if a > b
//

int compareZ(const void *a, const void *b)
{
	if (static_cast<const float *>(a)[_Z_] < static_cast<const float *>(b)[_Z_])
		return -1;

	if (static_cast<const float *>(a)[_Z_] == static_cast<const float *>(b)[_Z_])
		return 0;

	if (static_cast<const float *>(a)[_Z_] > static_cast<const float *>(b)[_Z_])
		return 1;
	
	return 0;
}


//
// Function: compareY()
//
// Parameters:
//    a - First value to compare
//    b - Second value to compare
//
// Returns:
//    Returns -1 if a < b
//             0 if a = b
//             1 if a > b
//

int compareY(const void *a, const void *b)
{
	if (static_cast<const float *>(a)[_Y_] < static_cast<const float *>(b)[_Y_])
		return -1;

	if (static_cast<const float *>(a)[_Y_] == static_cast<const float *>(b)[_Y_])
		return 0;

	if (static_cast<const float *>(a)[_Y_] > static_cast<const float *>(b)[_Y_])
		return 1;
	
	return 0;
}


