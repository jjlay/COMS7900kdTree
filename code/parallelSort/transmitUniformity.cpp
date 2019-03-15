

//
// Parallel includes
//

#include "mpi.h"


//
// Standard includes
//

#include <iostream>
#include <iomanip>


//
// Local includes
//

#include "definitions.h"


//
// Function: transmitUniformity
//
// Parameters:
//    bins - pointer to the array of bin edges
//
//    numWorkers - number of workers

void transmitUniformity( int *isUniform, int numWorkers) {

	int result;
	MPI_Request request;
	
//	std::cout << "Transmitting uniformity" << std::endl;
	
	for( int i = 1; i < numWorkers; i++ ) {
		
		result = MPI_Isend( isUniform, 1, MPI_INT, i,
			mpi_Tag_isUnif, MPI_COMM_WORLD, &request);
		
	}
}


