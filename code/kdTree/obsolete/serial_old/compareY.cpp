//
// Local includes
//

#include "definitions.h"
#include "Tree.h"


//
// Function: compareY()
//
// Parameters:
//    a - First value to compare
//    b - Second value to compare
//
// Returns:
//    Returns -1 if a < b
//             0 if a = b
//             1 if a > b
//

int Tree::compareY(const void *a, const void *b)
{
	if (static_cast<const double *>(a)[_Y_] < static_cast<const double *>(b)[_Y_])
		return -1;

	if (static_cast<const double *>(a)[_Y_] == static_cast<const double *>(b)[_Y_])
		return 0;

	if (static_cast<const double *>(a)[_Y_] > static_cast<const double *>(b)[_Y_])
		return 1;
}

