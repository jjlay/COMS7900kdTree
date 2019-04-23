#pragma once

#include "mpi.h"


//
// Function: receiveBinIndices
//
// Parameters:
//    bins - pointer to the array of bin edges
//
//    numWorkers - number of workers
//
// Returns:
//    Nothing
//

void receiveBinIndices(int **binI, int numWorkers, MPI_Comm comm);


