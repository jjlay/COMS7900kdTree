//
// swapArrayParts
//

//#undef _DEBUG_


//
//STL includes
//

#include <vector>

//
//Standard Includes
//

#include <sys/time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h> 
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include "mpi.h"

//
//Local includes
//

#include "swapArrayParts.h"
#include "definitions.h"


//
//Function: swapArrayParts
//
using namespace std;

struct Node{
	double ll_location;
	double ll_x;
	double ll_y;
	double ll_z;
	struct Node *next;
};

void swapArrayParts(double *pmyArray[], int *rowPTR , int *colPTR, int myrank, int numranks, int *binIPTR, int fromWho, int toWho, MPI_Comm comm){

	if (toWho == fromWho)
		return;

	MPI_Request request;
        MPI_Status status;
        int maxRank = numranks;
        int myRank = myrank;
        int *myBinI;
        myBinI  =(int*) malloc((maxRank+1)*sizeof(int));
        int *yourBinI;
        yourBinI = (int*) malloc((maxRank+1)*sizeof(int));
        int *storedBinIstart;
        storedBinIstart = (int*)malloc((maxRank+1)*sizeof(int));
        int *storedBinIend;
        storedBinIend = (int*)malloc((maxRank+1)*sizeof(int));
        int myStartRow = 0;
        int myEndRow = 0;
        int myArrayLength = colPTR[0]*rowPTR[0];
        int myAmountToReceive;
        int myAmountToSend;
        int mySendStartingPoint;
        double *myArray;
	myArray = (double*)malloc((rowPTR[0]*4)*sizeof(double));
//	cout << "MY RANK swap " << myRank << endl;
	for(int fill0 =0; fill0< rowPTR[0]*4  ;fill0++){
		myArray[fill0] = *(*pmyArray+fill0);
	}
//	cout << endl;
	if(fromWho == myRank) {
                for(int mi =0; mi<maxRank+1; mi++){
                        myBinI[mi] = binIPTR[mi];
                }
                MPI_Isend(myBinI, (maxRank+1), MPI_INT, toWho,999, comm, &request);
        }
        if(myRank ==toWho){
                MPI_Recv(yourBinI, (maxRank+1), MPI_INT, fromWho , 999, comm, &status);
                myStartRow = yourBinI[myRank];
                myEndRow = yourBinI[myrank+1];
                storedBinIstart[fromWho+1] = myStartRow;
                storedBinIend[fromWho+1] = myEndRow;
        }
        if(myRank == fromWho){
                myAmountToSend = 4*(myBinI[toWho+1]-myBinI[toWho]);
                mySendStartingPoint = 4*(myBinI[toWho]);
                MPI_Isend(&myArray[mySendStartingPoint], myAmountToSend, MPI_DOUBLE, toWho, 888,  comm, &request);
	}
        if(myRank == toWho){
                myAmountToReceive = 4*(myEndRow-myStartRow);
                double *receiveThis;
                receiveThis = (double*) malloc((myAmountToReceive)*sizeof(double));
                MPI_Recv(receiveThis, myAmountToReceive, MPI_DOUBLE, fromWho, 888 , comm,&status);
                double *tempArray;
                tempArray = (double*) malloc(((rowPTR[0]*4)+(myAmountToReceive))*sizeof(double));
                for(int fill = 0; fill< (rowPTR[0]*4);fill++){
                        tempArray[fill] = myArray[fill];
                }
                for(int fill2 = (rowPTR[0]*4); fill2 < (rowPTR[0]*4)+myAmountToReceive; fill2++){
                        tempArray[fill2] = receiveThis[fill2-rowPTR[0]*4];
                }
//		cout << "My rank free pmyArray : " << myRank << endl;
		//free(pmyArray);
		*pmyArray = (double*) malloc(((rowPTR[0]*4)+(myAmountToReceive))*sizeof(double));
//		cout << "my rank reallock pmyArray : " << myRank << endl;
		for(int fill3 = 0; fill3<(rowPTR[0]*4)+myAmountToReceive; fill3++){
			*(*pmyArray+fill3) = tempArray[fill3];			
		}
		free(tempArray);
                rowPTR[0]= rowPTR[0]+ myAmountToReceive/4;
		free(receiveThis);
        }
	free(myArray);
	free(myBinI);
	free(yourBinI);
	free(storedBinIend);
	free(storedBinIstart);
//sleep(myRank);
//	cout << "MY rank : " << myRank << endl;
//	for(int fill4 = 0; fill4<(rowPTR[0]*4); fill4++){
//		cout << *(*pmyArray+fill4) << " " ;
//	}
//	cout << endl;
//sleep(999999999);

return;
}













