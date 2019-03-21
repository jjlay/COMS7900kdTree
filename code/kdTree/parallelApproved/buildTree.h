#pragma once

//
// Local includes
//

#include "tree.h"


//
// Function: buildTree
//

void buildTree( double *data, int rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes );


