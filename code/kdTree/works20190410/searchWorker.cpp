//
// Parallel includes
//

#include "mpi.h"

//
// Local includes
//

#include "definitions.h"


//
// Standard includes
//

#include <iostream>
#include <iomanip>

using namespace std;


//
// Function: searchWorker
//

void searchWorker(int myRank) {

  cout << "Rank " << myRank << " is a searchWorker" << endl;

  auto buffer = new double[_SEARCH_WIDTH_]();
  const int messageSize = _SEARCH_WIDTH_;

  MPI_Bcast((void *)buffer, messageSize, MPI_DOUBLE, Rank0, MPI_COMM_WORLD);

  while (buffer[_SIGNAL_] == mpi_Signal_Run) {
    cout << "Rank " << myRank << " searching (" << buffer[_X_]
      << ", " << buffer[_Y_] << ", " << buffer[_Z_] << ") in radius "
      << buffer[_RADIUS_] << endl;

      MPI_Bcast((void *)buffer, messageSize, MPI_DOUBLE, Rank0, MPI_COMM_WORLD);
  }

  cout << "Rank " << myRank << " is halting searchWorker" << endl;

  delete buffer;
}
