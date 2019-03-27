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

  if (buffer[_SIGNAL_] == mpi_Signal_Halt) {
    cout << "Rank " << myRank << " is halting searchWorker" << endl;
  }

  delete buffer;
}
