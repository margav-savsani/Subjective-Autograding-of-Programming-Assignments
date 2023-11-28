#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS2(int node, int currenComp, BST* &BSTArray)
{


  

  this->connectedComponents[node] = currenComp;
  Node *currentNode = &nodes[node];
 
  for (int i = 0; i < currentNode->currentSize; i++)
  {
    int neighborNode = currentNode->adjacencyList[i]->value - 1;
   
    if (visited[neighborNode] == 0)
    {
      visited[neighborNode]++;

      BSTArray[currenComp].insert(node);
      nodes[neighborNode].parents[0] = node;
  
      modifiedDFS2(neighborNode, currenComp, BSTArray);
    }
    else if (visited[neighborNode] == 1 && !currentNode->checkIfParent(neighborNode ))
    {

      BSTArray[currenComp].insert(node);
      visited[neighborNode]++;

      int cycleNode = neighborNode;
      // cout<<cycleNode<<endl;
      int currNode = node;
      int parent = currentNode->parents[1] == -1 ? currentNode->parents[0] : currentNode->parents[1];

      int *exploredNodes = new int[numNodes];

      for (int i = 0; i < numNodes; i++)
      {
        exploredNodes[i] = 0;
      }

      bool found = 0;

      while (parent != -1 && !exploredNodes[currNode])
      {
        
        
        exploredNodes[currNode]++;
       
        currNode = parent;
        parent = nodes[currNode].parents[1] == -1 ? nodes[currNode].parents[0] : nodes[currNode].parents[1];
        
        if (currNode == cycleNode)
        {
          // cout<<"here"<<endl;
          exploredNodes[currNode]++;
          found = 1;
          break;
        }
      }
      if (found)
      {
        for (int i = 0; i < numNodes; i++)
        {
          incycle[i] = exploredNodes[i];
        }
      }

      nodes[neighborNode].parents[1] = node;
      modifiedDFS2(neighborNode, currenComp, BSTArray);
    }
  }
  if(nodes[node].currentSize == 0)
  {
    visited[node]++;
  }
}
void Graph::modifiedDFS()
{
  conComps = 0;
  visOnce = 0;
  visTwice = 0;
  inCycle = 0;
 
  int currentComp = 1;
  for (int i = 0; i < numNodes; i++)
  { 
    // cout<<nodes[i].currentSize<<endl;
    if (connectedComponents[i] == 0)
    {
      modifiedDFS2(i, currentComp, BSTArray);
      currentComp++;
    }
  }
  int curCon = 1;
  for (int i = 0; i < numNodes; i++)
  {
 
    if (connectedComponents[i] == curCon)
      conComps = curCon++;
    if (incycle[i] == 1)
      inCycle++;
    if (visited[i] == 1)
    {
      visOnce++;
      // cout << i << endl;
    }
    if (visited[i] == 2)
      visTwice++;
  }
}
void Graph::printResults()
{

  cout << "No of connected components: " << conComps << endl;
  cout << "No of nodes visited once: " << visOnce << endl;
  cout << "No of nodes visited twice: " << visTwice << endl;
  cout << "No of nodes in cycle: " << inCycle << endl;

  for (int i = 0; i < numNodes; i++)
  {
    if(BSTArray[i].root !=  nullptr)
    {
      BSTArray[i].printBST("",true);
    }
  }
  
}

#endif