//
// Local includes
//

#include "tree.h"


//
// Function: count()
//

int count(Tree *tree)
{
	int c = 0;

	if (tree->l != nullptr)
		c += count(tree->l);

	if (tree->r != nullptr)
		c += count(tree->r);

	if ((tree->l == nullptr) && (tree->r == nullptr))
		c = 1;

	return c;
}

