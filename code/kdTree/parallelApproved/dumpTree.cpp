
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
    << padding << "Parent: " << (t->p == nullptr ? "none" : t->p->name) << endl
    << padding << "Left child: " << (t->l == nullptr ? "none" : t->l->name) << endl
    << padding << "Right child: " << (t->r == nullptr ? "none" : t->r->name) << endl
    << padding << "x-min: " << t->x1 << ", x-max: " << t->x2 << endl
    << padding << "y-min: " << t->y1 << ", y-max: " << t->y2 << endl
    << padding << "z-min: " << t->z1 << ", z-max: " << t->z2 << endl
    << padding << "Node depth: " << t->depth << endl
    << padding << "Number of points: " << t->n << endl
    << padding << "Center of node: " << c[_X_] << ", " << c[_Y_] << ", " << c[_Z_] <<endl
    << padding << "Radius: " << radius << endl
    << padding << "----------" << endl;

  if (t->l != nullptr)
    dumpTree(t->l, depth+1, output, rank);

  if (t->r != nullptr)
    dumpTree(t->r, depth+1, output, rank);
}
