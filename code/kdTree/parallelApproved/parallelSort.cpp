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
#include "math.h"
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
#include "adaptBins_new.h"
#include "adaptBins_old.h"
#include "testUniformity.h"
#include "binData.h"
#include "receiveMinMax.h"
#include "transmitMinMax.h"
#include "transmitBinEdges.h"
#include "receiveBinCounts.h"
#include "transmitUniformity.h"
#include "receiveBinIndices.h"
#include "exportResults.h"
#include "min.h"
#include "max.h"
#include "sortData.h"
#include "swapArrayParts.h"
#include "cleanUp.h"


using namespace std;


//
// Function: main
//

void parallelSort( int myRank, int numNodes, double *tmpArray[], int *rowsPTR, int *colsPTR, int sortInd, MPI_Comm comm )
{
	int rows = *rowsPTR;
	int cols = *colsPTR;
	double *array = tmpArray[0];
	double myMin = 0.0;
	double myMax = 0.0;
	//number of lines TOTAL
	unsigned int numLines;
	
	// Use qsort
	sortData(array, cols, rows, sortInd);
		
	if( myRank == 0 ) {
	        auto allRows = new int[numNodes];
	        allRows[0] = *rowsPTR;
	        numLines = *rowsPTR;
	
	        MPI_Status tempStatus;
	
	        for (auto r = 1; r < numNodes; r++) {
	                MPI_Recv(&allRows[r], 1, MPI_INT, r, 1111,
	                        comm, &tempStatus);
	                numLines += allRows[r];
	        }
	} else {
		MPI_Send(rowsPTR, 1, MPI_INT, 0, 1111, comm );
	}

	// average lines per worker node
	int avgPtsPerWorker = numLines / numNodes;
	
	MPI_Barrier(comm);

	auto allMins = new double[numNodes];
	auto allMaxs = new double[numNodes];
	double minGlobal, maxGlobal;
	
	// Send minimums and maximums
	myMin = min(array, rows, cols, sortInd );
	myMax = max(array, rows, cols, sortInd );
	transmitMinMax( myMin, myMax, comm );
	
	if (myRank == 0) {
		for (auto r = 0; r < numNodes; r++) {
			receiveMinMax( r, &allMins[r], &allMaxs[r], comm );
		}
		
		minGlobal = allMins[0];
		maxGlobal = allMaxs[0];

		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal > allMins[r] )
				minGlobal = allMins[r];
			if( maxGlobal < allMaxs[r] )
				maxGlobal = allMaxs[r];
		}
	} 


	MPI_Barrier(comm);

	//////////////////////
	//                  //
	// Adapt Bin Sizes  //
	//                  //
	//////////////////////
	
	int worldRank = -1;
	MPI_Comm_rank( MPI_COMM_WORLD, &worldRank );
	
	int a = worldRank;
	
	// same across all nodes
	double *binE = new double[numNodes+1];
	// different across all nodes, master is sum of others
	int *binC  = new int[numNodes];
	int *binCt = new int[numNodes];
	
	// 2D binI for master node
	int **binI_2D = new int*[numNodes]; // [worker][bin]
	for( int i = 0; i < numNodes; i++ ) {
		binI_2D[i] = new int[numNodes+1];
	}
	
	// 1D binI for workers
	int *binI_1D = new int[numNodes+1];
	
	int result;
	MPI_Status status;
	MPI_Request request;

	// uniformity threshold
	double thresh = 0.101;
	double uniformity;
	// Change to 0 when the functions are written
	int isUniform[1];
	isUniform[0] = -1;
	
	if (myRank == 0) {
		// Calculate initial bin edges
		getLinearBins( binE, numNodes, myRank, minGlobal, maxGlobal );  // for real
		// Transmit initial bin edges
		transmitBinEdges( binE, numNodes, comm );
	} else {
		// Receive initial bin edges
		result = MPI_Recv( binE, numNodes+1, MPI_DOUBLE, 0,
			mpi_Tag_BinEdges, comm, &status );
	}
	
	binI_1D[0] = 0;
	binI_1D[numNodes] = rows;
	for( int i = 1; i < numNodes; i++ ) {
		binI_1D[i] = i*avgPtsPerWorker;
	}
	
	// get intitial bin counts, indices
	binData( array, binE, myRank, sortInd,
		numNodes, rows, binI_1D, binC); // for real
	
	if( myRank == 0 ){
		// Receive initial bin counts
		receiveBinCounts( binCt, numNodes, comm );
		for( int j = 0; j < numNodes; j++ ) {
			binCt[j] = binCt[j] + binC[j];
		}

	} else {
		// Transmit initial bin counts
		result = MPI_Send( binC, numNodes, MPI_INT, 0,
			mpi_Tag_BinCounts, comm );
	
		// Transmit initial bin indices
		result = MPI_Send( binI_1D, numNodes+1, MPI_INT, 0,
			mpi_Tag_BinIndices, comm );
	}
	
	if( myRank == 0 ) {
		// Receive initial bin indices
		receiveBinIndices( binI_2D, numNodes, comm );
		for( int j = 0; j < numNodes+1; j++ ) {
			binI_2D[0][j] = binI_1D[j];
		}
		
		// Determine if uniform
		*isUniform = testUniformity( binCt, numNodes, thresh, &uniformity );
		
		// Transmit isUniform update
		transmitUniformity( isUniform, numNodes, comm );
	} else { 
		// Receive isUniform update
		result = MPI_Recv( isUniform, 1, MPI_INT, 0,
			mpi_Tag_isUnif, comm, &status );
	}
	// end first iteration
	
	int iterations = 1;
	
	while( ( *isUniform == 0 ) && (iterations < abortCount) ) {
		if (myRank == 0) {
			if( iterations % 2 == 1) {
				adaptBins_new( binE, binCt, numNodes, numLines, avgPtsPerWorker );
			} else {
				adaptBins_old( binE, binCt, numNodes, iterations );
			}
			
			// Transmit initial bin edges
			transmitBinEdges( binE, numNodes, comm );
		} else {
			// Receive initial bin edges
			result = MPI_Recv( binE, numNodes+1, MPI_DOUBLE, 0,
				mpi_Tag_BinEdges, comm, &status );
		}
		
		binI_1D[0] = 0;
		binI_1D[numNodes] = rows;
		for( int i = 1; i < numNodes; i++ ) {
			binI_1D[i] = i*avgPtsPerWorker;
		}
		
		// get intitial bin counts, indices
		binData( array, binE, myRank, sortInd,
			numNodes, rows, binI_1D, binC); // for real
		
		if( myRank == 0 ){
			// Receive initial bin counts
			receiveBinCounts( binCt, numNodes, comm );
			for( int j = 0; j < numNodes; j++ ) {
				binCt[j] = binCt[j] + binC[j];
			}
	
		} else {
			// Transmit initial bin counts
			result = MPI_Send( binC, numNodes, MPI_INT, 0,
				mpi_Tag_BinCounts, comm );
		
			// Transmit initial bin indices
			result = MPI_Send( binI_1D, numNodes+1, MPI_INT, 0,
				mpi_Tag_BinIndices, comm );
		}
		
		if( myRank == 0 ) {
			// Receive initial bin indices
			receiveBinIndices( binI_2D, numNodes, comm );
			for( int j = 0; j < numNodes+1; j++ ) {
				binI_2D[0][j] = binI_1D[j];
			}
			
			// Determine if uniform
			*isUniform = testUniformity( binCt, numNodes, thresh, &uniformity );
		
			// Transmit isUniform update
			transmitUniformity( isUniform, numNodes, comm);
		} else { 
			// Receive isUniform update
			result = MPI_Recv( isUniform, 1, MPI_INT, 0,
				mpi_Tag_isUnif, comm, &status );
		}
		
		iterations++;
	}
	
	if ((iterations >= abortCount) && (myRank == Rank0)) {
		cerr << "===========================================" << endl;
		cerr << "Aborted adaptBins at iteration " << iterations << endl;

		cerr << "Rank " << myRank << " Bin counts are:" << endl;
		cerr << "Number of nodes " << numNodes << endl;

		for (auto i = 0; i < numNodes; i++) {
			cerr << "binCt[" << i << "] = " << binCt[i] << ", "
				<< "binE[" << i << "] = " << binE[i] << ", ";
			cerr << endl;
		}

		cout << "===========================================" << endl << endl;
	}		

	MPI_Barrier(comm);

	// Broadcast binI_2D to workers
	for( int i = 0; i < numNodes; i++ ) {
		result = MPI_Bcast( binI_2D[i], numNodes+1, MPI_INT, 0, comm );
	}

	MPI_Barrier( comm );
	int c = worldRank;


	//////////////////////////////
	//                          //
	// Swap Data Between Nodes  //
	//                          //
	//////////////////////////////
	
	int **start = new int*[numNodes]; // [worker][bin]
	for( int i = 0; i < numNodes; i++ ) {
		start[i] = new int[numNodes];
	}
	
	int newRows = 0;
	for( int i = 0; i < numNodes; i++ )
	{
		newRows += binI_2D[i][myRank+1] - binI_2D[i][myRank];
		start[i][0] = 0;
		
		for( int j = 0; j < numNodes; j++ )
		{
			start[i][j+1] = binI_2D[j][i+1] - binI_2D[j][i] + start[i][j];
		}
	}
	
	if( myRank == 0 ) {
		for( int i = 0; i < numNodes; i++ )
		{
			for( int j = 0; j < numNodes+1; j++ )
			{
				cout << binI_2D[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		for( int i = 0; i < numNodes; i++ )
		{
			for( int j = 0; j < numNodes; j++ )
			{
				cout << start[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
//	cout << newRows << endl;
	
	
	double *newArray = (double*) malloc( newRows*4*sizeof(double) );
	
	/*
        int F_rows = int(numLines);
        int F_cols = 4;
        int toWho;
        int fromWho;
        for( fromWho = 0; fromWho < numNodes; fromWho++ ){
                for( toWho = 0; toWho< numNodes; toWho++){
                        if(toWho!=fromWho){
                                if(myRank ==toWho || myRank ==fromWho){
                                        newSwap( &array, &newArray, &rows, &newRows, &F_cols, myRank, numNodes, binI_2D[fromWho], fromWho, toWho, comm );
                                }
                        }
                }
        //	MPI_Barrier(comm);
        }
	
	MPI_Barrier(comm);
	
//	cout << worldRank << " finished cleanup" << endl;
	
	for( int clean = 0; clean< numNodes; clean++){
		if(myRank == clean){
			cleanUp(&array, &rows, &F_cols, clean, numNodes, binI_2D[myRank]);
		}
	}
	*/
	
	MPI_Barrier(comm);
//	sortData(array, cols, rows, sortInd);
	
        // Export results
	
	*rowsPTR  = rows;
	*colsPTR  = cols;
	*tmpArray = array;
	int f = worldRank;
}


