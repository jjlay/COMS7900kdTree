//
// importFiles
//


#undef _DEBUG_


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
// #include "Data.h"

//
// Function: buildTree
//

void buildTree(double *data, Tree tree ) {
	
	// THIS FILE JUST CONTAINS COMMENTS FOR NOW
	
	// get number of data points
	
	// if n > 1
		// this is not a leaf
		
		// get/store min, max, range, center
		
		// get sort dimension
		
		// sort data, get split index/value
		
		// split data --> dataL, dataR

		// if dataL is not empty
			// init treeL
			// treeL.parent = tree
			// tree.left = treeL
			// buildTree( dataL, treeL )
		// end
		// if dataR is not empty
			// init treeR
			// treeR.parent = tree
			// tree.right = treeR
			// buildTree( dataR, treeR )
		// end
		
	// else
		// this is a leaf
		
		// tree.data = data // this should still be an array, but of length 1 (or 4 if we're still doing blocks
		
		// tree.center = data
		
	// end
	
}
