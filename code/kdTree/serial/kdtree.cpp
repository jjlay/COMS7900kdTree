//
// Local includes
//

#include "tree.h"
#include "importData .h"


//
// Standard includes
//

#include <string>

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

	string filename = "datafile00501.txt";
	auto data = importData(filename);


	// tree = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{}, 'n',{}, 'd', {}, 'c',{} );
	// tree(1).x1 = 0;
	// tree(1).x2 = 1;
	// tree(1).y1 = 0;
	// tree(1).y2 = 1;
	// tree = buildTree( data, tree );
	// disp("Tree complete!!!")
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
