//
// adaptBins
//


//
// Standard includes
//

#include <string>
#include <iostream>
#include <iomanip>



//
// Function: importFiles
//

void adaptBins( double *binE, int *binC, int numWorkers) {
	// binE = bin edges, binC = bin counts
	
	double *diff = new double[numWorkers+1];
	double dC, dB;
	
	for( int i = 1; i < numWorkers; i++ ) {
		
		dC = ( 2.0*(binC[i] - binC[i-1]) )/( 1.0*binC[i] + 1.0*binC[i-1] + 0.000001 );
		
	//	if( dC > 0 ) {
	//		dB = binE[i+1] - binE[i];
	//	} else if( dC < 0 ) {
	//		dB = -(binE[i] - binE[i-1]);
	//	} else {
	//		dB = 0;
	//	}
		dB = binE[i+1] - binE[i];
		
	//	diff[i] = 0.15*dC*dB;
	//	diff[i] = 0.45*dC*dB;
		diff[i] = 0.475*dC*dB;
	}
	
	for( int i = 1; i < numWorkers; i++ ) {
	//	std::cout << "adapt: " << i << " " << diff[i] << std::endl;
		binE[i] = binE[i] + diff[i];
	}
	
}

