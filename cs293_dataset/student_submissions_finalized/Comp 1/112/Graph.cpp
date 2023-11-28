#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// recursive DFS with helpful parameters
BST *Graph::myDFS(BST *myBST, int currNode, bool topLevelCall) // topLevelCall is only called from modified DFS
{
  if (topLevelCall)
  {
    myBST = new BST();
  }
  myBST->insert(nodes[currNode].value);
  nodes[currNode].numVisits++;
  listOfObjects<Node *> *neighbourList = adjacencyListArr[currNode];
  int neighbourIndex = 0;
  while (neighbourList != NULL)
  {
    if (neighbourList->object->numVisits == 0 && !(nodes[currNode].forbidden[neighbourIndex]))
    {
      // adding this node to the forbidden list of neighbour
      listOfObjects<Node *> *nnList = adjacencyListArr[neighbourList->object->value - 1]; // neighbours of neighbour
      int nnIndex = 0;                                                                    // neighbours of neighbour
      while (nnList != NULL)
      {
        if (nnList->object->value - 1 == currNode)
        {
          // found currNode
          nodes[neighbourList->object->value - 1].forbidden[nnIndex] = true;
          break;
        }
        nnList = nnList->next;
        nnIndex++;
      }
      myDFS(myBST, neighbourList->object->value - 1, false);
    }
    else if (neighbourList->object->numVisits == 1 && !(nodes[currNode].forbidden[neighbourIndex]))
    {
      // backedge. update cycles
      // add this node to the forbidden list of neighbour
      listOfObjects<Node *> *nnList = adjacencyListArr[neighbourList->object->value - 1]; // neighbours of neighbour
      int nnIndex = 0;                                                                    // neighbours of neighbour
      while (nnList != NULL)
      {
        if (nnList->object->value - 1 == currNode)
        {
          // found currNode
          nodes[neighbourList->object->value - 1].forbidden[nnIndex] = true;
          break;
        }
        nnList = nnList->next;
        nnIndex++;
      }
      myDFS(myBST, neighbourList->object->value - 1, false);
    }
    else if (neighbourList->object->numVisits == 2 && !(nodes[currNode].forbidden[neighbourIndex]))
    {
      // backedge. update cycles
    }
    neighbourList = neighbourList->next;
    neighbourIndex++;
  }
  if (topLevelCall)
  {
    return myBST;
  }
  else
  {
    // dummy return value
    return nullptr;
  }
}

void Graph::modifiedDFS()
{
  // reinitializing to zero in case this function is called repeatedly
  for (int i = 0; i < numNodes; i++)
  {
    nodes[i].numVisits = 0;
  }
  // this loop will run as many times as there are connected components
  while (true)
  {
    int doDFSOfMe = -1;
    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[i].numVisits == 0)
      {
        doDFSOfMe = i;
        break;
      }
    }
    if (doDFSOfMe == -1) // a value of -1 means that all components have been covered
    {
      break;
    }
    else // some components are leftover
    {
      if (components == nullptr)
      {
        components = new listOfObjects<BST *>(myDFS(nullptr, doDFSOfMe, true));
      }
      else
      {
        components->prev = new listOfObjects<BST *>(myDFS(nullptr, doDFSOfMe, true));
        components->prev->next = components;
        components = components->prev;
      }
      numComp++;
    }
  }
  return;
}

void Graph::printResults()
{
  int visTwice = 0; // number of nodes visited twice

  // calculating visTwice
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].numVisits == 2)
    {
      visTwice++;
    }
  }
  std::cout << "No. of connected components: " << numComp << std::endl;
  std::cout << "No. of nodes visited once: " << numNodes - visTwice << std::endl;
  std::cout << "No. of nodes visited twice: " << visTwice << std::endl;
  std::cout << "No. of nodes that are present in a cycle: "
            << "NOT IMPLEMENTED YET" << std::endl;
  int number = 1;

  // printing the trees
  while (components != nullptr)
  {
    std::cout << std::endl;
    std::cout << "Component " << number << ": " << std::endl;
    components->object->printBST("Hi", true);
    components = components->next;
    number++;
  }

  return;
}

#endif
