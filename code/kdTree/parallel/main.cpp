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
	
	// number of worker nodes
	int numWorkers = numNodes - 1;
	// total number of files to read
	int maxFilesToProc = 501;
	// number of lines PER FILE
	int maxRows = 1000;
	//number of lines TOTAL
	unsigned int numLines = maxRows*maxFilesToProc;
	// average lines per worker node
	int avgPtsPerWorker = numLines / numWorkers;


	// set cout to print doubles' full length
	std::cout.precision(17);
	
	std::cout << "Rank " << myRank
		<< " running on " << processorName 
		<< " with " << numNodes << " total processes" 
		<< std::endl;

	auto timeBeginFilenameDistribute = std::chrono::system_clock::now();
	chrono::duration<double> timeElapsedSeconds = timeBeginFilenameDistribute - timeStart;
	cout << "TIMING : Rank " << std::fixed << std::setprecision(0) << myRank << " took "
		<< std::setprecision(2) << timeElapsedSeconds.count() << " seconds "
		<< " to initialize MPI" << endl;

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
	if (myRank == 0) {
		distributeFiles(FilenameArray, numNodes-1);
	} 
	else {
		// Receive file list
		FilenameArray = receiveFiles(myRank);
	}

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


	MPI_Finalize();

	return _OKAY_;
}
