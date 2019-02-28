//
// Local includes
//

#include "Tree.h"
#include "definitions.h"


//
// Standard includes
//

#include <string>

using namespace std;


//
// Function:  main
//

int main(int argc, char *argv[]) {
	
	auto theTree = new Tree("datafile00501.txt");

	auto contained = theTree->SearchTree(0.0, 0.0, 0.0, 0.1);
	
	return _OKAY_;
}

