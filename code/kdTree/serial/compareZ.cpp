//
// Local includes
//

#include "definitions.h"
#include "Tree.h"


//
// Function: compareZ()
//

int Tree::compareZ(const void *a, const void *b)
{
	if (static_cast<const double *>(a)[_Z_] < static_cast<const double *>(b)[_Z_])
		return -1;

	if (static_cast<const double *>(a)[_Z_] == static_cast<const double *>(b)[_Z_])
		return 0;

	if (static_cast<const double *>(a)[_Z_] > static_cast<const double *>(b)[_Z_])
		return 1;
}
