//
// receiveFiles
//


//
// Parallel includes
//

#include "mpi.h"


//
// Standard includes
//

#include <string>
#include <iostream>
#include <stdlib.h>


//
// STL includes
//

#include <vector>


//
// Local includes
//

#include "definitions.h"

using namespace std;


//
// Function: receiveFiles
//
// Parameters:
//   myRank - the rank of the current process
//
// Returns:
//   A vector of strings containing the filenames
//   for this process to work on.
//

vector<string> receiveFiles(int myRank) {

	// The vector to hold the filenames
	vector<string> files;

	int mpiReturn;
	MPI_Request request;
	MPI_Status status;

	// Allocate memory for the buffer
	char *buffer = static_cast<char *>(calloc(mpi_Max_Filename * 2, sizeof(char)));

	// This is the expected string to signal that rank 0
	// is done sending files.
	string strDone = "DONE!";

	int Run = 1;
	
	mpiReturn = MPI_Irecv(buffer, mpi_Max_Filename, MPI_CHAR,
		Rank0, mpi_Tag_File, MPI_COMM_WORLD, &request);

	while(Run) {
		// Wait until one arrives since we do
		// not have anything else to do.
		MPI_Wait(&request, &status);

		mpiReturn = MPI_Irecv(buffer, mpi_Max_Filename, MPI_BYTE,
			Rank0, mpi_Tag_File, MPI_COMM_WORLD, &request);

		// Convert the filename to a C++ string
		auto s = string(buffer);

		// Have we received the signal to end?
		if (s == strDone) {
			Run = 0;
		}
		else {
			// If this is a filename, add it to our list.
			if (s.length() > 0)
				files.push_back(s);
		}
	}

	return files;
}


