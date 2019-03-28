
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

using namespace std;


//
// Function: search501
//

void search501(int myRank, string path) {
  cout << "Rank " << myRank << " has started search501" << endl;

  //
  // Setup
  //

  string filename = path + "datafile00501.txt";
  const int maxSearchRows = 5;

  const int numberRadii = 3;
  double radii[] = {0.01, 0.05, 0.10};

  //
  // Import the list of points to search
  //

  vector<string> listOfFiles;
  listOfFiles.push_back(filename);

  auto searchable = new double[_MAX_ROWS_ * _ROW_WIDTH_];
  unsigned long int maxArraySize = _MAX_ROWS_ * _ROW_WIDTH_;

  int rows = 0, cols = _ROW_WIDTH_;
  importFiles(listOfFiles, myRank, searchable, &rows, &cols, maxSearchRows,
    maxArraySize);

  auto buffer = new double[_SEARCH_WIDTH_]();
  buffer[_SIGNAL_] = mpi_Signal_Run;
  const int messageSize = _SEARCH_WIDTH_;

  for (auto rad = 0; rad < numberRadii; rad++) {
    for (auto r = 0; r < rows; r++) {
      // Perform the search
      unsigned long int offset = r * _ROW_WIDTH_;
      auto searchX = searchable[offset + _X_];
      auto searchY = searchable[offset + _Y_];
      auto searchZ = searchable[offset + _Z_];
      auto searchIndex = searchable[offset + _INDEX_];
      auto radius = radii[rad];

      buffer[_X_] = searchX;
      buffer[_Y_] = searchY;
      buffer[_Z_] = searchZ;
      buffer[_RADIUS_] = radius;
      MPI_Bcast((void *)buffer, messageSize, MPI_DOUBLE, Rank0, MPI_COMM_WORLD);
    }
  }

  buffer[_SIGNAL_] = mpi_Signal_Halt;
  MPI_Bcast((void *)buffer, messageSize, MPI_DOUBLE, Rank0, MPI_COMM_WORLD);
  delete buffer;
}