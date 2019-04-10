#pragma once

//
// Local includes
//

#include "tree.h"
#include "getSortDim.h"

#include "mpi.h"


//
// Function: buildTree
//

void buildTree_parallel( float *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes );


