#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{

  graphFile << "DFS:" << endl;
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 0)
    {
      DFS(i); //DFS is called
    }
    else 
    {
      numComp++; //number of connected components is increased
    }
  }

  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 1)
    {
      numOnce++;
    }
    if (visited[i] == 2)
    {
      numNodes_Cycle++;
      numTwice++;
    }
    visited[i] = 0;
  }

  return;
}

void Graph::printResults()
{
  graphFile << "No. of connected components: " << numComp << endl;
  graphFile << "No. of nodes visited once: " << numOnce << endl;
  graphFile << "No. of nodes visited twice: " << numTwice << endl;
  graphFile << "No. of nodes that are present in a cycle: " << numNodes_Cycle << endl;
  Tree->printBinaryTree(Tree->root, "", false);
  return;
}
void Graph::DFS(int v)
{
  static int vit = -1;
  visited[v]++;
  graphFile << v + 1 << endl;
  Tree->insert(v + 1);
  int val = v + 1;
  for (int i = 0; i < numNodes; i++)
  {
    if (adjacencyMatrix[v * numNodes + i] == 1 && (visited[i] != 2))
    {
      if (visited[i] == 1)
      {
        if(i!=vit){ //condition for not being parent
          DFS(i); // recursive call 
          vit = i;
        }
      }
      else if (visited[i] == 0)
      {
        DFS(i); //recursive call
      }
    }
  }
}
#endif
