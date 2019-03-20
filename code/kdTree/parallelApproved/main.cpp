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
#include "sortArray.h"
#include "exportResults.h"
#include "min.h"
#include "max.h"
#include "LL_sort.h"
#include "swapArrayParts.h"
#include "cleanUp.h"
#include "testSort.h"
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
	int maxFilesToProc = 30;
	// number of lines PER FILE
	int maxRows = 1000;
	
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
	
	int rows = 0, cols = 0;

        // Read data files in
        double *array = new double[FilenameArray.size() * maxRows * _ROW_WIDTH_]; //JJL
        importFiles(FilenameArray, myRank, array, &rows, &cols, maxRows);

        MPI_Request tempRequest;
        MPI_Isend(&rows, 1, MPI_INT, Rank0, mpi_Tag_RowCount, MPI_COMM_WORLD, &tempRequest);

	MPI_Barrier(MPI_COMM_WORLD);
	
	///////////////
	// buildTree //
	///////////////
	
	// initialize tree
	auto tree = new struct Tree;
	tree->p = nullptr;
	tree->depth = 0;
	
	buildTree( array, rows, cols, tree, MPI_COMM_WORLD );
	
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	////////////////
	// searchTree //
	////////////////
	
	// output
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	delete array;
	
	MPI_Finalize();

//	return _OKAY_;
	return 0;
}


