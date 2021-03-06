#pragma once

//
// Local includes
//

#include "tree.h"


//
// Standard includes
//

#include <string>

using namespace std;


//
// Function: buildTree
//

void searchTree( float *point, float rad, float *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes, string name );


