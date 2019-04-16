//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"
#include "buildTree_serial.h"
#include "buildTree_parallel.h"
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

void buildTree(float *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes, string name ) {

	int q = 0, currentRank = 0, rootRank;
	MPI_Comm_size( comm, &q );
	MPI_Comm_rank( comm, &currentRank );
	MPI_Comm_rank( MPI_COMM_WORLD, &rootRank );

	int key = 50000;

	if( q > 1 ) {
		float *array = data[0];
		buildTree_parallel( &array, rows, cols, tree, comm, currentRank, q );
		*data = array;
	} 
	else 
	{
		buildTree_serial( *data, rows, cols, tree);
	}

}
