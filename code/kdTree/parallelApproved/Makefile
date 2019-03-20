CC = mpicxx
CFLAGS = -std=c++11 -ggdb # -fbounds-check -Warray-bounds -Wall

# Removed LL_sort
main : main.o buildTree.o buildTree_serial.o buildTree_parallel.o parallelSort.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o transmitMinMax.o getLinearBins.o adaptBins.o testUniformity.o transmitMinMax.o receiveMinMax.o binData.o transmitBinEdges.o receiveBinCounts.o transmitUniformity.o receiveBinIndices.o exportResults.o sortArray.o min.o max.o swapArrayParts.o cleanUp.o testSort.o binData2.o sortData.o
	$(CC) $(CFLAGS) -o main main.o buildTree.o buildTree_serial.o buildTree_parallel.o parallelSort.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o getLinearBins.o adaptBins.o testUniformity.o transmitMinMax.o receiveMinMax.o binData.o transmitBinEdges.o receiveBinCounts.o transmitUniformity.o receiveBinIndices.o exportResults.o sortArray.o min.o max.o swapArrayParts.o cleanUp.o testSort.o binData2.o sortData.o



%.o : %.cpp definitions.h
	$(CC) $(CFLAGS) -c $< 

testbinsizing : testbinsizing.o
	$(CC) $(CFLAGS) -o testbinsizing testbinsizing.o

testbinsizing.o : testbinsizing.cpp
	$(CC) $(CFLAGS) -c testbinsizing.cpp

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
