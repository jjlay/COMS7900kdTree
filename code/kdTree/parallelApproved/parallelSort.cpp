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
	// average lines per worker node
	int avgPtsPerWorker = numLines / numNodes;
	
        // Perform initial sort
        //sortArray(array, rows, cols, sortInd);
	//LL_sort(array, rows, cols, sortInd);
	
	// Use qsort
	sortData(array, cols, rows, sortInd);
		
	if( myRank == 0 ) {
	        // Rank 0 is going to receive the number of lines on each
	        // worker node
	
	        auto allRows = new int[numNodes];
	        allRows[0] = *rowsPTR;
	        numLines = *rowsPTR;
	
	        MPI_Status tempStatus;
	
	        for (auto r = 1; r < numNodes; r++) {
	                MPI_Recv(&allRows[r], 1, MPI_INT, r, 1111,
	                        comm, &tempStatus);
	                numLines += allRows[r];
	        }
	
	        for (auto r = 1; r < numNodes; r++)
	                cout << "Rank " << r << " sent " << allRows[r] << " rows" << endl;
	
	        cout << "There were a total of " << numLines << " rows across all workers" << endl;
	} else {
		MPI_Send(rowsPTR, 1, MPI_INT, 0, 1111, comm );
	}

	
	MPI_Barrier(comm);

	auto allMins = new double[numNodes];
	auto allMaxs = new double[numNodes];
	double minGlobal, maxGlobal;
	
	// Send minimums and maximums
	myMin = min(array, rows, cols, _X_);
	myMax = max(array, rows, cols, _X_);
	transmitMinMax( myMin, myMax, comm );
	
	if (myRank == 0) {
		// Receive minimums and maximums
	//	allMins[Rank0] = 0.0;
	//	allMaxs[Rank0] = 0.0;

		for (auto r = 0; r < numNodes; r++) {
			receiveMinMax( r, &allMins[r], &allMaxs[r], comm );
		//	cout << r << " " << allMins[r] << " " << allMaxs[r] << endl;
		}
		
		minGlobal = allMins[0];
		maxGlobal = allMaxs[0];

		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal > allMins[r] )
				minGlobal = allMins[r];
			if( maxGlobal < allMaxs[r] )
				maxGlobal = allMaxs[r];
		}
	//	std::cout << minGlobal << " " << maxGlobal << std::endl;
	} 


	MPI_Barrier(comm);

	//////////////////////
	//                  //
	// Adapt Bin Sizes  //
	//                  //
	//////////////////////

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
//		std::cout << "ITERATION: 0" << std::endl;
		
		// Calculate initial bin edges
		getLinearBins( binE, numNodes, myRank, minGlobal, maxGlobal );  // for real
//		std::cout << "binE: " << binE[0] << " " << binE[1] << " " << binE[2] << " " << binE[3] << std::endl;
		
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
//	cout << myRank << " binC: " << binC[0] << " " << binC[1] << " " << binC[2] << endl;
	
	if( myRank == 0 ){
		// Receive initial bin counts
		receiveBinCounts( binCt, numNodes, comm );
		for( int j = 0; j < numNodes; j++ ) {
			binCt[j] = binCt[j] + binC[j];
		}

//		cout << myRank << "first binCt: ";
//		for( int i = 0; i < numNodes; i++ ) {
//			cout << binCt[i] << " ";
//		}
//		cout << std::endl;
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
		
	/*
		for( int i = 0; i < numNodes; i++ ) {
			std::cout << i << " binI_2D: " << binI_2D[i][0] 
				<< " " << binI_2D[i][1] << " " 
				<< binI_2D[i][2] << " " << binI_2D[i][3] << std::endl;
		}
	*/
		
		// Determine if uniform
		*isUniform = testUniformity( binCt, numNodes, thresh, &uniformity );
		
	/*
		if( *isUniform == 1 ) {
			std::cout << "Threshold:  " << thresh << std::endl;
			std::cout << "Uniformity: " << uniformity << std::endl;
			std::cout << "DONE: the bins are uniform" << std::endl;
		} else {
			std::cout << "Threshold:  " << thresh << std::endl;
			std::cout << "Uniformity: " << uniformity << std::endl;
			std::cout << "CONTINUE: the bins aren't uniform" << std::endl;
		}
	*/	
		// Transmit isUniform update
		transmitUniformity( isUniform, numNodes, comm );
	} else { 
		// Receive isUniform update
		result = MPI_Recv( isUniform, 1, MPI_INT, 0,
			mpi_Tag_isUnif, comm, &status );
	}
	// end first iteration
	
	int iterations = 1;
//	int deathCount = 100;  // Number of iterations we will allow adaptBins to be stuck
	
	while( ( *isUniform == 0 ) && (iterations < abortCount) ) {
//	while( iterations < 2 ) {
		
		if (myRank == 0) {
//			cout << "ITERATION: " << iterations << endl;
			
			// Adapt bin edges
			// new
		//	adaptBins( binE, binCt, numNodes, numLines, avgPtsPerWorker );
			// old
			adaptBins( binE, binCt, numNodes, iterations );
			
	//		cout << "binE: " << binE[0] << " " << binE[1] << " " << binE[2] << " " << binE[3] << endl;
			
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
	//	cout << myRank << " binC: " << binC[0] << " " << binC[1] << " " << binC[2] << endl;
		
		if( myRank == 0 ){
			// Receive initial bin counts
			receiveBinCounts( binCt, numNodes, comm );
			for( int j = 0; j < numNodes; j++ ) {
				binCt[j] = binCt[j] + binC[j];
			}
	
//			cout << myRank << " binCt: ";
//			for( int i = 0; i < numNodes; i++ ) {
//				cout << binCt[i] << " ";
//			}
//			cout << std::endl;
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
			
		/*
			for( int i = 0; i < numNodes; i++ ) {
				std::cout << i+1 << " binI_2D: " << binI_2D[i][0] 
					<< " " << binI_2D[i][1] << " " 
					<< binI_2D[i][2] << " " << binI_2D[i][3] << std::endl;
			}
		*/
			
			// Determine if uniform
			*isUniform = testUniformity( binCt, numNodes, thresh, &uniformity );
			
		/*	
			if( *isUniform == 1 ) {
				std::cout << "Threshold:  " << thresh << std::endl;
				std::cout << "Uniformity: " << uniformity << std::endl;
				std::cout << "DONE: the bins are uniform" << std::endl;
			} else {
				std::cout << "Threshold:  " << thresh << std::endl;
				std::cout << "Uniformity: " << uniformity << std::endl;
				std::cout << "CONTINUE: the bins aren't uniform" << std::endl;
			}
		*/
			// Transmit isUniform update
			transmitUniformity( isUniform, numNodes, comm);
		} else { 
			// Receive isUniform update
			result = MPI_Recv( isUniform, 1, MPI_INT, 0,
				mpi_Tag_isUnif, comm, &status );
		}
		
		iterations++;
	}
	
	
	// print iterations required for uniformity
	if (myRank == 0)
		cout << "ITERATIONS: " << iterations << endl;
	
	
	if ((iterations >= abortCount) && (myRank == Rank0)) {
		cout << "===========================================" << endl;
		cout << "Aborted adaptBins at iteration " << iterations << endl;

		cout << "Rank " << myRank << " Bin counts are:" << endl;
		cout << "Number of nodes " << numNodes << endl;

		for (auto i = 0; i < numNodes; i++) {
			cout << "binCt[" << i << "] = " << binCt[i] << ", "
				<< "binE[" << i << "] = " << binE[i] << ", ";
			cout << endl;
		}

		cout << "===========================================" << endl << endl;
	}		

	MPI_Barrier(comm);

// multiline start	
	// Broadcast binI_2D to workers
	for( int i = 0; i < numNodes; i++ ) {
		result = MPI_Bcast( binI_2D[i], numNodes+1, MPI_INT, 0, comm );
	}
// multiline end

/* / multiline start
	if( myRank == 1 ) {
		for( int i = 0; i < numNodes; i++ ) {
			std::cout << i << " binI_2D: " << binI_2D[i][0] 
				<< " " << binI_2D[i][1] << " " 
				<< binI_2D[i][2] << " " 
				<< binI_2D[i][3] << std::endl;
		}
	}
*/ // multiline end


	//////////////////////////////
	//                          //
	// Verify the bin info is   //
	// valid                    //
	//                          //
	//////////////////////////////
/*	
	if (myRank == Rank0) {




	}
	else {
		for (auto i = 1; i < numNodes; i++) {
			if (binI_1D[i] < binI_1D[i-1]) {
				cout << "Rank " << myRank << " : binI[" << i << "] (" << binI_1D[i] << ") is less than "
					<< "binI[" << i-1 << "] (" << binI_1D[i-1] << ") ***" << endl;
			} 
			else {
				cout << "Rank " << myRank << " : binI[" << i << "] (" << binI_1D[i] << ") is greater than "
					<< "binI[" << i-1 << "] (" << binI_1D[i-1] << ")" << endl;
			}

			if (binE[i] < binE[i-1]) {
				cout << "Rank " << myRank << " : binE[" << i << "] (" << binE[i] << ") is less than "
					<< "binE[" << i-1 << "] (" << binE[i-1] << ") ***" << endl;
			}
			else {
				cout << "Rank " << myRank << " : binE[" << i << "] (" << binE[i] << ") is greater than "
					<< "binE[" << i-1 << "] (" << binE[i-1] << ")" << endl;
			}
		}
	}
*/
	
	MPI_Barrier( comm );


	//////////////////////////////
	//                          //
	// Swap Data Between Nodes  //
	//                          //
	//////////////////////////////

//	MPI_Barrier( comm );

//        cout << "\n **********At Swap Arrays ******* with rank : " << myRank  << endl;
        int F_rows = int(numLines);
        int F_cols = 4;
        int toWho;
        int fromWho;
        for( fromWho = 0; fromWho < numNodes; fromWho++ ){
               for( int toWho = 0; toWho< numNodes; toWho++){
                        if(toWho!=fromWho){
                                if(myRank ==toWho || myRank ==fromWho){
//                                        cout << "Rank " << myRank << " towho: " << toWho << " is entering swap parts with  " << fromWho << endl;
                                        swapArrayParts( &array, &rows, &F_cols, myRank, numNodes, binI_2D[fromWho], fromWho, toWho, comm );
//                                        cout << "^^^^^^^^^Rank " << myRank << " towho: " << toWho << " exited swap parts with  " << fromWho << endl;
                                }
                //      sleep(5);

                        }
                }
        	MPI_Barrier(comm);
        }

        MPI_Barrier( comm );

//	cout << "rank: " << myRank << " has made it to cleanup !!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
        // Cleanup elements from same node
        for(int clean = 0; clean< numNodes; clean++){
		if(myRank == clean){
             		cleanUp(&array, &rows, &F_cols, clean, numNodes, binI_2D[myRank]);   
		}
        }

	MPI_Barrier(comm);

	// Final sort
	//LL_sort(array, rows, cols, sortInd);
	sortData(array, cols, rows, sortInd);
	
//	cout << "Rank " << myRank << " array after clean up " << rows << endl;
	
/*
	for(int iii =0 ; iii< rows ; iii++){
		cout << "rank: " << myRank << " Row: " << iii << " : " ;
		for(int kkk =0; kkk < 4; kkk++){
			cout << array[4*iii+kkk] << " : " ;
		}
		cout << endl;
	}
*/


        // Export results

	*rowsPTR  = rows;
	*colsPTR  = cols;
	*tmpArray = array;
}


