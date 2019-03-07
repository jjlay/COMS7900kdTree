//
// Local includes
//

#include "tree.h"


//
// Function: searchTree
//

void searchTree(Tree *tree, double c0[4], double radius) {
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
}

