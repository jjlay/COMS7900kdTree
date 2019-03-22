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
#include <string>

using namespace std;


//
// Function: buildTree
//

void buildTree(double *data, int rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes, string name ) {
	
	int q = 0, currentRank = 0;
	MPI_Comm_size( comm, &q );
	MPI_Comm_rank( comm, &currentRank );
	
	int key = 50000 + (tree->depth) * 100;


	if( q > 1 ) {
	//	cout << key << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank 
	//		<< " parallel named " << tree->name  << " q = " << q << " called by " << tree->name
	//		<< endl;
		buildTree_parallel( data, rows, cols, tree, comm, currentRank, q );
	} 
	else 
	{
		tree->name += "*";
	//	cout << key << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank 
	//		<< " serial named " << tree->name  << " q = " << q << " called by " << tree->name
	//		<< endl;
		//buildTree_serial( data, rows, cols, tree);
	}
	
}




