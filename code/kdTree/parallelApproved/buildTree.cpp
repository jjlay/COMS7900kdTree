//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"

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

void buildTree(double *data, int rows, int cols, Tree *tree, MPI_Comm comm) {
	
	int q;
	MPI_Comm_size( comm, &q );
	
	if( q > 1 ) {
		cout << "parallel" << endl;
		// buildTree_parallel( ... )
	} else {
		cout << "seriall" << endl;
		// buildTree_serial( ... )
	}
	
}




