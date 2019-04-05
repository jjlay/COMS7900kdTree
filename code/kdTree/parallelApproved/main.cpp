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
#include <chrono>


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
#include "search501.h"
#include "searchWorker.h"

// buildTree
#include "tree.h"
#include "buildTree.h"
#include "searchTree.h"
#include "searchTree_serial.h"
#include "searchTree_parallel.h"



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

	// Begin the timing
	auto chronoStart = chrono::system_clock::now();


	// total number of files to read
	const int maxFilesToProc = 50;

	// number of lines PER FILE
	const int maxRows = 100000;

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

	auto chronoEndOfListFiles = chrono::system_clock::now();


	// Distribute files to workers
	if (myRank == 0)
		distributeFiles( FilenameArray, numNodes );

	auto chronoEndOfDistributeFiles = chrono::system_clock::now();

	MPI_Barrier(MPI_COMM_WORLD);


	// Receive file list
	FilenameArray = receiveFiles(myRank);

	auto chronoEndOfReceiveFiles = chrono::system_clock::now();

	if (FilenameArray.size() == 0) {
		// OMG! Nothing to do!
		MPI_Finalize();
		cerr << "Failed!" << endl;
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

	auto chronoEndOfImportFiles = chrono::system_clock::now();

	MPI_Request tempRequest;
	MPI_Isend(&rows, 1, MPI_INT, Rank0, mpi_Tag_RowCount, MPI_COMM_WORLD,
		&tempRequest);

	MPI_Barrier(MPI_COMM_WORLD);


	///////////////
	// buildTree //
	///////////////

	// initialize tree
	Tree *tree = new struct Tree;
	tree->p = nullptr;
	tree->depth = 0;
	tree->n     = rows;
	tree->parentComm = MPI_COMM_SELF;
	tree->leftComm = MPI_COMM_SELF;
	tree->rightComm = MPI_COMM_SELF;
	tree->thisComm = MPI_COMM_WORLD;
	tree->name = "t";

	cerr << "70000 : Rank " << myRank << " is calling buildTree" << endl;
	buildTree( &array, &rows, cols, tree, tree->thisComm, myRank, 
		numNodes, tree->name );


	auto chronoEndOfBuildTree = chrono::system_clock::now();

	MPI_Barrier(MPI_COMM_WORLD);


	////////////////
	// searchTree //
	////////////////

	cerr << "80000 : Rank " << myRank << " is calling search501" << endl;
	
	search501( myRank, path, tree);
	
	auto chronoEndOfSearch501 = chrono::system_clock::now();
	
	MPI_Barrier(MPI_COMM_WORLD);

	cerr << "98000 : Rank " << myRank << " has completed search501" << endl;


	chrono::duration<double> timeToListFiles = chronoEndOfListFiles - chronoStart;
	chrono::duration<double> timeToDistributeFiles = chronoEndOfDistributeFiles - chronoEndOfListFiles;
	chrono::duration<double> timeToReceiveFiles = chronoEndOfReceiveFiles - chronoEndOfDistributeFiles;
	chrono::duration<double> timeToImportFiles = chronoEndOfImportFiles - chronoEndOfReceiveFiles;
	chrono::duration<double> timeToRun = chronoEndOfSearch501 - chronoStart;

	cerr << "99000 : Rank " << myRank << " took " << timeToListFiles.count() << " seconds to list files" << endl;
	cerr << "99000 : Rank " << myRank << " took " << timeToDistributeFiles.count() << " seconds to distribute files" << endl;
	cerr << "99000 : Rank " << myRank << " took " << timeToReceiveFiles.count() << " seconds to receive files" << endl;
	cerr << "99000 : Rank " << myRank << " took " << timeToImportFiles.count() << " seconds to import files" << endl;
	cerr << "99000 : Rank " << myRank << " took " << timeToRun.count() << " seconds to run" << endl;

	MPI_Finalize();

	return _OKAY_;
}


