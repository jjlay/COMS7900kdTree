//
// Parallel Sort
//

//
// Standard includes
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono> 

#include <unistd.h>
#include <time.h>
//
// Parallel includes
//

#include "mpi.h"


//
// Local includes
//

#include "definitions.h"

// parallelSort
#include "initializeMPI.h"
#include "listFiles.h"
#include "distributeFiles.h"
#include "receiveFiles.h"
#include "importFiles.h"
#include "getLinearBins.h"
#include "adaptBins.h"
#include "testUniformity.h"
#include "binData.h"
#include "binData2.h"
#include "receiveMinMax.h"
#include "transmitMinMax.h"
#include "transmitBinEdges.h"
#include "receiveBinCounts.h"
#include "transmitUniformity.h"
#include "receiveBinIndices.h"
#include "exportResults.h"
#include "min.h"
#include "max.h"
#include "swapArrayParts.h"
#include "cleanUp.h"
#include "parallelSort.h"

// buildTree
#include "tree.h"
#include "buildTree.h"



using namespace std;


//
// Function: main
//

int main(int argc, char *argv[])
{
	////////////////
	// MPI setup  //
	////////////////

	string processorName = "";
	int myRank = 0, numNodes = 0;
	
	initializeMPI(&processorName, &myRank, &numNodes, argc, argv);
	
	// total number of files to read
	const int maxFilesToProc = 3;

	// number of lines PER FILE
	const int maxRows = 10;
	
	int sortInd = 1; // x = 1

	//////////////////
	// Data Import  //
	//////////////////

	// location of the data files
	std::string homeDir = getenv("HOME");
	std::string path = homeDir + "/localstorage/public/coms7900-data/";

	std::vector<std::string> FilenameArray;

	// Retrieve the list of files to process
	if (myRank == 0)
		FilenameArray = listFiles(path, maxFilesToProc);

	// Distribute files to workers
	if (myRank == 0)
		distributeFiles( FilenameArray, numNodes );
	
	// Receive file list
	FilenameArray = receiveFiles(myRank);

	if (FilenameArray.size() == 0) {
		// OMG! Nothing to do!
		MPI_Finalize();
		cout << "Failed!" << endl;
		return _FAIL_;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	
	int rows = 0, cols = _ROW_WIDTH_;

	// Read data files in
	unsigned long int arrayLimit = (FilenameArray.size() * maxRows * cols + 8);
	double *array = new double[arrayLimit];

	importFiles(FilenameArray, myRank, array, &rows, &cols, maxRows, arrayLimit);

	MPI_Request tempRequest;
	MPI_Isend(&rows, 1, MPI_INT, Rank0, mpi_Tag_RowCount, MPI_COMM_WORLD, 
		&tempRequest);

	MPI_Barrier(MPI_COMM_WORLD);
	
	////////////////////////
	// Check min and max  //
	////////////////////////

	// Debug
	double minX = 9999, maxX = -9999, minY = 9999, maxY = -9999, minZ = 9999, maxZ = -9999;
	unsigned long int arrayIndex = 0;

	for (auto i = 0; i < rows; i++) {
		if (array[arrayIndex + _X_] < minX)
			minX = array[arrayIndex + _X_];

		if (array[arrayIndex + _X_] > maxX)
			maxX = array[arrayIndex + _X_];

		if (array[arrayIndex + _Y_] < minY)
			minY = array[arrayIndex + _Y_];

		if (array[arrayIndex + _Y_] > maxY)
			maxY = array[arrayIndex + _Y_];

		if (array[arrayIndex + _Z_] < minZ)
			minZ = array[arrayIndex + _Z_];

		if (array[arrayIndex + _Z_] > maxZ)
			maxZ = array[arrayIndex + _Z_];

		arrayIndex += 4;
	}

	cout << "main : Rank " << myRank << ", rows = " << rows << ", minX = " << minX << ", maxX = " << maxX
		<< ", minY = " << minY << ", maxY = " << maxY 
		<< ", minZ = " << minZ << ", maxZ = " << maxZ << endl;

	///////////////
	// buildTree //
	///////////////
	
	// initialize tree
	auto tree = new struct Tree;
	tree->p = nullptr;
	tree->depth = 0;
	tree->n     = maxRows*maxFilesToProc;
	
	buildTree( array, rows, cols, tree, MPI_COMM_WORLD, myRank, numNodes );
	
	/*
	cout << "root " << tree->i << endl;
	cout << tree->x1 << " " << tree->x2 << endl;
	cout << tree->y1 << " " << tree->y2 << endl;
	cout << tree->z1 << " " << tree->z2 << endl;
	
	cout << "left" << endl;
	cout << tree->l->x1 << " " << tree->l->x2 << endl;
	cout << tree->l->y1 << " " << tree->l->y2 << endl;
	cout << tree->l->z1 << " " << tree->l->z2 << endl;

	cout << "right" << endl;
	cout << tree->r->x1 << " " << tree->r->x2 << endl;
	cout << tree->r->y1 << " " << tree->r->y2 << endl;
	cout << tree->r->z1 << " " << tree->r->z2 << endl;
	*/
	
	cout << "Rank " << myRank << " finished  buildTree" << endl;

  MPI_Barrier(MPI_COMM_WORLD);
	
	////////////////
	// searchTree //
	////////////////
	
	// output
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	delete array;
	
	MPI_Finalize();

	return _OKAY_;
}


