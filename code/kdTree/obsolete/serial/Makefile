CC = g++
CFLAGS = -std=c++11 -O3

kdTree : kdTree.o circle.o importData.o plotTree.o searchTree.o buildTree.o sortData.o count.o searchTreeJJ.o
	$(CC) $(CFLAGS) -o kdTree kdTree.o circle.o importData.o plotTree.o searchTree.o buildTree.o sortData.o count.o searchTreeJJ.o

kdTree.o : kdTree.cpp tree.h importData.h definitions.h buildTree.h searchTree.h count.h searchTreeJJ.h
	$(CC) $(CFLAGS) -c kdTree.cpp

circle.o : circle.cpp tree.h
	$(CC) $(CFLAGS) -c circle.cpp

count.o : count.cpp tree.h
	$(CC) $(CFLAGS) -c count.cpp

importData.o : importData.cpp definitions.h
	$(CC) $(CFLAGS) -c importData.cpp

plotTree.o : plotTree.cpp tree.h
	$(CC) $(CFLAGS) -c plotTree.cpp

searchTree.o : searchTree.cpp tree.h
	$(CC) $(CFLAGS) -c searchTree.cpp

searchTreeJJ.o : searchTreeJJ.cpp tree.h definitions.h
	$(CC) $(CFLAGS) -c searchTreeJJ.cpp

buildTree.o : buildTree.cpp tree.h sortData.h definitions.h
	$(CC) $(CFLAGS) -c buildTree.cpp

sortData.o : sortData.cpp definitions.h
	$(CC) $(CFLAGS) -c sortData.cpp


clean :
	rm -f *.o
	rm -f kdtree
	rm -f gmon.out

