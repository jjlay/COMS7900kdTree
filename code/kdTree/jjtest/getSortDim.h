//
// Parallel Sort
//

//
// Standard includes
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono> 

#include <unistd.h>
#include <time.h>
//
// Parallel includes
//

#include "mpi.h"


//
// Local includes
//

#include "tree.h"
#include "definitions.h"
#include "receiveMinMax.h"
#include "transmitMinMax.h"
#include "min.h"
#include "max.h"


using namespace std;


//
// Function: main
//

int getSortDim( float *data, int rows, int cols, Tree *tree, int myRank, int numNodes, MPI_Comm comm );


