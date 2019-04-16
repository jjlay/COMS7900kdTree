//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"

#include "min.h"
#include "max.h"

//
// Standard includes
//

#include <iostream>
#include <math.h>

using namespace std;


//
// Function: buildTree
//

void buildTree_serial(float *data, int *rows, int cols, Tree *tree) {

	// function tree = buildTree( data, tree )
	//
	//     % pause(0.1)
	//
	//     % get length
	//     [ nPts, nDim ] = size( data );
	//     tree(1).n = nPts;


	if (*rows > 1) {
		//     tree(1).c = [ 0.5*( min(data(:,1)) + max(data(:,1)) ), 0.5*( min(data(:,2)) + max(data(:,2)) )];
		//
		//     if nPts > 1
		//         disp("Creating branch...")
		//
		//         % get range and sortInd
		//         xmin = min( data(:,1) );
		//         xmax = max( data(:,1) );
		//         ymin = min( data(:,2) );
		//         ymax = max( data(:,2) );
		//
		//         xlen = xmax - xmin;
		//         ylen = ymax - ymin;
		//

		auto xMin = min( data, *rows, cols, _X_ );
		auto xMax = max( data, *rows, cols, _X_ );
		auto rangeX = xMax - xMin;

		// cout << endl << "Min X: " << xMin << ", Max X: " << xMax << ", Range X: " << rangeX << endl << endl;

		auto yMin = min( data, *rows, cols, _Y_ );
		auto yMax = max( data, *rows, cols, _Y_ );
		auto rangeY = yMax - yMin;

		// cout << endl << "Min Y: " << yMin << ", Max Y: " << yMax << ", Range Y: " << rangeY << endl << endl;

		auto zMin = min( data, *rows, cols, _Z_ );
		auto zMax = max( data, *rows, cols, _Z_ );
		auto rangeZ = zMax - zMin;

		// cout << endl << "Min Z: " << zMin << ", Max Z: " << zMax << ", Range Z: " << rangeZ << endl << endl;

		tree->c[_INDEX_] = _Undefined_;
		tree->c[_X_] = (xMax + xMin) / 2.0;
		tree->c[_Y_] = (yMax + yMin) / 2.0;
		tree->c[_Z_] = (zMax + zMin) / 2.0;

		tree->radius = sqrt(pow(tree->c[_X_] - xMin, 2.0) +
					 pow(tree->c[_Y_] - yMin, 2.0) +
					 pow(tree->c[_Z_] - zMin, 2.0));

		//         tree(1).x1 = xmin;
		//         tree(1).x2 = xmax;
		//         tree(1).y1 = ymin;
		//         tree(1).y2 = ymax;

		tree->x1 = xMin;
		tree->x2 = xMax;
		tree->y1 = yMin;
		tree->y2 = yMax;
		tree->z1 = zMin;
		tree->z2 = zMax;

		//
		//         if xlen > ylen
		//             sortInd = 1;
		//         else
		//             sortInd = 2;
		//         end

		int sortInd = _Undefined_;

		if ((sortInd == _Undefined_) && (rangeX >= rangeY) && (rangeX >= rangeZ))
			sortInd = _X_;

		if ((sortInd == _Undefined_) && (rangeY >= rangeX) && (rangeY >= rangeZ))
			sortInd = _Y_;

		if ((sortInd == _Undefined_) && (rangeZ >= rangeX) && (rangeZ >= rangeY))
			sortInd = _Z_;


		//         % sort
		//         [tmp, ind] = sort( data(:,sortInd) );

		sortData(data, cols, *rows, sortInd);

		//         dataSort   = zeros( nPts, 2 );
		//         if sortInd == 1
		//             dataSort(:,1) = tmp;
		//             dataSort(:,2) = data(ind,2);
		//         else
		//             dataSort(:,1) = data(ind,1);
		//             dataSort(:,2) = tmp;
		//         end
		//
		//         half = cast( floor(nPts/2), 'uint16' );

		int leftCount = *rows / 2;
		int rightCount = *rows - leftCount;

		auto leftPtr = &data[0];
		auto rightPtr = &data[(leftCount * cols)];

		//
		//         % call buildTree
		//         treeLeft  = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{} );
		//         treeRight = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{} );

		// Create the children
		tree->l = new Tree;
		tree->r = new Tree;

		// Set the children's parent
		tree->l->p = tree;
		tree->r->p = tree;

		buildTree_serial(leftPtr, &leftCount, cols, tree->l);
		buildTree_serial(rightPtr, &rightCount, cols, tree->r);
	}
	else
	{
		tree->d[_INDEX_] = data[_INDEX_];
		tree->d[_X_] = data[_X_];
		tree->d[_Y_] = data[_Y_];
		tree->d[_Z_] = data[_Z_];

		tree->c[_INDEX_] = data[_INDEX_];
		tree->c[_X_] = data[_X_];
		tree->c[_Y_] = data[_Y_];
		tree->c[_Z_] = data[_Z_];
		tree->radius = 0.0;

		tree->l = nullptr;
		tree->r = nullptr;
	}
}
