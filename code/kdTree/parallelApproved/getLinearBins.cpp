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
#include "Data.h"

//
// Function: getLinearBins
//

void getLinearBins( double *binE, int numWorkers, int myRank,
	double minGlobal, double maxGlobal ) {
	
	double width = (maxGlobal - minGlobal);
	
	for( int i = 0; i < numWorkers+1; i++ ) {
		
		binE[i] = minGlobal + width*( (1.0*i)/numWorkers );
		// print for debug
	//	std::cout << "linear bin edge " << i << ": " << binE[i] << std::endl;
	}
	binE[0]          = binE[0] - width*0.0001;
	binE[numWorkers] = binE[numWorkers] + width*0.0001;
	
}

