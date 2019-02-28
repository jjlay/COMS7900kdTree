//
// Local includes
//

#include "Tree.h"
#include "definitions.h"


//
// Standard includes
//

#include <iostream>
#include <chrono>


//
// Method: SortData()
//

void Tree::SortData(double *data, int numCols, int numRows, int dimension)
{
	auto start = std::chrono::system_clock::now();
	std::cout << "Before sort " << data[_X_] << " and " << data[numCols + _X_] << std::endl;

	switch (dimension)
	{
	case _X_ :
		qsort(data, numRows, numCols * sizeof(double), Tree::compareX);
		break;

	case _Y_ :
		qsort(data, numRows, numCols * sizeof(double), Tree::compareY);
		break;

	case _Z_ :
		qsort(data, numRows, numCols * sizeof(double), Tree::compareZ);
		break;

	case _Index_ :
		qsort(data, numRows, numCols * sizeof(double), Tree::compareIndex);
		break;

	default :
		cout << "Invalid dimenion " << to_string(dimension) << endl;
		exit(_FAIL_);
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << "After sort " << data[_X_] << " and " << data[numCols + _X_] << std::endl;
	std::cout << "Sorted " << numRows << " rows in " << elapsed.count() << " seconds" << std::endl;

}

