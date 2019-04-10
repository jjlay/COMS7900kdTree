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

void transmitMinMax( double min, double max, MPI_Comm comm );



