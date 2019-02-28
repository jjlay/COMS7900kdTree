//
// Local includes
//

#include "definitions.h"
#include "Tree.h"


//
// Function: compareIndex()
//

int Tree::compareIndex(const void *a, const void *b)
{
	if (static_cast<const double *>(a)[_Index_] < static_cast<const double *>(b)[_Index_])
		return -1;

	if (static_cast<const double *>(a)[_Index_] == static_cast<const double *>(b)[_Index_])
		return 0;

	if (static_cast<const double *>(a)[_Index_] > static_cast<const double *>(b)[_Index_])
		return 1;
}
