
//
// Local includes
//

#include "tree.h"

//
// Standard includes
//

#include <fstream>
#include <string>


//
// Function: dumpTree
//

void dumpTree(Tree *t, int depth, ofstream *output) {

  string padding = "";

  for (auto i = 0; i < depth; i++)
    padding += " ";

  *output << padding << "----------" << endl
    << padding << "Depth: " << depth << endl
    << padding << "Name: " << t->Name << endl
    << padding << "----------" << endl;

  dumpTree(t->l, depth+1, output);
  dumpTree(t->r, depth+1, output);
}
