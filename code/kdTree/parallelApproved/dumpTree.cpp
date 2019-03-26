
//
// Local includes
//

#include "tree.h"

//
// Standard includes
//

#include <fstream>
#include <string>
#include <iostream>


//
// Function: dumpTree
//

void dumpTree(Tree *t, int depth, ofstream *output, int rank) {

  string padding = "";

  for (auto i = 0; i < depth; i++)
    padding += "  ";

  *output << padding << "----------" << endl
    << padding << "Rank: " << rank << endl
    << padding << "Depth: " << depth << endl
    << padding << "Name: " << t->name << endl
    << padding << "----------" << endl;

  if (t->l != nullptr)
    dumpTree(t->l, depth+1, output);

  if (t->r != nullptr)
    dumpTree(t->r, depth+1, output);
}
