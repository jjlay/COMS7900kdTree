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
		void SortData(double *data, int numCols, int numRows, int dimension);
		double *ImportData(string filename, int *numCols, int *numRows);
		unsigned long int CalculateIndex(string filename);

		static int compareX(const void *a, const void *b);
		static int compareY(const void *a, const void *b);
		static int compareZ(const void *a, const void *b);
		static int compareIndex(const void *a, const void *b);


	public:
		//
		// Constructors
		//

		// Called by main to import data and begin tree construction
		Tree(string filename);

		// Used to create child nodes
		Tree(Tree *parent, double *data, int numCols, int numRows);

		// Deconstructor to clean up our mess
		~Tree();

		// Public methods
		void searchTree(double *found, Tree tree, double *c0, double rad);
		double *GetRange();
		double *GetCenter();
		int GetCount();
		int GetSortDimension();
		unsigned long int Dump(unsigned long int parent, unsigned long int key);
};

