//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"

#include "min.h"
#include "max.h"

//
// Standard includes
//

#include <iostream>
#include <math.h>

using namespace std;


//
// Function: buildTree
//

int searchTree_serial(double *point, double rad, Tree *tree) {
	
	int myRank;
	MPI_Comm_rank( MPI_COMM_WORLD, &myRank);
	
	int found = 0;

	double distance2 = pow(point[_X_] - tree->c[_X_], 2.0) +
			   pow(point[_Y_] - tree->c[_Y_], 2.0) +
			   pow(point[_Z_] - tree->c[_Z_], 2.0);

//	cout << "zzzz " << myRank << " " << tree->depth << " " << tree->radius <<  " " << tree->c[_X_] << " " << tree->c[_Y_] << " " << tree->c[_Z_] << endl;
	
	
	int d = 1;
	
	if( distance2 <= pow((rad + tree->radius),2.0) ) {
		
		
		
		if ((tree->l == nullptr) && (tree->r == nullptr)) {
			// Data point
//			cout << "myRank: " << myRank << " the point: " << tree->d[1] << " " << tree->d[2] << " " << tree->d[3] << endl;
			return 1;
		}
		else {
			if( tree->l != nullptr ) {
				// Intersection!
				found += searchTree_serial( point, rad, tree->l );
			}
			if( tree->r != nullptr ) {
				found += searchTree_serial( point, rad, tree->r );
			}
		}
	}
	
	return found;
}




