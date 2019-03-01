//
// Local includes
//

#include "Tree.h"


//
// Standard includes
//

#include <iostream>

using namespace std;


//
// Method: Dump()
//
// Parameters:
//    key - The unique identity of the parent node
//
// Returns:
//    Largest unique identity
// 
// Description:
//
// This method dumps the content of a node along with all of 
// its children
//

unsigned long int Tree::Dump(unsigned long int parent, unsigned long int key)
{
	auto whoAmI = key + 1;
	auto nextKey = whoAmI;

	cout << endl << "===== Node " << whoAmI << " =====" << endl
		<< "Parent " << parent << endl
		<< "Left child: " << (left != nullptr ? "Yes" : "No") << endl
		<< "Right child: " << (right != nullptr ? "Yes" : "No") << endl
		<< "===========================" << endl
		<< endl;

	if (left != nullptr)
		nextKey = left->Dump(whoAmI, nextKey);

	if (right != nullptr)
		nextKey = right->Dump(whoAmI, nextKey);

	return nextKey;
}