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

//
// Local includes
//
//

#include "definitions.h"


//
// Function: importFiles
//

void adaptBins( float *binE, int *binC, int NumWorkers, int numLines, float avgPtsPerWorker );
	

