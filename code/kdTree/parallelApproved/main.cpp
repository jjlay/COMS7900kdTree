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
#include "receiveMinMax.h"
#include "binData.h"
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
#include "dumpTree.h"
#include "search501.h"
#include "searchWorker.h"

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
	const int maxFilesToProc = 10;

	// number of lines PER FILE
	const int maxRows = 100;

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

	// void importFiles(vector<string> files, int myRank,
	// 	double *myData, int *rows, int *cols, int maxRows,
	// 	int maxRowsPerFile, unsigned long int arrayLimit)

	importFiles(FilenameArray, myRank, array, &rows, &cols, maxRows, arrayLimit);

	MPI_Request tempRequest;
	MPI_Isend(&rows, 1, MPI_INT, Rank0, mpi_Tag_RowCount, MPI_COMM_WORLD,
		&tempRequest);

	MPI_Barrier(MPI_COMM_WORLD);


	///////////////
	// buildTree //
	///////////////

	// initialize tree
	auto tree = new struct Tree;
	tree->p = nullptr;
	tree->depth = 0;
	tree->n     = rows;
	tree->parentComm = MPI_COMM_SELF;
	tree->leftComm = MPI_COMM_SELF;
	tree->rightComm = MPI_COMM_SELF;
	tree->thisComm = MPI_COMM_WORLD;
	tree->name = "t";

	buildTree( &array, &rows, cols, tree, tree->thisComm, myRank, numNodes, tree->name );

	sleep(myRank+1);

	for (auto i = 0; i < rows; i++ ) {
		cout << "11111 : Rank " << myRank << " Row " << i << " X " << array[(i*_ROW_WIDTH_) + _X_]
			<< " Y " << array[(i*_ROW_WIDTH_) + _Y_]
			<< " Z " << array[(i*_ROW_WIDTH_) + _Z_] << endl;
		if (i == 0)
			i = rows - 2;
	}

	MPI_Barrier(MPI_COMM_WORLD);

/*
	string dumpFile = "dump-" + to_string(myRank) + ".txt";
	ofstream d;

	d.open(dumpFile, ios::out);
	dumpTree(tree, 0, &d, myRank);
	d.close();
*/

	MPI_Barrier(MPI_COMM_WORLD);

	////////////////
	// searchTree //
	////////////////

	if (myRank == Rank0) {
		search501(myRank, path);
	}
	else {
		// Worker
		searchWorker(myRank);
	}

	// output

	MPI_Barrier(MPI_COMM_WORLD);

	// delete array;

	MPI_Finalize();

	return _OKAY_;
}
