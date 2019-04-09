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
	cout << "00000 : main : Rank " << myRank << " on " << processorName << ", Total nodes " << numNodes << endl;
	
	// Begin the timing
	auto chronoStart = chrono::system_clock::now();


	// total number of files to read
	const int maxFilesToProc = 501;

	// number of lines PER FILE
	const int maxRows = 20000000;

	cout << "00000 : main : " << maxFilesToProc << " files with " << maxRows << " rows each" << endl;


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

	cerr << "00000 : main : Rank " << myRank << " : Allocating " << arrayLimit << " bytes or "
		<< arrayLimit / 1024 /1024 /1024 << " GB" << endl;

	double *array = new double[arrayLimit];

	cerr << "00000 : main : Rank " << myRank << " : Finished allocation" << endl;


	// void importFiles(vector<string> files, int myRank,
	// 	double *myData, int *rows, int *cols, int maxRows,
	// 	int maxRowsPerFile, unsigned long int arrayLimit)

	importFiles(FilenameArray, myRank, array, &rows, &cols, maxRows, arrayLimit);

	auto chronoEndOfImportFiles = chrono::system_clock::now();

	MPI_Request tempRequest;
	MPI_Isend(&rows, 1, MPI_INT, Rank0, mpi_Tag_RowCount, MPI_COMM_WORLD,
		&tempRequest);

	MPI_Barrier(MPI_COMM_WORLD);

	chrono::duration<double> runtime = chronoEndOfImportFiles - chronoStart;

	cerr << "999999 : main : Rank " << myRank << " runtime " << runtime.count() << " seconds" << endl;

	MPI_Finalize();

	return _OKAY_;
}


