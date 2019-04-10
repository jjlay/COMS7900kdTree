//
// Local includes
//

#include "definitions.h"


//
// Standard includes
//

#include <iostream>


//
// Parallel includes
//

#include "mpi.h"


//
// Function: transmitMinMax
//
// Parameters:
//   min - least value
//   max - greatest value
//
// Returns:
//   Nothing

void transmitMinMax( float min, float max, MPI_Comm comm ) {

	auto minMax = new float[2];

	minMax[_MIN_] = min;
	minMax[_MAX_] = max;

	int result = MPI_Send(minMax, 2, MPI_FLOAT, Rank0,
		mpi_Tag_SendMinMax, comm);
}


