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
#include <string.h>


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
	char *buffer = (char *) calloc(mpi_Max_Filename * 2, sizeof(char));

	// This is the expected string to signal that rank 0
	// is done sending files.
	string strDone = "DONE!";

	int Run = 1;
	int count = 0;
	
	while(Run) {
		memset(buffer, 0, mpi_Max_Filename);

		mpiReturn = MPI_Irecv(buffer, mpi_Max_Filename, MPI_CHAR,
			Rank0, count, MPI_COMM_WORLD, &request);

		// Wait until one arrives since we do
		// not have anything else to do.
		MPI_Wait(&request, &status);

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

		cerr << (30000 + myRank * 100 + count) << " : receiveFiles: Rank " 
			<< myRank << " received " << buffer 
			<< " as tag " << count << endl;
		count++;
	}

	return files;
}


