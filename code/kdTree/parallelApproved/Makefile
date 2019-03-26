CC = mpicxx
CFLAGS = -std=c++11 -ggdb # -fbounds-check -Warray-bounds -Wall

main : main.o getSortDim.o buildTree.o buildTree_serial.o buildTree_parallel.o parallelSort.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o transmitMinMax.o getLinearBins.o adaptBins.o testUniformity.o transmitMinMax.o receiveMinMax.o binData.o transmitBinEdges.o receiveBinCounts.o transmitUniformity.o receiveBinIndices.o exportResults.o min.o max.o swapArrayParts.o cleanUp.o sortData.o
	$(CC) $(CFLAGS) -o main main.o getSortDim.o buildTree.o buildTree_serial.o buildTree_parallel.o parallelSort.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o getLinearBins.o adaptBins.o testUniformity.o transmitMinMax.o receiveMinMax.o binData.o transmitBinEdges.o receiveBinCounts.o transmitUniformity.o receiveBinIndices.o exportResults.o min.o max.o swapArrayParts.o cleanUp.o sortData.o

%.o : %.cpp definitions.h
	$(CC) $(CFLAGS) -c $<


clean :
	rm -f testbinsizing parallelSort main kdTree
	rm -f *.o
	rm -f core.*
	rm -f MetropolisKdTree.e2*
	rm -f MetropolisKdTree.o2*
	rm -f dump-*.txt


nolog :
	rm -f core.*
	rm -f MetropolisKdTree.e2*
	rm -f MetropolisKdTree.o2*
