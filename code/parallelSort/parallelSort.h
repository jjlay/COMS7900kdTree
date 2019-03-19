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

#include "definitions.h"
#include "initializeMPI.h"
#include "listFiles.h"
#include "distributeFiles.h"
#include "receiveFiles.h"
#include "importFiles.h"
#include "getLinearBins.h"
#include "adaptBins.h"
#include "testUniformity.h"
#include "binData.h"
#include "binData2.h"
#include "receiveMinMax.h"
#include "transmitMinMax.h"
#include "transmitBinEdges.h"
#include "receiveBinCounts.h"
#include "transmitUniformity.h"
#include "receiveBinIndices.h"
#include "sortArray.h"
#include "exportResults.h"
#include "min.h"
#include "max.h"
#include "LL_sort.h"
#include "swapArrayParts.h"
#include "cleanUp.h"
#include "testSort.h"


using namespace std;


//
// Function: main
//

void parallelSort( int myRank, int numNodes, double *tmpArray[], int *rows, int *cols, int sortInd );

