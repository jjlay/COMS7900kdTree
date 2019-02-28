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

void Tree::SortData(double *data, int numCols, int numRows)
{
	auto start = std::chrono::system_clock::now();
	std::cout << "Before sort " << data[_X_] << " and " << data[numCols + _X_] << std::endl;

	qsort(data, numRows, numCols * sizeof(double), compareX);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << "After sort " << data[_X_] << " and " << data[numCols + _X_] << std::endl;
	std::cout << "Sorted " << numRows << " rows in " << elapsed.count() << " seconds" << std::endl;

}

