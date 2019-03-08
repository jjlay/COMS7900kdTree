//
// Local includes
//

#include "tree.h"
#include "importData.h"
#include "sortData.h"
#include "definitions.h"
#include "buildTree.h"
#include "searchTree.h"


//
// Standard includes
//

#include <string>
#include <iostream>
#include <chrono>

using namespace std;


// % Concerns:
// % 1) for non 2^n data, check for dataL/dataR are empty
// % 2) pass structs by reference so they get changed at all levels
// % 
// % 
// % 
// % 
// 

int main(int argc, char *argv) {
	// %%%%%%%%%%%%
	// %%% main %%%
	// %%%%%%%%%%%%
	// nPts = 10;
	// 
	// % generate data
	// data = rand( nPts, 2 );
	// 

	int rows = 0, cols = 0;
	string filename = "datafile00501.txt";
	auto data = importData(filename, &cols, &rows);


	// tree = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{}, 'n',{}, 'd', {}, 'c',{} );

	auto tree = new struct Tree;

	// tree(1).x1 = 0;
	// tree(1).x2 = 1;
	// tree(1).y1 = 0;
	// tree(1).y2 = 1;

	tree->x1 = 0.0;
	tree->x2 = 1.0;
	tree->y1 = 0.0;
	tree->y2 = 1.0;
	tree->z1 = 0.0;
	tree->z2 = 1.0;
	tree->p = nullptr;
	tree->depth = 0;


	// tree = buildTree( data, tree );
	auto startTreeBuild = std::chrono::system_clock::now();

	buildTree(data, rows, cols, tree);

	// disp("Tree complete!!!")
	auto endTreeBuild = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTreeBuild = endTreeBuild - startTreeBuild;

	cout << "Tree completed in " << elapsedTreeBuild.count() << " seconds" << endl;

	auto leftCount = count(tree->l);
	auto rightCount = count(tree->r);

	cout << "Left side had " << leftCount << " points, and the right side had " << rightCount << endl;


	// 
	// data
	// 
	// center = [ 0.5, 0.5 ];
	// rad    = 0.25;
	// found  = searchTree( tree, center, rad )

	auto point = new double[4];
	point[_X_] = 0.5;
	point[_Y_] = 0.5;
	point[_Z_] = 0.5;
	point[_Index_] = _Undefined_;

	double radius = 0.25;

	searchTree(tree, point, radius);


	// 
	// 
	// 
	// 
	// % plot data
	// figure('Renderer', 'painters', 'Position', [600 10 650 650])
	// hold on
	// plot( data(:,1), data(:,2), 'b.', 'MarkerSize', 12 )
	// plot( data(:,1), data(:,2), 'bo', 'MarkerSize', 8 )
	// % plotTree( tree )
	// circle( center(1), center(2), rad)
	// axis( [ 0, 1, 0, 1 ] )
	// hold off

	// %%%%%%%%%%%%
	// %%% done %%%
	// %%%%%%%%%%%%

	return _OKAY_;
}

