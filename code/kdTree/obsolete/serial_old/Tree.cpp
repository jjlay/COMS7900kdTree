//
// Local includes
//

#include "Tree.h"
#include "definitions.h"


//
// Standard includes 
//

#include <string>
#include <iostream>
#include <chrono>

using namespace std;


//
// Constructor that accepts file to import
//
// Parameters:
//    filename - Filename containing data to import
//
// Returns:
//    Nothing
// 
// Description:
//
// This constructor is called by the main function to begin the 
// tree construction process. It reads in the data, sorts it,
// and builds the tree using the second constructor.
//

Tree::Tree(string filename) {
	auto start = std::chrono::system_clock::now();

	int rows = 0;
	int cols = 0;

	// Import the raw data
	auto data = ImportData(filename, &cols, &rows);

	cout << "Imported " << rows << " rows and " << cols << " columns" << endl;

	// Sort the data
	SortData(data, cols, rows, _X_);

	// Split the data

	int leftRows = rows / 2;
	int rightRows = rows - leftRows;

	unsigned long int leftElements = leftRows * cols;
	unsigned long int rightElements = (cols * rows) - leftElements;

	// Build the tree
	left = new Tree(this, data, cols, leftRows);
	right = new Tree(this, &data[leftElements], cols, rightRows);

	// Clean up our temporary array
	delete data;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Built tree with " << rows << " rows in " << elapsed.count() << " seconds" << std::endl;
}


//
// Constructor for creating child nodes
//
// Parameters:
//    parent - Pointer to the node above this one
//    data - Subset of the file to be managed by this node
//    numCols - Number of columns in each row
//    numRows - Number of rows in the subset
//
// Returns:
//    Nothing
// 
// Description:
//
// This constructor is called by the other constructor and is used to
// create the child nodes from a subset of the data.
//

Tree::Tree(Tree *parent, double *data, int cols, int rows)
{
	if (rows > 1) {
		// Split the data

		int leftRows = rows / 2;
		int rightRows = rows - leftRows;

		unsigned long int leftElements = leftRows * cols;
		unsigned long int rightElements = (cols * rows) - leftElements;

		// Build the tree
		left = new Tree(this, data, cols, leftRows);
		right = new Tree(this, &data[leftElements], cols, rightRows);
	}
	else
	{
		// We are at the end!
	}
}
