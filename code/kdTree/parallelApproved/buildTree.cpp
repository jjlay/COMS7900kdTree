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

void buildTree(double *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes, string name ) {

	int q = 0, currentRank = 0;
	MPI_Comm_size( comm, &q );
	MPI_Comm_rank( comm, &currentRank );

	int key = 50000 + (tree->depth) * 100;


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
		double *array = data[0];
		tree->source = _Source_buildTree_parallel;
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

		tree->name += "*";
		tree->source = _Source_buildTree_serial;

	//	cout << key << " : " << __FUNCTION__ << " : Depth " << tree->depth << " Rank " << currentRank
	//		<< " serial named " << tree->name  << " q = " << q << " called by " << tree->name
	//		<< endl;
		buildTree_serial( *data, rows, cols, tree);
	}

}

