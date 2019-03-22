#pragma once

//
// Parallel includes
//

#include "mpi.h"

//
// Standard includes
//

#include <string>

using namespace std;


//
// Struct
//

	// tree = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{}, 'n',{}, 'd', {}, 'c',{} );

struct Tree {
	Tree *p;  // Parent
	Tree *l;  // Left child
	Tree *r;  // Right child
	int i;    // Sort index

	MPI_Comm parentComm, leftComm, rightComm, thisComm;

	string name;

	double x1;  // Min x
	double x2;  // Max x
	double y1;  // Min y
	double y2;  // Max y
	double z1;  // Min z
	double z2;  // Max z

	int depth;
	int n;      // Number of points

	double c[4];  // Center of this tree
	double radius;

	double d[4];  // Data point
	double index;  // File row index
}
;
