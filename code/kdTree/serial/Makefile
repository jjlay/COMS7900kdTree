CC = g++
CFLAGS = -std=c++11

kdtree : kdtree.o circle.o importData.o plotTree.o searchTree.o buildTree.o tree.h
	$(CC) $(CFLAGS) -o kdtree kdtree.o

kdtree.o : kdtree.cpp tree.h
	$(CC) $(CFLAGS) -c kdtree.cpp

circle.o : circle.cpp tree.h
	$(CC) $(CFLAGS) -c circle.cpp

importData.o : importData.cpp tree.h
	$(CC) $(CFLAGS) -c importData.cpp

plotTree.o : plotTree.cpp tree.h
	$(CC) $(CFLAGS) -c plotTree.cpp

searchTree.o : searchTree.cpp tree.h
	$(CC) $(CFLAGS) -c searchTree.cpp

buildTree.o : buildTree.cpp tree.h
	$(CC) $(CFLAGS) -c buildTree.cpp


clean :
	rm -f *.o
	rm -f kdtree


