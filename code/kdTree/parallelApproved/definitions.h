#pragma once

//
// Definitions
//

//
// Control
// 

#define _DEBUG_
#define _TIMING_
//#undef _TIMING_

#define _Undefined_ -1

//
// Return Values
//

#define _OKAY_   0
#define _FAIL_  -1


//
// Node Status
//

#define NodeUndefined  -1
#define NodeExit       -3


//
// MPI Tags
//

#define mpi_Tag_Name         10
#define mpi_Tag_State        20
#define mpi_Tag_File         30
#define mpi_Tag_SendMinMax   40

#define mpi_Tag_BinEdges     50
#define mpi_Tag_BinCounts    55
#define mpi_Tag_BinIndices   56

#define mpi_Tag_isUnif       60
#define mpi_Tag_RowCount     70


//
// MPI Colors
//

#define mpi_Color_Left   0
#define mpi_Color_Right  1


//
// MPI lengths
//

#define mpi_Max_Filename  100


//
// other variables
//


#define Rank0    0
#define abortCount  5000  // Number of loops to halt in adaptBins




//
// Used for transmitting min and max
//

#define _MIN_  0
#define _MAX_  1


//
// Data map
//

#define _INDEX_   0
#define _X_       1
#define _Y_       2
#define _Z_       3
#define _ROW_WIDTH_   4
#define _MAX_ROWS_ 20000000  // Max number of rows in file


