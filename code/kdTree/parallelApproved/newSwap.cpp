//
// swapArrayParts
//

//#undef _DEBUG_


//
//STL includes
//

#include <vector>

//
//Standard Includes
//

#include <sys/time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h> 
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include "mpi.h"

//
//Local includes
//

#include "swapArrayParts.h"
#include "definitions.h"


//
//Function: swapArrayParts
//
using namespace std;

void newSwap(double *pmyArray[], double *newArray, int *rowPTR , int *colPTR, int myrank, int numranks, int *binIPTR, int fromWho, int toWho, MPI_Comm comm){
	
	MPI_Request request;
        MPI_Status status;
	
	if( myRank == fromWho )
	{
		MPI_Isend( &pmyArray[4*binIPTR[toWho]], 4*(binIPTR[toWho+1]-binIPTR[toWho]), MPI_DOUBLE, toWho, 888, comm, &request );
		
	}
	
	
	if( myRank == toWho )
	{
		MPI_Recv( &newArray[4*binIPTR[fromWho]], 4*(binIPTR[toWho+1]-binIPTR[toWho]), MPI_DOUBLE, fromWho, 888, comm, &status );
		
	}
	
	
	return;
}













