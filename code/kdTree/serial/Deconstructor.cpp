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
// Deconstructor
//

Tree::~Tree()
{
	cout << "Destroyed!" << endl;

	if (left != nullptr) {
		delete left;
		left = nullptr;
	}

	if (right != nullptr) {
		delete right;
		right = nullptr;
	}

}