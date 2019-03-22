//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"
#include "getSortDim.h"
#include "buildTree.h"


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

void buildTree_parallel( double *data, int rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes ) {

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
	
	int numLeftNodes = numNodes / 2;
	int numRightNodes = numNodes - numLeftNodes;

//	cout << key << " : buildTree_parallel : Depth " << tree->depth << " Rank " << currentRank << ", Left nodes = " << numLeftNodes << ", Right nodes = " << numRightNodes << endl;

	// getSortDim crashes the code!
	int sortDim = getSortDim( data, rows, cols, tree, currentRank, numNodes, comm );
	
	int color = 0;

	if (myRank < numLeftNodes) {
	//	cout << key+1 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " is going left" << endl;
		tree->l = new Tree;
		tree->l->name = tree->name + "l";
		tree->r = nullptr;
		tree->rightComm = MPI_COMM_SELF;
		color = mpi_Color_Left;
		MPI_Comm tempComm = MPI_COMM_SELF;
		MPI_Comm_split(tree->thisComm, color, myRank, &tempComm);
		tree->leftComm = tempComm;
		
		int newRank = _Undefined_;
		MPI_Comm_rank( tempComm, &newRank );
		
		//cout << key+2 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " has a new communicator and is now rank " << newRank 
		//	<< " called " << tree->l->name << endl;

		tree->l->p = tree;
		tree->l->depth = tree->depth+1;
		tree->l->parentComm = tree->thisComm;
		tree->l->thisComm = tempComm;
		tree->l->l = nullptr;
		tree->l->r = nullptr;
		tree->l->leftComm = MPI_COMM_SELF;
		tree->l->rightComm = MPI_COMM_SELF;

		// cout << key+4 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " is calling buildTree" << endl;
		buildTree(data, rows, cols, tree->l, tree->l->thisComm, newRank, numLeftNodes, tree->l->name);
		// cout << key+5 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " has returned from buildTree" << endl;
	}
	else 
	// Split right
	{
	//	cout << key+10 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " is going right" << endl;
		tree->r = new Tree;
		tree->r->name = tree->name + "r";
		tree->l = nullptr;
		tree->leftComm = MPI_COMM_SELF;

		color = mpi_Color_Right;
		MPI_Comm tempComm = MPI_COMM_SELF;
		MPI_Comm_split(tree->thisComm, color, myRank, &tempComm);
		tree->rightComm = tempComm;

		int newRank = _Undefined_;
		MPI_Comm_rank(tempComm, &newRank);
		
	//	cout << key+11 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " has a new communicator and is now rank " << newRank 
	//		<< " called " << tree->r->name << endl;

		tree->r->p = tree;
		tree->r->depth = tree->depth+1;
		tree->r->parentComm = tree->thisComm;
		tree->r->thisComm = tempComm;
		tree->r->l = nullptr;
		tree->r->r = nullptr;
		tree->r->leftComm = MPI_COMM_SELF;
		tree->r->rightComm = MPI_COMM_SELF;

	//	cout << key+12 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " is calling buildTree" << endl;
		buildTree(data, rows, cols, tree->r, tree->r->thisComm, newRank, numRightNodes, tree->r->name);
	//	cout << key+13 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank << " has returned from buildTree" << endl;
	}

	// cout << "buildTree_parallel : Rank " << myRank 
	// 	<< ", Depth " << tree->depth
	// 	<< ", SortDim " << sortDim 
	// 	<< ", Joining COMM " << color
	// 	<< endl;	
}




