//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"
#include "getSortDim.h"


//
// Standard includes
//

#include "mpi.h"
#include <iostream>
#include <math.h>

using namespace std;


//
// Function: buildTree
//

void buildTree_parallel( double *data, int rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes ) {
	
	if( rows > 1 ) {
		int sortDim = getSortDim( data, rows, cols, tree, myRank, numNodes, comm );
		
		cout << myRank << " " << sortDim << endl;
		
		
		
		
	} else {
		
		
		
		
		
		
	}
	
}




