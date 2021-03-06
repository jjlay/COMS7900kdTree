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

void searchTree( double *point, double rad, double *data[], int *rows, int cols, Tree *tree, MPI_Comm comm, int myRank, int numNodes, string name );


