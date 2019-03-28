//
// adaptBins
//


//
// Standard includes
//

#include <string>
#include <iostream>
#include <iomanip>

#include "math.h"

using namespace std;

//
// Function: importFiles
//

void adaptBins_old( double *binE, int *binC, int numWorkers, int step ) {
	// binE = bin edges, binC = bin counts
	
	double *diff = new double[numWorkers+1];
	double dC, dB, scale;
	
	for( int i = 1; i < numWorkers; i++ ) {
		
		dC = ( 2.0*(binC[i] - binC[i-1]) )/( 1.0*binC[i] + 1.0*binC[i-1] + 0.000001 );
//		cout << dC << " ";
		
	//	if( dC > 0 ) {
	//		dB = binE[i+1] - binE[i];
	//	} else if( dC < 0 ) {
	//		dB = -(binE[i] - binE[i-1]);
	//	} else {
	//		dB = 0;
	//	}
		dB = binE[i+1] - binE[i];
		
		scale = 1 - (1 - 0.1)*(1 - exp(-0.03*step));
	//	cout << scale << endl;
		
	//	diff[i] = 0.15*dC*dB;
	//	diff[i] = 0.45*dC*dB;
		diff[i] = 0.475*scale*dC*dB;
	}
	
	for( int i = 1; i < numWorkers; i++ ) {
		binE[i] = binE[i] + diff[i];
	}
	
}

