CC = mpicxx
CFLAGS = -std=c++11 -ggdb # -fbounds-check -Warray-bounds -Wall

importTest : importTest.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o 
	$(CC) $(CFLAGS) -o importTest importTest.o initializeMPI.o listFiles.o distributeFiles.o receiveFiles.o importFiles.o 

%.o : %.cpp definitions.h
	$(CC) $(CFLAGS) -c $<


clean :
	rm -f testbinsizing parallelSort main kdTree
	rm -f *.o
	rm -f core.*
	rm -f importTest*.e2*
	rm -f importTest*.o2*
	rm -f dump*.txt
	rm -f importTest

nolog :
	rm -f core.*
	rm -f importTest*.e2*
	rm -f importTest*.o2*
	rm -f dump*.txt

