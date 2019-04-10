#pragma once

#include "mpi.h"


//
// Function: transmitMinMax
//
// Parameters:
//   min - least value
//   max - greatest value
//
// Returns:
//   Nothing

void transmitMinMax( float min, float max, MPI_Comm comm );



