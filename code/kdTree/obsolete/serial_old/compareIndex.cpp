//
// Local includes
//

#include "definitions.h"
#include "Tree.h"


//
// Method: compareIndex()
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

int Tree::compareIndex(const void *a, const void *b)
{
	if (static_cast<const double *>(a)[_Index_] < static_cast<const double *>(b)[_Index_])
		return -1;

	if (static_cast<const double *>(a)[_Index_] == static_cast<const double *>(b)[_Index_])
		return 0;

	if (static_cast<const double *>(a)[_Index_] > static_cast<const double *>(b)[_Index_])
		return 1;
}
