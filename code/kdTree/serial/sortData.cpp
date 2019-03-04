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

void sortData(double *data, int numCols, int numRows, int dimension)
{
	auto start = std::chrono::system_clock::now();
	std::cout << "Before sort " << data[_X_] << " and " << data[numCols + _X_] << std::endl;

	switch (dimension)
	{
	case _X_:
		qsort(data, numRows, numCols * sizeof(double), compareX);
		break;

	case _Y_:
		qsort(data, numRows, numCols * sizeof(double), compareY);
		break;

	case _Z_:
		qsort(data, numRows, numCols * sizeof(double), compareZ);
		break;

	case _Index_:
		qsort(data, numRows, numCols * sizeof(double), compareIndex);
		break;

	default:
		cout << "Invalid dimenion " << to_string(dimension) << endl;
		exit(_FAIL_);
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << "After sort " << data[_X_] << " and " << data[numCols + _X_] << std::endl;
	std::cout << "Sorted " << numRows << " rows in " << elapsed.count() << " seconds" << std::endl;

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
	if (static_cast<const double *>(a)[_X_] < static_cast<const double *>(b)[_X_])
		return -1;

	if (static_cast<const double *>(a)[_X_] == static_cast<const double *>(b)[_X_])
		return 0;

	if (static_cast<const double *>(a)[_X_] > static_cast<const double *>(b)[_X_])
		return 1;
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
	if (static_cast<const double *>(a)[_Index_] < static_cast<const double *>(b)[_Index_])
		return -1;

	if (static_cast<const double *>(a)[_Index_] == static_cast<const double *>(b)[_Index_])
		return 0;

	if (static_cast<const double *>(a)[_Index_] > static_cast<const double *>(b)[_Index_])
		return 1;
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
	if (static_cast<const double *>(a)[_Z_] < static_cast<const double *>(b)[_Z_])
		return -1;

	if (static_cast<const double *>(a)[_Z_] == static_cast<const double *>(b)[_Z_])
		return 0;

	if (static_cast<const double *>(a)[_Z_] > static_cast<const double *>(b)[_Z_])
		return 1;
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
	if (static_cast<const double *>(a)[_Y_] < static_cast<const double *>(b)[_Y_])
		return -1;

	if (static_cast<const double *>(a)[_Y_] == static_cast<const double *>(b)[_Y_])
		return 0;

	if (static_cast<const double *>(a)[_Y_] > static_cast<const double *>(b)[_Y_])
		return 1;
}

