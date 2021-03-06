//
// Local includes
//

#include "tree.h"
#include "sortData.h"
#include "definitions.h"


//
// Standard includes
//

#include <iostream>
#include <math.h>

using namespace std;


//
// Function: buildTree
//

void buildTree(double *data, int rows, int cols, Tree *tree) {

	// function tree = buildTree( data, tree )
	//     
	//     % pause(0.1)
	//     
	//     % get length
	//     [ nPts, nDim ] = size( data );
	//     tree(1).n = nPts;

	tree->n = rows;

	if (rows > 1) {
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

		sortData(data, cols, rows, _X_);

		auto xMin = data[_X_];
		auto xMax = data[(rows - 1) * cols + _X_];
		auto rangeX = xMax - xMin;

		// cout << endl << "Min X: " << xMin << ", Max X: " << xMax << ", Range X: " << rangeX << endl << endl;

		sortData(data, cols, rows, _Y_);

		auto yMin = data[_Y_];
		auto yMax = data[(rows - 1) * cols + _Y_];
		auto rangeY = yMax - yMin;

		// cout << endl << "Min Y: " << yMin << ", Max Y: " << yMax << ", Range Y: " << rangeY << endl << endl;

		sortData(data, cols, rows, _Z_);

		auto zMin = data[_Z_];
		auto zMax = data[(rows - 1) * cols + _Z_];
		auto rangeZ = zMax - zMin;

		// cout << endl << "Min Z: " << zMin << ", Max Z: " << zMax << ", Range Z: " << rangeZ << endl << endl;

		tree->c[_Index_] = _Undefined_;
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

		sortData(data, cols, rows, sortInd);

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

		int leftCount = rows / 2;
		int rightCount = rows - leftCount;

		//         
		//         tree(1).i = sortInd;

		tree->i = sortInd;

		//         tree(1).v = 0.5*( dataSort(half,sortInd) + dataSort(half+1,sortInd) );
		//         
		//         % split
		//         dataLeft  = dataSort(1:half,:);
		//         dataRight = dataSort(half+1:end,:);

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

		tree->l->depth = tree->depth + 1;
		tree->r->depth = tree->depth + 1;

		//         
		// %         if sortInd == 1
		// %             treeLeft(1).x1 = tree(1).x1;
		// %             treeLeft(1).x2 = tree(1).v;
		// %             treeLeft(1).y1 = tree(1).y1;
		// %             treeLeft(1).y2 = tree(1).y2;
		// %             
		// %             treeRight(1).x1 = tree(1).v;
		// %             treeRight(1).x2 = tree(1).x2;
		// %             treeRight(1).y1 = tree(1).y1;
		// %             treeRight(1).y2 = tree(1).y2;
		// %         else
		// %             treeLeft(1).x1 = tree(1).x1;
		// %             treeLeft(1).x2 = tree(1).x2;
		// %             treeLeft(1).y1 = tree(1).y1;
		// %             treeLeft(1).y2 = tree(1).v;
		// %             
		// %             treeRight(1).x1 = tree(1).x1;
		// %             treeRight(1).x2 = tree(1).x2;
		// %             treeRight(1).y1 = tree(1).v;
		// %             treeRight(1).y2 = tree(1).y2;
		// %         end
		//         
		//         if ~isempty(dataLeft)
		//             treeLeft = buildTree( dataLeft, treeLeft );
		//         end
		//         if ~isempty(dataLeft)
		//             treeRight = buildTree( dataRight, treeRight );
		//         end
		//         
		//         treeLeft(1).p = tree;
		//         treeLeft(1).p = tree;
		//                 
		//         tree(1).l = treeLeft;
		//         tree(1).r = treeRight;

		buildTree(leftPtr, leftCount, cols, tree->l);
		buildTree(rightPtr, rightCount, cols, tree->r);
	}
	else
	{
		//     else
		//         tree(1).d  = data;
		//         tree(1).c  = data;
		//         tree(1).x1 = data(1);
		//         tree(1).x2 = data(1);
		//         tree(1).y1 = data(2);
		//         tree(1).y2 = data(2);
		//         disp("Branch complete")
		//     end
		//     
		// end
		// 

		tree->d[_Index_] = data[_Index_];
		tree->d[_X_] = data[_X_];
		tree->d[_Y_] = data[_Y_];
		tree->d[_Z_] = data[_Z_];

		tree->c[_Index_] = data[_Index_];
		tree->c[_X_] = data[_X_];
		tree->c[_Y_] = data[_Y_];
		tree->c[_Z_] = data[_Z_];
		tree->radius = 0.0;

		tree->l = nullptr;
		tree->r = nullptr;

		// cout << "Depth of " << tree->depth << endl;
	}
}




