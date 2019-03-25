//
// testUniformity
//


//
// Standard includes
//

#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

//
// Function: testUniformity
//

int testUniformity( int *binC, int numWorkers, double thresh, double *uniformity ) {
	// binC = bin counts
	
	int isUniform; 	// final returned value
	double test;
	double avgPts = (double) binC[0];
	double maxPts = (double) binC[0];
	double minPts = (double) binC[0];
	
	for( int i = 1; i < numWorkers; i++ ) {
		avgPts = avgPts + (double) binC[i];
		if( binC[i] > maxPts) {
			maxPts = (double) binC[i];
		}
		if( binC[i] < minPts) {
			minPts = (double) binC[i];
		}

	}
	avgPts = ( avgPts/numWorkers + 0.0000001 );
	
	cout << minPts << " " << avgPts << " " << maxPts << endl;
	
	
	// average metric
//	*uniformity = (maxPts - avgPts)/avgPts + (avgPts - minPts)/avgPts;
//	*uniformity = *uniformity/2;
	
	// max metric
	*uniformity = (maxPts - avgPts)/avgPts;
	test = (avgPts - minPts)/avgPts;
	if( test > *uniformity )
		*uniformity = test;
	
	if( *uniformity < thresh ){
		isUniform = 1;
	} else {
		isUniform = 0;
	}
	
	return isUniform;
	
}


