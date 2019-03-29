//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"
#include "searchTree_serial.h"
#include "searchTree_parallel.h"
#include "min.h"
#include "max.h"

#include "mpi.h"

//
// Standard includes
//

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

using namespace std;


//
// Function: buildTree
//

void searchTree( double *point, double rad, double *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes, string name ) {

	int q = 0, currentRank = 0, rootRank;
	MPI_Comm_size( comm, &q );
	MPI_Comm_rank( comm, &currentRank );
	MPI_Comm_rank( MPI_COMM_WORLD, &rootRank );

	int key = 50000 + (tree->depth) * 100;


	if( q > 1 ) {
		searchTree_parallel( point, rad, data, rows, cols, tree, comm, currentRank, q );

	} 
	else 
	{
		searchTree_serial( point, rad, *data, rows, cols, tree);
	}

}




