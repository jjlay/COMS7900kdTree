
//
// Local includes
//

#include "definitions.h"
#include "importFiles.h"

//
// Parallel includes
//

#include "mpi.h"


//
// STL includes
//

#include <vector>


//
// Standard includes
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "tree.h"
#include "searchTree_serial.h"

using namespace std;


//
// Function: search501
//

void search501(int myRank, string path, Tree *tree) {
	
	//
	// Setup
	//
	
	string filename = path + "datafile00501.txt";
	const int maxSearchRows = 30000;
	const int numberRadii = 3;
	float radii[] = {0.01, 0.05, 0.10};
	
	//
	// Import the list of points to search
	//
	
	vector<string> listOfFiles;
	listOfFiles.push_back(filename);
	
	auto searchable = new float[_MAX_ROWS_ * _ROW_WIDTH_];
	unsigned long int maxArraySize = _MAX_ROWS_ * _ROW_WIDTH_;
	
	int rows = 0, cols = _ROW_WIDTH_;
	importFiles(listOfFiles, myRank, searchable, &rows, &cols, maxSearchRows,
	  maxArraySize);
	
	auto buffer = new float[_SEARCH_WIDTH_]();
	buffer[_SIGNAL_] = mpi_Signal_Run;
	const int messageSize = _SEARCH_WIDTH_;
	
	float point[4];
	unsigned long int offset;
	float radius;
	
	int *foundEach;
	int *foundAll;
	
	foundEach = (int*)malloc( rows*numberRadii*sizeof(int) );
	foundAll  = (int*)malloc( rows*numberRadii*sizeof(int) );
	
	for (auto rad = 0; rad < numberRadii; rad++) {
		for (auto r = 0; r < rows; r++) {
			// Perform the search
			radius = radii[rad];
			offset = r * _ROW_WIDTH_;
			point[0] = searchable[offset + _INDEX_];
			point[1] = searchable[offset + _X_];
			point[2] = searchable[offset + _Y_];
			point[3] = searchable[offset + _Z_];
			
			foundEach[ numberRadii*r + rad ] = searchTree_serial( point, radius, tree );
		}
	}
	
	// send
	MPI_Reduce( foundEach, foundAll, rows*numberRadii, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );
	if( myRank == 0 ) {
		cout << "==================" << endl
			<< "POINTS FOUND:" << endl
			<< " X             Y             Z            "
			<< setw(11) << fixed << setprecision(2) << radii[0] << "   " 
			<< setw(11) << fixed << setprecision(2) << radii[1] << "   " 
			<< setw(11) << fixed << setprecision(2) << radii[2] << endl
			<< "------------  ------------  ------------  ------------  ------------  ------------"
			<< endl;

		for (auto r = 0; r < rows; r++) {
			cout << setw(12) << fixed << setprecision(6) << searchable[r * _ROW_WIDTH_ + _X_] << "  "
				<< setw(12) << fixed << setprecision(6) << searchable[r * _ROW_WIDTH_ + _Y_] << "  "
				<< setw(12) << fixed << setprecision(6) << searchable[r * _ROW_WIDTH_ + _Z_] << "  "
				<< setw(12) << fixed << setprecision(0) << foundAll[ numberRadii*r ] << "  " 
				<< setw(12) << fixed << setprecision(0) << foundAll[ numberRadii*r + 1 ] << "  " 
				<< setw(12) << fixed << setprecision(0) << foundAll[ numberRadii*r + 2 ] << endl;
		}
	}
	
	free(foundEach);
	free(foundAll);
	
}





