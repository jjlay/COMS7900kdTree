#pragma once

//
// Standard includes
//

#include <string>

using namespace std;


class Tree {
	private:
		int dummy;
	
	
	public:
		Tree(string filename);
		Tree();
		~Tree();
		int SearchTree(double x, double y, double z, double radius);
};

