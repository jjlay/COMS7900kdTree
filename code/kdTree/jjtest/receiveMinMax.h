#pragma once

#include "mpi.h"


//
// Function: receiveMinMax
//
// Parameters:
//   sourceRank - rank from which to receive the min and max
//   min - least value
//   max - greatest value
//
// Returns:
//   Nothing

void receiveMinMax(int sourceRank, float *min, float *max, MPI_Comm comm);


