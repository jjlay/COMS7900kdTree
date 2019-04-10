#pragma once


//
// Function: transmitBinEdges
//
// Parameters:
//    bins - pointer to the array of bin edges
//
//    numWorkers - number of workers
//
// Returns:
//    Nothing
//

void transmitBinEdges(float *bins, int numWorkers, MPI_Comm comm);


