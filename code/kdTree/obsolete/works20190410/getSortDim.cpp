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
#include <math.h>


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
//	cout << "Rank " << myRank
//		<< " Name " << tree->name
//		<< " is in getSortDim" << endl;
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
			receiveMinMax(r, &allMins[r][_X_], &allMaxs[r][_X_], comm);
		}
		
		minGlobal[_X_] = allMins[0][_X_];
		maxGlobal[_X_] = allMaxs[0][_X_];
		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal[_X_] > allMins[r][_X_] )
				minGlobal[_X_] = allMins[r][_X_];
			if( maxGlobal[_X_] < allMaxs[r][_X_] )
				maxGlobal[_X_] = allMaxs[r][_X_];
		}
		
		//cout << "Rank " << myRank
		//	<< " Name " << tree->name
		//	<<  " X: " << minGlobal[_X_] << " " << maxGlobal[_X_] << endl;
	} else {
		
		transmitMinMax(xMin, xMax, comm);
	}
	
//	cout << "Rank " << myRank
//		<< " Name " << tree->name
//		<< " is in getSortDim before y min" << endl;
	// y min/max
	if( myRank == 0 ) {
		allMins[0][_Y_] = yMin;
		allMaxs[0][_Y_] = yMax;
		for (auto r = 1; r < numNodes; r++) {
			receiveMinMax(r, &allMins[r][_Y_], &allMaxs[r][_Y_], comm);
		}
		
		minGlobal[_Y_] = allMins[0][_Y_];
		maxGlobal[_Y_] = allMaxs[0][_Y_];
		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal[_Y_] > allMins[r][_Y_] )
				minGlobal[_Y_] = allMins[r][_Y_];
			if( maxGlobal[_Y_] < allMaxs[r][_Y_] )
				maxGlobal[_Y_] = allMaxs[r][_Y_];
		}
		
		//cout << "Rank " << myRank 
		//	<< " Name " << tree->name
		//	<< " Y: " << minGlobal[_Y_] << " " << maxGlobal[_Y_] << endl;
	} else {
		transmitMinMax(yMin, yMax, comm);
	}
	
//	cout << "Rank " << myRank
//		<< " Name " << tree->name
//		<< " is in getSortDim before z min" << endl;
	// z min/max
	if( myRank == 0 ) {
		allMins[0][_Z_] = zMin;
		allMaxs[0][_Z_] = zMax;
		for (auto r = 1; r < numNodes; r++) {
			receiveMinMax(r, &allMins[r][_Z_], &allMaxs[r][_Z_], comm);
		}
		
		minGlobal[_Z_] = allMins[0][_Z_];
		maxGlobal[_Z_] = allMaxs[0][_Z_];
		for (auto r = 1; r < numNodes; r++) {
			if( minGlobal[_Z_] > allMins[r][_Z_] )
				minGlobal[_Z_] = allMins[r][_Z_];
			if( maxGlobal[_Z_] < allMaxs[r][_Z_] )
				maxGlobal[_Z_] = allMaxs[r][_Z_];
		}
		
		//cout << "Rank " << myRank 
		//	<< " Name " << tree->name
		//	<< " Z: " << minGlobal[_Z_] << " " << maxGlobal[_Z_] << endl;
	} else {
		transmitMinMax(zMin, zMax, comm);
	}
	
//	cout << "Rank " << myRank
//		<< " Name " << tree->name
//		<< " is in getSortDim before range" << endl;
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
	
	// bcast mins'maxs for tree storage
	MPI_Bcast( minGlobal, 4, MPI_DOUBLE, 0, tree->thisComm );
	MPI_Bcast( maxGlobal, 4, MPI_DOUBLE, 0, tree->thisComm );
	
	tree->x1 = minGlobal[_X_];
	tree->x2 = maxGlobal[_X_];
	tree->y1 = minGlobal[_Y_];
	tree->y2 = maxGlobal[_Y_];
	tree->z1 = minGlobal[_Z_];
	tree->z2 = maxGlobal[_Z_];
	
	tree->c[_INDEX_] = _Undefined_;
	tree->c[_X_] = (minGlobal[_X_] + maxGlobal[_X_]) / 2.0;
	tree->c[_Y_] = (minGlobal[_Y_] + maxGlobal[_Y_]) / 2.0;
	tree->c[_Z_] = (minGlobal[_Z_] + maxGlobal[_Z_]) / 2.0;

	tree->radius = sqrt(pow(tree->c[_X_] - minGlobal[_X_], 2.0) +
			pow(tree->c[_Y_] - minGlobal[_Y_], 2.0) +
			pow(tree->c[_Z_] - minGlobal[_Z_], 2.0));

//	cout << "Rank " << myRank
//		<< " Name " << tree->name 
//		<< " is about to broadcast" << endl;
	
	MPI_Bcast( &sortDim, 1, MPI_INT, 0, comm );

	return sortDim;
	
}



