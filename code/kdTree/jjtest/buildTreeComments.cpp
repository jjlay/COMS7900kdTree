//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"


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

void buildTree_parallel(float *data, int rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes ) {
	
	// tree.n = total number of data points
	
	// if tree.n > 1
		// Bcast len(data) from each worker
		// Bcast x,y,z min/max of all nodes
		// find global x,y,z min/max
		// get x,y,z widths
		// tree.c = center of box
		// sortDim = argmax( x,y,z widths )
		// store above calculations in tree.stuff
		
		// parallelSort( data, sortDim, myRank, numWorkers, ... )
		
		// split on worker that most evenly halves the data
		// workersL, workersR = arrays of ranks that will be on left or right
		// numL, numR = number of data points in L/R halves
		// if numL > 0
			// worldL = new comm_world using workersL
			// treeL = left child of tree (empty struct)
			// buildTree( data, xxx, cols, treeL, worldL )
			// tree.L = treeL
			// treeL.parent = tree
		// end
		// if numR > 0
			// worldR = new comm_world using workersR
			// treeR = left child of tree (empty struct)
			// buildTree( data, xxx, cols, treeR, worldR )
			// tree.R = treeR
			// treeR.parent = tree
		// end
	// else
		// tree.d = data[0:3]
		// tree.c = data[0:3]
		// tree.mins/maxs = data[whatever]
	// end
		
}


