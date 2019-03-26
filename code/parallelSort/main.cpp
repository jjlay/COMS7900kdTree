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
// #include "LL_sort.h"
#include "swapArrayParts.h"
#include "cleanUp.h"
#include "testSort.h"

#include "parallelSort.h"

using namespace std;


//
// Function: main
//

int main(int argc, char *argv[])
{
	////////////////
	//            //
	// MPI setup  //
	//            //
	////////////////

	string processorName = "";
	int myRank = 0, numNodes = 0;

	initializeMPI(&processorName, &myRank, &numNodes, argc, argv);

	// total number of files to read
	const int maxFilesToProc = 100;
	// number of lines PER FILE
	const int maxRows = 10000;

	int sortInd = 1; // x = 1
	

	//////////////////
	//              //
	// Data Import  //
	//              //
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

	//
	// Check to make sure there is actual work
	//
	
	if (FilenameArray.size() == 0) {
		// OMG! Nothing to do!
		MPI_Finalize();
		cout << "Failed!" << endl;
		return _FAIL_;
	}

	
	MPI_Barrier(MPI_COMM_WORLD);
	
	int rows = 0, cols = _ROW_WIDTH_;

        // Read data files in
        int maxArraySize = FilenameArray.size() * maxRows * cols;
        double *array = new double[maxArraySize];

        importFiles(FilenameArray, myRank, array, &rows, &cols, maxRows, maxArraySize);

        MPI_Request tempRequest;
        MPI_Isend(&rows, 1, MPI_INT, Rank0, mpi_Tag_RowCount, 
		MPI_COMM_WORLD, &tempRequest);

	MPI_Barrier(MPI_COMM_WORLD);

	
	//////////////////
	//              //
	// parallelSort //
	//              //
	//////////////////

	parallelSort( myRank, numNodes, &array, &rows, &cols, sortInd );
	
	// DONE
	
	delete array;

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();

	return _OKAY_;
}


