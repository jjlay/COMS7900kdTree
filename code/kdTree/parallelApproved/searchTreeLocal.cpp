//
// Local includes
//

#include "tree.h"
#include "definitions.h"


//
// Standard includes
//

#include <math.h>


//
// Function: searchTreeJJ
//

int searchTreeLocal(Tree *tree, double searchCenter[4], double radius, int depth) {
	//
	// function [ found ] = searchTree( tree, c0, rad )
	//
	//     % check left
	//     xlen  = tree(1).x2 - tree(1).x1;
	//     ylen  = tree(1).y2 - tree(1).y1;
	//
	//     check = ( abs( tree(1).c(1) - c0(1) ) <= abs( rad + xlen/2 ) ) && ...
	//             ( abs( tree(1).c(2) - c0(2) ) <= abs( rad + ylen/2 ) );
	//
	//     found = [];
	//     if check == 1
	//         L = [];
	//         R = [];
	//         if tree(1).n > 1
	//             L = searchTree( tree(1).l, c0, rad );
	//             R = searchTree( tree(1).r, c0, rad );
	//             found = [ L; R ];
	//         else
	//             found = tree(1).d;
	//         end
	//     end
	//     tree(1).n
	//     found
	//
	// end
	//
	//

	int found = 0;

	double distance = sqrt(pow(searchCenter[_X_] - tree->c[_X_], 2.0) +
				pow(searchCenter[_Y_] - tree->c[_Y_], 2.0) +
				pow(searchCenter[_Z_] - tree->c[_Z_], 2.0));

	if (distance <= (radius + tree->radius)) {
		if ((tree->l == nullptr) && (tree->r == nullptr)) {
			// Data point
			return 1;
		}
		else {
			// Intersection!
			found += searchTreeLocal(tree->l, searchCenter, radius, depth+1);
			found += searchTreeLocal(tree->r, searchCenter, radius, depth+1);
		}
	}


	return found;
}
