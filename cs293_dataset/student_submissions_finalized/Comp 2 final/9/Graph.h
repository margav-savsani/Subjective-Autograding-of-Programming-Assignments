#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Node
{
public:
  int value;
  int froms;
  Node **from;
  int tos;
  Node **to;
  int source;
  int decomposed_value;

  Node()
  {
    value = 0;
    decomposed_value = 0;
  }

  Node(int v)
  {
    value = v;
    froms = 0;
    tos = 0;
    source = 0;
    decomposed_value = v;
  }
};

class Graph
{
  int numNodes;
  int *similarpairs;
  int similarcount;
  Node *nodes;
  int **similar;
  int *decomposed;
  int **collapsed_edges;
  int countedges;

public:
  Graph(int nNodes)
  {
    numNodes = nNodes;

    nodes = new Node[nNodes];

    similarcount = 0;
    similarpairs = new int[2 * nNodes * nNodes];

    similar = new int *[nNodes];
    decomposed = new int[nNodes];
    collapsed_edges = new int *[nNodes * nNodes];
    countedges = 0;

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i] = Node(i + 1);
      nodes[i].from = new Node *[nNodes];
      nodes[i].to = new Node *[nNodes];
      similar[i] = new int[nNodes];

      for (int J = 0; J < nNodes; J++)
      {
        similar[i][J] = 0;
      }
    }
    for (int i = 0; i < numNodes*numNodes; i++)
    {
      collapsed_edges[i] = new int[2];
    }
  }

  ~Graph()
  {
    delete[] nodes;
  }

  void insertNode(int from, int to);
  void checkSource();
  void insertSimilar(int similar1, int similar2);
  void checkSimilar3();
  void checkSimilar2(int n);
  void collapse();
  void printResults();
};

#endif
