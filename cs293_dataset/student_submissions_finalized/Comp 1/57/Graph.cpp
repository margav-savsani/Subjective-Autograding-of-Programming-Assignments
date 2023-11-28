#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

static int start = 0; //  Global static varible used for recursion and counting no of components
BST *b = new BST();   // global varible used in insertion and deletion

// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{

  if (starting == 1) // I have to insert after starting connected components
  {
    // b.insert(nodes[start].value);
    b->insert(nodes[start].value); // inserting into tree
    visited[start]++;              // visited array
    int k = start;
    for (int i = 0; i < numNodes; i++) // finding adjacent vertices
    {

      if (tempadj[k][i])
      {
        tempadj[i][k] = 0;

        if (visited[i] < 2)
        {
          start = i;
          modifiedDFS();
        }
      }
    }
    start = k;
    tempadj[k] = adjlist[k];
  }
}
void Graph::connectedcomponents()
{
  starting = 1;
  int count = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 0)
    {
      b = new BST();
      count++;   // for counting number of components
      start = i; // for updating starting vertex of DFS

      cout << "BST component number :  " << count << endl;
      modifiedDFS();

      b->printBST("");
      cout << "....................................................." << endl;
    }
  }
  cout << "no of connected components are :  " << count << endl;
  int vistedonce = 0;   // for storing visited once
  int visitedtwice = 0; // for storing visited twice
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 1)
    {
      vistedonce++;
    }
    if (visited[i] == 2)
    {
      visitedtwice++;
    }
  }
  // for printing in required manner
  cout << "no of nodes visited once: " << vistedonce << endl;
  cout << "no of nodes visited twice: " << visitedtwice << endl;
}
int Graph::noofcyclicnodes(int number)

{
  // repeatedly removing vertex of degree 1 untill all nodes have degree >2
  // repeating untill all nodes with degree 1 is removed
  int *degree = new int[numNodes];
  int count = 0;
  for (int i = 0; i < numNodes; i++)
  {
    degree[i] = 0;
  }
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (counting[i][j] == 1)
      {
        degree[i]++;
      }
    }
    if (degree[i] < 2)
    {
      for (int k = 0; k < numNodes; k++)
      {
        counting[i][k] = 0;
        counting[k][i] = 0;
      }
    }
    else
      count++;
  }
  if (count != number)
  {
    return noofcyclicnodes(count);
  }
  else
  {
    return count;
  }
}

void Graph::printResults()
{
  connectedcomponents();
  int k = noofcyclicnodes(numNodes);
  cout << "total no of nodes that are present in  atleast one cycle is :  " << k << endl;
  return;
}

#endif
