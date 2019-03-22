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
	int key = 50000 + (tree->depth * 100) + 5;
	
	int numLeftNodes = numNodes / 2;
	int numRightNodes = numNodes - numLeftNodes;

	cout << key << " : buildTree_parallel : Depth " << tree->depth << " Rank " << myRank << ", Left nodes = " << numLeftNodes << ", Right nodes = " << numRightNodes << endl;

	// Get global mins and maxs
	double globalMinX = 0;
	double globalMaxX = 0;
	double globalMinY = 0;
	double globalMaxY = 0;
	double globalMinZ = 0;
	double globalMaxZ = 0;

	tree->x1 = globalMinX;
	tree->x2 = globalMaxX;
	tree->y1 = globalMinY;
	tree->y2 = globalMaxY;
	tree->z1 = globalMinZ;
	tree->z2 = globalMaxZ;

	tree->c[_INDEX_] = _Undefined_;
	tree->c[_X_] = (globalMinX + globalMaxX) / 2.0;
	tree->c[_Y_] = (globalMinY + globalMaxY) / 2.0;
	tree->c[_Z_] = (globalMinZ + globalMaxZ) / 2.0;

	tree->radius = sqrt(pow(tree->c[_X_] - globalMinX, 2.0) +
		pow(tree->c[_Y_] - globalMinY, 2.0) +
		pow(tree->c[_Z_] - globalMinZ, 2.0));

	int sortDim = getSortDim( data, rows, cols, tree, myRank, numNodes, comm );
	
	int color = 0;

	if (myRank < numLeftNodes) {
		cout << key+1 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " is going left" << endl;
		tree->l = new Tree;
		tree->l->name = tree->name + "l";
		tree->r = nullptr;
		tree->rightComm = MPI_COMM_SELF;
		color = mpi_Color_Left;
		MPI_Comm tempComm;
		MPI_Comm_split(tree->thisComm, color, myRank, &tempComm);
		tree->leftComm = tempComm;
		
		int newRank = _Undefined_;
		MPI_Comm_rank(tempComm, &newRank);
		
		cout << key+2 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " has a new communicator and is now rank " << newRank 
			<< " called " << tree->l->name << endl;

		tree->l->p = tree;
		tree->l->depth = tree->depth+1;
		tree->l->parentComm = tree->thisComm;
		tree->l->thisComm = tempComm;
		tree->l->l = nullptr;
		tree->l->r = nullptr;
		tree->l->leftComm = MPI_COMM_SELF;
		tree->l->rightComm = MPI_COMM_SELF;

		cout << key+4 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " is calling buildTree" << endl;
		buildTree(data, rows, cols, tree->l, tree->leftComm, newRank, numLeftNodes, tree->l->name);
		cout << key+5 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " has returned from buildTree" << endl;
	}
	else 
	{
		cout << key+1 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " is going right" << endl;
		tree->r = new Tree;
		tree->r->name = tree->name + "r";
		tree->l = nullptr;
		tree->leftComm = MPI_COMM_SELF;

		color = mpi_Color_Right;
		MPI_Comm tempComm;
		
		cout << key+2 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " is splitting right" << endl;			

		MPI_Comm_split(tree->thisComm, color, myRank, &tempComm);

		cout << key+3 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " has split!" << endl;			

		tree->rightComm = tempComm;

		int newRank = _Undefined_;
		MPI_Comm_rank(tempComm, &newRank);
		
		cout << key+4 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " has a new communicator and is now rank " << newRank 
			<< " called " << tree->r->name << endl;

		tree->r->p = tree;
		tree->r->depth = tree->depth+1;
		tree->r->parentComm = tree->thisComm;
		tree->r->thisComm = tempComm;
		tree->r->l = nullptr;
		tree->r->r = nullptr;
		tree->r->leftComm = MPI_COMM_SELF;
		tree->r->rightComm = MPI_COMM_SELF;

		cout << key+5 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " is calling buildTree" << endl;
		buildTree(data, rows, cols, tree->r, tree->rightComm, newRank, numRightNodes, tree->r->name);
		cout << key+6 << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << myRank << " has returned from buildTree" << endl;
	}

	// cout << "buildTree_parallel : Rank " << myRank 
	// 	<< ", Depth " << tree->depth
	// 	<< ", SortDim " << sortDim 
	// 	<< ", Joining COMM " << color
	// 	<< endl;	
}




