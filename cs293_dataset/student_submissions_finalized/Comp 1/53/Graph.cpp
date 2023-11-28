#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::DFS(Node *currentNode, Node *parent, int &recursionLevel, listOfObjects<BST *> *tail_trees)
{
  recursionLevel++; // increasing the recursion level at the start of the call
  currentNode->visited++; // increasing its visited mark
  listOfObjects<Node *> *currNode = currentNode->adjacency_list; // the head of the adjacency list of the 
  if (currentNode->visited == 1)
  { //if visiting for the first time
    currentNode->dfsparent = parent; //set its original parent
    currentNode->arrtime = timecounter; // set its first arrival time
    timecounter++; // increase the timecounter
  }
  // Iterating through each node of the adjacency list
  while (currNode != nullptr)
  { // Here we are doing 2 things. First if there is a back edge from the "currentnode" to the iterator currNode(the next node) and also if we can proceed the DFS call of the next node
    bool move_ahead = false; 
    if (currentNode->dfsparent == nullptr)
      move_ahead = true;
    else if (currNode->object->value != currentNode->dfsparent->value)
      move_ahead = true;
    
    // Checking the node if there is back edge and if there is include all the points in the cycle traversing from currentNode to the next node via the DFS backwards
    if ((currNode->object->visited > 0) && (move_ahead == true) && (currNode->object->arrtime < currentNode->arrtime))
    {
      // traversing backwards in dfs and incycle = true
      Node *iterator_parent = currentNode;
      while (iterator_parent->value != currNode->object->value)
      {
        iterator_parent->inCycle = true;
        iterator_parent = iterator_parent->dfsparent;
        if (iterator_parent == nullptr)
          break;
      }
      if (iterator_parent != nullptr)
        iterator_parent->inCycle = true;
    }
    //Now checking if we can proceed to the DFS of next node
    if (currNode->object->visited != 2 && (move_ahead == true))
    {
      tail_trees->object->insert(currNode->object);
      
      DFS(currNode->object, currentNode, recursionLevel, tail_trees);
    }
    currNode = currNode->next;
  }
  recursionLevel--; // decreasing the recursion level before exiting
  return;
}

void Graph::modifiedDFS()
{ // 3 steps:
  // First check if that root was involved in previous any DFS or not
  // Second run the DFS starting from the roor
  // Finally checking again if the next root is applicable for next connected component

  static int recursionLevel = -1; // to check whether to make a new component or not
  static Node *root = nullptr; //This is the root of the binary search tree
  static int count = 0; // This keeps the counter of the number of nodes who have been surely dealt with

  //The first part
  if (recursionLevel == -1)
  {
    if (root == nullptr)
      root = nodes;
    if (root->visited != 0)
    {
      if (count < numNodes - 1)
      {
        count++;
        root++;
        modifiedDFS();
        return;
      }
      else
      {
        count = 0;
        root = nullptr;
        return;
      }
    }
    else
    {
      numConnectedComp++;
      BST *new_tree = new BST(root);
      listOfObjects<BST *> *new_listobject = new listOfObjects<BST *>(new_tree);
      if (trees == nullptr)
      {
        trees = new_listobject;
        tail_trees = trees;
      }
      else
      {
        tail_trees->next = new_listobject;
        new_listobject->prev = tail_trees;
        tail_trees = tail_trees->next;
      }
    }
  }

  //The second part

  DFS(root, nullptr, recursionLevel, tail_trees);

  if (recursionLevel == -1)
  {

    if (count < numNodes - 1)
    {
      count++;
      root++;
      modifiedDFS();
      return;
    }
    else
    {
      count = 0;
      root = nullptr;
      return;
    }
  }
  return;
}

// The third part

void Graph::printResults()
{ // Variables to be printed
  int visitedOnce = 0;
  int visitedTwice = 0;
  int incycle = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 1)
      visitedOnce++;
    else if (nodes[i].visited == 2)
      visitedTwice++;
    if (nodes[i].inCycle == true)
      incycle++;
  }
  listOfObjects<BST *> *currNode = trees;
  // Printing the BSTs
  while (currNode != nullptr)
  {
    currNode->object->printBST("");
    currNode = currNode->next;
  }
  //Printing the remaining parameters
  cout << "No. of connected components:" << numConnectedComp << endl;
  cout << "No. of nodes visited once :" << visitedOnce << endl;
  cout << "No. of nodes visited twice :" << visitedTwice << endl;
  cout << "No. of nodes in cycle :" << incycle << endl;

  return;
}

#endif
