//
// Local includes
//

#include "tree.h"
#include "importData.h"
#include "definitions.h"
#include "buildTree.h"
#include "searchTree.h"
#include "searchTreeJJ.h"
#include "count.h"


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

int main( int argc, char *argv[] ) {
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

	// only used for prototype
/*
	tree->x1 = 0.0;
	tree->x2 = 1.0;
	tree->y1 = 0.0;
	tree->y2 = 1.0;
	tree->z1 = 0.0;
	tree->z2 = 1.0;
*/
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

	cout << "Left side had " << leftCount << " points, and the right side had " << rightCount << endl
		<< "Total points in tree were " << leftCount + rightCount << endl;


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

	auto startTreeSearch = std::chrono::system_clock::now();
	
	auto found = searchTreeJJ(tree, point, radius, 0);

	auto endTreeSearch = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTreeSearch = endTreeSearch - startTreeSearch;

	cout << "Found " << found << " points in " << elapsedTreeSearch.count() << " seconds" << endl;

	cout << endl << "=== DEBUG ===" << endl
		<< "Tree info:" << endl
		<< "x(min, max) " << tree->x1 << ", " << tree->x2 << endl
		<< "y(min, max) " << tree->y1 << ", " << tree->y2 << endl
		<< "z(min, max) " << tree->z1 << ", " << tree->z2 << endl
		<< "center " << tree->c[_X_] << ", " << tree->c[_Y_] << ", " << tree->c[_Z_] << endl
		<< "radius " << tree->radius << endl << endl
		<< "** Left child info:" << endl
		<< "   x(min, max) " << tree->l->x1 << ", " << tree->l->x2 << endl
		<< "   y(min, max) " << tree->l->y1 << ", " << tree->l->y2 << endl
		<< "   z(min, max) " << tree->l->z1 << ", " << tree->l->z2 << endl
		<< "   center " << tree->l->c[_X_] << ", " << tree->l->c[_Y_] << ", " << tree->l->c[_Z_] << endl
		<< "   radius " << tree->l->radius << endl << endl
		<< "** Right child info:" << endl
		<< "   x(min, max) " << tree->r->x1 << ", " << tree->r->x2 << endl
		<< "   y(min, max) " << tree->r->y1 << ", " << tree->r->y2 << endl
		<< "   z(min, max) " << tree->r->z1 << ", " << tree->r->z2 << endl
		<< "   center " << tree->r->c[_X_] << ", " << tree->r->c[_Y_] << ", " << tree->r->c[_Z_] << endl
		<< "   radius " << tree->r->radius << endl << endl;

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

