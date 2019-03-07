//
// Local includes
//

#include "tree.h"
#include "importData.h"
#include "sortData.h"
#include "definitions.h"
#include "buildTree.h"


//
// Standard includes
//

#include <string>
#include <iostream>

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

	sortData(data, cols, rows, _X_);
	auto rangeX = data[(rows - 1) * cols + _X_] - data[_X_];
	cout << endl <<  "Min X: " << data[_X_] << ", Max X: " << data[(rows - 1) * cols + _X_] << ", Range X: " << rangeX << endl << endl;

	sortData(data, cols, rows, _Y_);
	auto rangeY = data[(rows - 1) * cols + _Y_] - data[_Y_];
	cout << endl << "Min Y: " << data[_Y_] << ", Max Y: " << data[(rows - 1) * cols + _Y_] << ", Range Y: " << rangeY << endl << endl;

	sortData(data, cols, rows, _Z_);
	auto rangeZ = data[(rows - 1) * cols + _Z_] - data[_Z_];
	cout << endl << "Min Z: " << data[_Z_] << ", Max Z: " << data[(rows - 1) * cols + _Z_] << ", Range Z: " << rangeZ << endl << endl;


	// tree = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{}, 'n',{}, 'd', {}, 'c',{} );

	struct Tree tree;

	// tree(1).x1 = 0;
	// tree(1).x2 = 1;
	// tree(1).y1 = 0;
	// tree(1).y2 = 1;

	tree.x1 = 0.0;
	tree.x2 = 1.0;
	tree.y1 = 0.0;
	tree.y2 = 1.0;
	tree.z1 = 0.0;
	tree.z2 = 1.0;


	// tree = buildTree( data, tree );

	buildTree(data, rows, cols, &tree);

	// disp("Tree complete!!!")

	cout << "Tree completed" << endl;

	// 
	// data
	// 
	// center = [ 0.5, 0.5 ];
	// rad    = 0.25;
	// found  = searchTree( tree, center, rad )
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
}

