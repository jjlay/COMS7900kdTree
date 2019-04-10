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

int testUniformity( int *binC, int numWorkers, float thresh, float *uniformity ) {
	// binC = bin counts
	
	int isUniform; 	// final returned value
	float test;
	float avgPts = (float) binC[0];
	float maxPts = (float) binC[0];
	float minPts = (float) binC[0];
	
	for( int i = 1; i < numWorkers; i++ ) {
		avgPts = avgPts + (float) binC[i];
		if( binC[i] > maxPts) {
			maxPts = (float) binC[i];
		}
		if( binC[i] < minPts) {
			minPts = (float) binC[i];
		}

	}
	avgPts = ( avgPts/numWorkers + 0.0000001 );
	
//	cout << minPts << " " << avgPts << " " << maxPts << endl;
	
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


