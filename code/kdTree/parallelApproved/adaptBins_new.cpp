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
#include <iomanip>
#include <fstream>


using namespace std;


//
// Local includes
//
//

#include "definitions.h"

//
// Function: importFiles
//

void adaptBins_new( float *binE, int *binC, int numWorkers, int numLines, float avgPtsPerWorker ) {
	// binE = bin edges, binC = bin counts
	
	float *binE2   = new float[numWorkers+1];    // the new bin edges, copy to binE
	float *binCum  = new float[numWorkers+1];    // cumulative binC
//	float *totals  = new float[numWorkers-1];    //
//	int    *indices = new int[numWorkers-1];    // bin index in which the new edges lie	
	int     ind;
	
	// get binCum
	binCum[0] = 0;
	for( int j = 1; j < numWorkers+1; j++ ) {
		binCum[j] = binCum[j-1] + binC[j-1];
	}
	
	// get ind, binE2
	for( int j = 0; j < numWorkers-1; j++ ) {
		// get ind
		ind = 0;

		while( binCum[ind+1] < (j+1)*avgPtsPerWorker ) {
			ind++;
		}
		
		// get binE2
		binE2[j+1] = binE[ind] + ( (j+1)*avgPtsPerWorker - binCum[ind] )/binC[ind]*( binE[ind+1] - binE[ind] );
	}
	
	for( int i = 1; i < numWorkers; i++ ) {
		binE[i] = binE2[i];
	}
	
}

