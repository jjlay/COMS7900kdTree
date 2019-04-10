//
// getLinearBins
//


//
// Standard includes
//

#include <string>
#include <iostream>


//
// Function: getLinearBins
//

void getLinearBins( float *binE, int numWorkers, int myRank,
	float minGlobal, float maxGlobal ) {
	
	float width = (maxGlobal - minGlobal);
	
	for( int i = 0; i < numWorkers+1; i++ ) {
		
		binE[i] = minGlobal + width*( (1.0*i)/numWorkers );
	}

	binE[0]          = binE[0] - width*0.0001;
	binE[numWorkers] = binE[numWorkers] + width*0.0001;
	
}

