#pragma once

//
// importFiles
//


#undef _DEBUG_


//
// STL includes
//

#include <vector>

//
// Standard includes
//

#include <string>
#include <iostream>
#include <fstream>

#include <math.h>

//
// Local includes
//
//

#include "definitions.h"
#include "Data.h"


//
// Function: binDAta
//

void binData( float *data, float *binE, int myRank, int numWorkers, int numPoints, int *binI, int *binC);


