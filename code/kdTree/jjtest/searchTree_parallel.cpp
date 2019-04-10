//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"
#include "getSortDim.h"
#include "buildTree.h"

#include "parallelSort.h"

//
// Parallel includes
//

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

void searchTree_parallel( float *point, float rad, float *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes ) {

	MPI_Status mpiStatusResult;
	int mpiReturnValue;

	int currentRank = 0;
	mpiReturnValue = MPI_Comm_rank( tree->thisComm, &currentRank );

	if (mpiReturnValue != MPI_SUCCESS) {
		cout << "CRASH: " << __FUNCTION__ << " Line " << __LINE__ << endl;
		MPI_Abort(MPI_COMM_WORLD, _FAIL_);
		exit(_FAIL_);
	}

	int key = 50000 + (tree->depth * 100) + 5;
	
	
	
	
	
	
	
}




