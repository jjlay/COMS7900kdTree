#pragma once

#include "mpi.h"


//
// Parallel Sort
//


//
// Function: main
//

void parallelSort( int myRank, int numNodes, double *tmpArray[], int *rows, int *cols, int sortInd, MPI_Comm comm );

