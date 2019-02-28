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
	

	int rows = 0;
	int cols = 0;

	// Import the raw data
	auto data = ImportData(filename, &cols, &rows);

	cout << "Imported " << rows << " rows and " << cols << " columns" << endl;

	// Sort the data
	SortData(data, cols, rows, _X_);

	// Build the tree
	left = new Tree(this, data, cols, rows);
	right = new Tree(this, data, cols, rows);

	// Clean up our temporary array
	delete data;

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

Tree::Tree(Tree *parent, double *data, int numCols, int numRows)
{
	cout << "I am a child node" << endl;
	
}
