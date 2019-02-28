//
// Local includes
//

#include "definitions.h"
#include "Tree.h"


//
// Function: compareY()
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

