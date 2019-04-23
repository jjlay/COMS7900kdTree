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

void searchTree_parallel( double *point, double rad, double *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes );


