#pragma once

#include "mpi.h"


//
// Function: receiveBinCounts
//
// Parameters:
//    bins - pointer to the array of bin edges
//
//    numWorkers - number of workers
//
// Returns:
//    Nothing
//

void receiveBinCounts(int *bins, int numWorkers, MPI_Comm comm );


