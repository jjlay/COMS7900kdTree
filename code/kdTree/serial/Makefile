CC = g++
CFLAGS = -std=c++11

kdtree : main.o CalculateIndex.o Deconstructor.o ImportData.o SortData.o Tree.o compareIndex.o compareX.o compareY.o compareZ.o searchTree.o
	$(CC) $(CFLAGS) -o kdtree *.o

%.o : %.cpp definitions.h
	$(CC) $(CFLAGS) -c $< 

clean :
	rm -f kdtree
	rm -f *.o

