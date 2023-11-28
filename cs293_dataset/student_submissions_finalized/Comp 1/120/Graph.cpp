#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() // Modified DFS
{
  for (int i = 0; i < numNodes; i++)
  {
    if (numoftimes[i] == 0) // To count number of connected components
    {
      BST b;
      out.push_back(mDFS(i + 1, 0, b)); // pushing into vector
      connected++;                      // increasing connected
    }
  }
  return;
}
BST Graph::mDFS(int start, int parent, BST b)
{
  int z = 0;
  if (numoftimes[start - 1] <= 1)
  {
    b.insert(start);
    numoftimes[start - 1]++;
    for (int i = ((start - 1) * numNodes); i < (start * numNodes); i++)
    {
      if (adj[i] != 0 && i != (((start - 1) * numNodes) + parent - 1)) // checking in the adjacency matrix
      {
        adj[((i - ((start - 1) * numNodes)) * numNodes + (start - 1))] = 0; // removing back edge
        mDFS(i + 1 - ((start - 1) * numNodes), start, b);                   // recursion for dfs
        // adj[((start-1)*numNodes)+(i - ((start - 1) * numNodes))]=0;
      }
    }
  }
  if (parent != 0) // removing edge between parent and current node
  {
    adj[((parent - 1) * numNodes) + start - 1] = 0;
    // adj[((start-1)*numNodes)+parent-1]=0;
  }
  return b;
}

void Graph::printResults()
{
  int once = 0;                                                // dummy variable for once
  vector<int> ones;                                            // vector to store ones
  vector<int> twos;                                            // vector to store twos
  int twice = 0;                                               // dummy variable for twice
  cout << "No. of connected components:" << connected << endl; // connected componemts
  for (int i = 0; i < numNodes; i++)
  {
    if (numoftimes[i] == 1)
    {
      once++;                // increasing ones
      ones.push_back(i + 1); // appending it to vector
    }
    else
    {
      twice++;               // increaing twos
      twos.push_back(i + 1); // appending it to vector
    }
  }
  cout << "No. of nodes visited once:" << once;
  cout << "(";
  for (int i = 0; i < once; i++)
  {
    if (i != once - 1)
    {
      cout << ones[i] << ",";
    }
    else
    {
      cout << ones[i];
    }
  }
  cout << ")" << endl;
  cout << "No. of nodes visited twice:" << twice; // visited twice
  cout << "(";
  for (int i = 0; i < twice; i++)
  {
    if (i != twice - 1)
    {
      cout << twos[i] << ",";
    }
    else
    {
      cout << twos[i];
    }
  }
  cout << ")" << endl;
  int b = twice;
  cout << "No. of nodes that are present in a cycle:" << twice << endl; // printing number of cycles
  for (int i = 0; i < connected; i++)
  {
    out[i].printBST("");
  }


  return;
}

#endif
