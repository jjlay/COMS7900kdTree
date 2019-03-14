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


using namespace std;


//
// Function: main
//


int main(int argc, char *argv[]) {

	////////////////
	//            //
	// MPI setup  //
	//            //
	////////////////

	std::string processorName;
	int myRank, numNodes;

	initializeMPI(&processorName, &myRank, &numNodes, argc, argv);

	auto timeStart = std::chrono::system_clock::now();
		
	std::cout << "Rank " << myRank
		<< " running on " << processorName 
		<< " with " << numNodes << " total processes" 
		<< std::endl;

	auto timeBeginFilenameDistribute = std::chrono::system_clock::now();


	//////////////////
	//              //
	// Data Import  //
	//              //
	//////////////////

	// location of the data files
	std::string homeDir = getenv("HOME");
	std::string path = homeDir + "/localstorage/public/coms7900-data/";

	std::vector<std::string> allFilesArray;

	// Retrieve the list of files to process
	if (myRank == 0)
		allFilesArray = listFiles(path);

	// Distribute files to workers
	if (myRank == 0) 
		distributeFiles(allFilesArray, numNodes);

	// Receive file list
	auto filenameArray = receiveFiles(myRank);

	//
	// Check to make sure there is actual work
	//
	
	if (filenameArray.size() == 0) {
		// OMG! Nothing to do!
		MPI_Finalize();
		cout << "Failed!" << endl;
		return _FAIL_;
	}

	
	MPI_Barrier(MPI_COMM_WORLD);

	double *array;
	int rows = 0, cols = 0, maxRows = _MAX_ROWS_;

	auto timeBeginImport = std::chrono::system_clock::now();

    // Read data files in
    array = new double[filenameArray.size() * maxRows * _ROW_WIDTH_]; 
    importFiles(path, filenameArray, myRank, array, &rows, &cols, maxRows);

    MPI_Request tempRequest;
    MPI_Isend(&rows, 1, MPI_INT, Rank0, mpi_Tag_RowCount, MPI_COMM_WORLD, &tempRequest);

	auto timeEndImport = std::chrono::system_clock::now();
	chrono::duration<double> timeElapsedSeconds = timeEndImport - timeBeginImport;
	cout << "TIMING : Rank " << std::fixed << std::setprecision(0) << myRank << " took "
		<< std::setprecision(2) << timeElapsedSeconds.count() << " seconds "
		<< " to import data" << endl;



	///////////////////////////////////////
	//
	// Wrap up
	//
	///////////////////////////////////////

	MPI_Barrier(MPI_COMM_WORLD);

	auto timeEnd = std::chrono::system_clock::now();
	timeElapsedSeconds = timeEnd - timeStart;
	std::cout << "TIMING : Rank " << std::fixed << std::setprecision(0) << myRank << " took "
		<< std::setprecision(2) << timeElapsedSeconds.count() << " seconds "
		<< "to run" << std::endl;

	MPI_Finalize();

	return _OKAY_;
}


