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

	int key = 50000 + (tree->depth) * 100;

//	cout << tree->depth << endl;

	if( q > 1 ) {
/*
		ofstream f;
		auto newName = name + "-" + to_string(myRank) + ".csv";
		f.open(newName, ios::out);

		auto tempMin = min(data[0], *rows, cols, _X_);
		auto tempMax = max(data[0], *rows, cols, _X_);
		f << tempMin << ", " << tempMax << endl;

		tempMin = min(data[0], *rows, cols, _Y_);
		tempMax = max(data[0], *rows, cols, _Y_);
		f << tempMin << ", " << tempMax << endl;

		tempMin = min(data[0], *rows, cols, _Z_);
		tempMax = max(data[0], *rows, cols, _Z_);
		f << tempMin << ", " << tempMax << endl;

		f.close();
*/

	//	cout << key << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank
	//		<< " parallel named " << tree->name  << " q = " << q << " called by " << tree->name
	//		<< endl;
		float *array = data[0];
		buildTree_parallel( &array, rows, cols, tree, comm, currentRank, q );
		*data = array;

/*
		ofstream f;
		auto newName = name + "-" + to_string(myRank) + ".csv";
		f.open(newName, ios::out);

		auto tempMin = min(data[0], *rows, cols, _X_);
		auto tempMax = max(data[0], *rows, cols, _X_);
		f << tempMin << ", " << tempMax << endl;

		tempMin = min(data[0], *rows, cols, _Y_);
		tempMax = max(data[0], *rows, cols, _Y_);
		f << tempMin << ", " << tempMax << endl;

		tempMin = min(data[0], *rows, cols, _Z_);
		tempMax = max(data[0], *rows, cols, _Z_);
		f << tempMin << ", " << tempMax << endl;

		f.close();
*/

	//	cout << key << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank 
	//		<< " parallel named " << tree->name  << " q = " << q << " called by " << tree->name
	//		<< endl;
	} 
	else 
	{
/*
		ofstream f;
		auto newName = name + "-" + to_string(myRank) + ".csv";
		f.open(newName, ios::out);

		auto tempMin = min(data[0], *rows, cols, _X_);
		auto tempMax = max(data[0], *rows, cols, _X_);
		f << tempMin << ", " << tempMax << endl;

		tempMin = min(data[0], *rows, cols, _Y_);
		tempMax = max(data[0], *rows, cols, _Y_);
		f << tempMin << ", " << tempMax << endl;

		tempMin = min(data[0], *rows, cols, _Z_);
		tempMax = max(data[0], *rows, cols, _Z_);
		f << tempMin << ", " << tempMax << endl;

		f.close();
*/
		tree->name += "*";

	//	cout << key << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank
	//		<< " serial named " << tree->name  << " q = " << q << " called by " << tree->name
	//		<< endl;
		
	//	cout << rootRank << " before serial" << endl;
		buildTree_serial( *data, rows, cols, tree);
	//	cout << rootRank << " after serial" << endl;
	}

}
