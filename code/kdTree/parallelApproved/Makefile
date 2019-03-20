CC = mpicxx
CFLAGS = -std=c++11 -ggdb # -fbounds-check -Warray-bounds -Wall

main : main.o buildTree.o buildTree_serial.o buildTree_parallel.o parallelSort.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o transmitMinMax.o getLinearBins.o adaptBins.o testUniformity.o transmitMinMax.o receiveMinMax.o binData.o transmitBinEdges.o receiveBinCounts.o transmitUniformity.o receiveBinIndices.o exportResults.o sortArray.o min.o max.o swapArrayParts.o cleanUp.o binData2.o sortData.o importData.o
	$(CC) $(CFLAGS) -o main main.o buildTree.o buildTree_serial.o buildTree_parallel.o parallelSort.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o getLinearBins.o adaptBins.o testUniformity.o transmitMinMax.o receiveMinMax.o binData.o transmitBinEdges.o receiveBinCounts.o transmitUniformity.o receiveBinIndices.o exportResults.o sortArray.o min.o max.o swapArrayParts.o cleanUp.o binData2.o sortData.o importData.o

%.o : %.cpp definitions.h
	$(CC) $(CFLAGS) -c $< 


clean :
	rm -f testbinsizing parallelSort main kdTree
	rm -f *.o
	rm -f core.*
	rm -f MetropolisSort.e*
	rm -f MetropolisSort.o*


nolog :
	rm -f core.*
	rm -f MetropolisSort.e*
	rm -f MetropolisSort.o*
