//
// Local includes
//

#include "tree.h"
#include "sortData.h"


//
// Standard includes
//

#include <iostream>

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
	auto rangeX = data[(rows - 1) * cols + _X_] - data[_X_];
	cout << endl << "Min X: " << data[_X_] << ", Max X: " << data[(rows - 1) * cols + _X_] << ", Range X: " << rangeX << endl << endl;

	sortData(data, cols, rows, _Y_);
	auto rangeY = data[(rows - 1) * cols + _Y_] - data[_Y_];
	cout << endl << "Min Y: " << data[_Y_] << ", Max Y: " << data[(rows - 1) * cols + _Y_] << ", Range Y: " << rangeY << endl << endl;

	sortData(data, cols, rows, _Z_);
	auto rangeZ = data[(rows - 1) * cols + _Z_] - data[_Z_];
	cout << endl << "Min Z: " << data[_Z_] << ", Max Z: " << data[(rows - 1) * cols + _Z_] << ", Range Z: " << rangeZ << endl << endl;



	//         tree(1).x1 = xmin;
	//         tree(1).x2 = xmax;
	//         tree(1).y1 = ymin;
	//         tree(1).y2 = ymax;
	//         
	//         if xlen > ylen
	//             sortInd = 1;
	//         else
	//             sortInd = 2;
	//         end
	//         
	//         % sort
	//         [tmp, ind] = sort( data(:,sortInd) );
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
	//         
	//         tree(1).i = sortInd;
	//         tree(1).v = 0.5*( dataSort(half,sortInd) + dataSort(half+1,sortInd) );
	//         
	//         % split
	//         dataLeft  = dataSort(1:half,:);
	//         dataRight = dataSort(half+1:end,:);
	//         
	//         % call buildTree
	//         treeLeft  = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{} );
	//         treeRight = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{} );
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
}
