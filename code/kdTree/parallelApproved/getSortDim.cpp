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

#include "tree.h"
#include "definitions.h"
#include "receiveMinMax.h"
#include "transmitMinMax.h"
#include "min.h"
#include "max.h"


using namespace std;


//
// Function: main
//

int getSortDim( double *data, int rows, int cols, Tree *tree, int myRank, int numNodes, MPI_Comm comm )
{
	int sortDim = _X_;
	
	// get local xyz min max
	auto xMin = min( data, rows, cols, _X_ );
	auto xMax = max( data, rows, cols, _X_ );
	
	auto yMin = min( data, rows, cols, _Y_ );
	auto yMax = max( data, rows, cols, _Y_ );
	
	auto zMin = min( data, rows, cols, _Z_ );
	auto zMax = max( data, rows, cols, _Z_ );
	
	auto allMins   = new double[numNodes][_ROW_WIDTH_];
	auto allMaxs   = new double[numNodes][_ROW_WIDTH_];
	auto minGlobal = new double[_ROW_WIDTH_];
	auto maxGlobal = new double[_ROW_WIDTH_];
	
	// x min/max
	if( myRank == 0 ) {
		allMins[0][_X_] = xMin;
		allMaxs[0][_X_] = xMax;
		for (auto r = 1; r < numNodes; r++) {
			receiveMinMax(r, &allMins[r][_X_], &allMaxs[r][_X_]);
		}
		
		minGlobal[_X_] = allMins[0][_X_];
		maxGlobal[_X_] = allMaxs[0][_X_];
		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal[_X_] > allMins[r][_X_] )
				minGlobal[_X_] = allMins[r][_X_];
			if( maxGlobal[_X_] < allMaxs[r][_X_] )
				maxGlobal[_X_] = allMaxs[r][_X_];
		}
		
		cout << "X: " << minGlobal[_X_] << " " << maxGlobal[_X_] << endl;
	} else {
		transmitMinMax(xMin, xMax);
	}
	
	// y min/max
	if( myRank == 0 ) {
		allMins[0][_Y_] = yMin;
		allMaxs[0][_Y_] = yMax;
		for (auto r = 1; r < numNodes; r++) {
			receiveMinMax(r, &allMins[r][_Y_], &allMaxs[r][_Y_]);
		}
		
		minGlobal[_Y_] = allMins[0][_Y_];
		maxGlobal[_Y_] = allMaxs[0][_Y_];
		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal[_Y_] > allMins[r][_Y_] )
				minGlobal[_Y_] = allMins[r][_Y_];
			if( maxGlobal[_Y_] < allMaxs[r][_Y_] )
				maxGlobal[_Y_] = allMaxs[r][_Y_];
		}
		
		cout << "Y: " << minGlobal[_Y_] << " " << maxGlobal[_Y_] << endl;
	} else {
		transmitMinMax(yMin, yMax);
	}
	
	// z min/max
	if( myRank == 0 ) {
		allMins[0][_Z_] = zMin;
		allMaxs[0][_Z_] = zMax;
		for (auto r = 1; r < numNodes; r++) {
			receiveMinMax(r, &allMins[r][_Z_], &allMaxs[r][_Z_]);
		}
		
		minGlobal[_Z_] = allMins[0][_Z_];
		maxGlobal[_Z_] = allMaxs[0][_Z_];
		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal[_Z_] > allMins[r][_Z_] )
				minGlobal[_Z_] = allMins[r][_Z_];
			if( maxGlobal[_Z_] < allMaxs[r][_Z_] )
				maxGlobal[_Z_] = allMaxs[r][_Z_];
		}
		
		cout << "Z: " << minGlobal[_Z_] << " " << maxGlobal[_Z_] << endl;
	} else {
		transmitMinMax(zMin, zMax);
	}
	
	if( myRank == 0 ) {
		auto rangeX = maxGlobal[_X_] - minGlobal[_X_];
		auto rangeY = maxGlobal[_Y_] - minGlobal[_Y_];
		auto rangeZ = maxGlobal[_Z_] - minGlobal[_Z_];
		
		double test = 0;
		
		if( rangeX > test ) {
			sortDim = _X_;
			test = rangeX;
		}
		if( rangeY > test ) {
			sortDim = _Y_;
			test = rangeY;
		}
		if( rangeZ > test ) {
			sortDim = _Z_;
		}
	}
	
	MPI_Bcast( &sortDim, 1, MPI_INT, 0, comm );
	
	return sortDim;
	
}



