
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

void dumpTree(Tree *t, int depth, ofstream *output) {

  string padding = "";

  for (auto i = 0; i < depth; i++)
    padding += "  ";

  cout << padding << "----------" << endl
      << padding << "Depth: " << depth << endl
      << padding << "Name: " << t->name << endl
      << padding << "----------" << endl;

  *output << padding << "----------" << endl
    << padding << "Depth: " << depth << endl
    << padding << "Name: " << t->name << endl
    << padding << "----------" << endl;

  if (t->l != nullptr)
    dumpTree(t->l, depth+1, output);

  if (t-r != nullptr)
    dumpTree(t->r, depth+1, output);
}
