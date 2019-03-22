//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"
#include "buildTree_serial.h"
#include "buildTree_parallel.h"

#include "mpi.h"

//
// Standard includes
//

#include <iostream>
#include <math.h>

using namespace std;


//
// Function: buildTree
//

void buildTree(double *data, int rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes ) {
	
	int q;
	MPI_Comm_size( comm, &q );
	
	int key = 50000 + (tree->depth) * 100;

	if( q > 1 ) {
		cout << key << " : " << __FUNCTION__ << " : Rank " << myRank << " parallel on communicator " << comm << endl;
		buildTree_parallel( data, rows, cols, tree, comm, myRank, q );
	} else {
		cout << key << " : " << __FUNCTION__ << " : Rank " << myRank << " serial " << " on communicataor " << comm << endl;
		//buildTree_serial( data, rows, cols, tree);
	}
	
}




