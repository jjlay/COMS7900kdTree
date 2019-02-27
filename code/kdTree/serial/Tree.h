#pragma once

//
// Standard includes
//

#include <string>

using namespace std;


class Tree {
	private:
		// Child nodes
		Tree *left, *right;

		// Parent node
		Tree *parent;

		double xMin, xMax, yMin, yMax, zMin, zMax;
		double xCenter, yCenter, zCenter;
		double radius;

		int pointsContained;

		int dimensionSorted;
		double splitValue;

		// For a single data point
		int isDataPoint;
		double x, y, z;
		int index; // index from the row in the file

		//
		// Private methods that cannot be called outside of the class
		//

		double *SplitData(double *data, int numCols, int numRows);
		void SortData(double *data, int numCols, int numRows);


	public:
		Tree(string filename);
		Tree();
		~Tree();
		int SearchTree(double x, double y, double z, double radius);
		double *GetRange();
		double *GetCenter();
		int GetCount();
		int GetSortDimension();
};

