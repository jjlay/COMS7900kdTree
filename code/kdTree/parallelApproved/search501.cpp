
//
// Local includes
//

#include "definitions.h"
#include "importFiles.h"


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

void search501(int myRank) {
  cout << "Rank " << myRank << " has started search501" << endl;

  //
  // Setup
  //

  const string filename = "data501.txt";
  const int maxSearchRows = 10;

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

  for (auto rad = 0; rad < numberRadii; rad++) {
    for (auto r = 0; r < rows; r++) {
      // Perform the search
      unsigned long int offset = r * _ROW_WIDTH_;
      auto searchX = searchable[offset + _X_];
      auto searchY = searchable[offset + _Y_];
      auto searchZ = searchable[offset + _Z_];
      auto searchIndex = searchable[offset + _INDEX_];
      auto radius = radii[rad];
      
    }
  }
}
