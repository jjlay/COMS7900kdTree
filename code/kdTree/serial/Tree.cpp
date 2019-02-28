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
// Constructor
//

Tree::Tree() {
	// Constructor
	
}


//
// Constructor that accepts file to import
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


	// Clean up our temporary array
	delete data;

}

