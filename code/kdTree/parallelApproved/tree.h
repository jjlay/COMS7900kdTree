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

	MPI_Comm parentComm, leftComm, rightComm, thisComm;

	string name;

	float x1;  // Min x
	float x2;  // Max x
	float y1;  // Min y
	float y2;  // Max y
	float z1;  // Min z
	float z2;  // Max z

	int depth;

	float c[4];  // Center of this tree
	float radius;

	float d[4];  // Data point
}
;
