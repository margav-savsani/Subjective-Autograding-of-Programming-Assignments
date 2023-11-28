#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class Node
{
public:
  int value;

};

class Graph
{
  int numNodes;
  int numEdges;

  Node *nodes;


public:
  Graph(int nNodes, int nEdges)
  {
    numNodes = nNodes;
    numEdges = nEdges;
   
   
    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }
  }
  void CheckGAD();
};

#endif