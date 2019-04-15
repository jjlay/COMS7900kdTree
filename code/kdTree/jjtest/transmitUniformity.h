#pragma once

#include "mpi.h"


//
// Function: transmitUniformity
//
// Parameters:
//    bins - pointer to the array of bin edges
//
//    numWorkers - number of workers
//
// Returns:
//    Nothing
//

void transmitUniformity( int *isUniform, int numWorkers, MPI_Comm comm);


