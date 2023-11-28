#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

//Check if an edge already exists
bool Node::existsEdge(Node *adc)
{
  listOfObjects<Node *> *iterator = head;//iterates over all edges
  while (iterator != NULL)
  {
    if (iterator->object->value == adc->value)
    {
      return true;
    }
    iterator = iterator->next;
  }
  return false;
}

//Insert an edge in the adjacency list of a node
void Node::insertEdge(Node *adjacentNode, Edge *edge)
{
  if (head == nullptr)//null adjacency list
  {
    head = new listOfObjects<Node *>(adjacentNode);
    tail = head;
    edgehead = new listOfObjects<Edge *>(edge);
    edgetail = edgehead;
  }
  else// non-null list
  {
    tail->next = new listOfObjects<Node *>(adjacentNode);
    tail->next->prev = tail;
    tail = tail->next;
    edgetail->next = new listOfObjects<Edge *>(edge);
    edgetail->next->prev = edgetail;
    edgetail = edgetail->next;
  }
}

//inserting in the BST
void BST::insert(int value)
{
  if (root == nullptr)//empty BST
  {
    root = new BSTNode(value);
    return;
  }
  BSTNode *iterator = root;//iterating to an empty position
  while (true)
  {
    if (iterator->value > value)//smaller insertion value than the value at node, go left
    {
      if (iterator->left == nullptr)// if left null, add node
      {
        iterator->left = new BSTNode(value);
        iterator->left->parent = iterator;
        return;
      }
      else
        iterator = iterator->left;
    }
    else//larger insertion value than the value at node, go right
    {
      if (iterator->right == nullptr)// if null, add node
      {
        iterator->right = new BSTNode(value);
        iterator->right->parent = iterator;
        return;
      }
      else
        iterator = iterator->right;
    }
  }
}

void BST::printBST(const string &prefix, bool isLeft) // Printing the BST
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->value << endl;
    BSTNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);//printing left
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);//printing right
    root = curr;
  }
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() // Initialization part
{
  for (int i = 0; i < numNodes; i++)//initiliazing data
  {
    visited[i] = 0;
    parents[0][i] = -1;
    parents[1][i] = -1;
  }
  listOfObjects<Edge*> *edges = edgeList;
  while(edges!=nullptr){
    edges->object->backtracked = false;
    edges = edges->next;
  }
  for (int i = 0; i < numNodes; i++)// running dfs such that it runs on all connected components
  {
    if (visited[i] == 0)//Not visited in any connected component yet, new component
    {
      BST *bst = new BST();//BST
      recursiveModDFS(i, bst);
      connectedComps++;
      if (bsts == nullptr)//first connectedcomponenet
      {
        bsts = new listOfObjects<BST *>(bst);
        endbsts = bsts;
      }
      else//more than one
      {
        endbsts->next = new listOfObjects<BST *>(bst);
        endbsts->next->prev = endbsts;
        endbsts = endbsts->next;
      }
    }
    if (visited[i] == 1)//visited once
    {
      visitedonce++;
    }
    else
    {
      visitedtwice++;//visited = 3 for my implementation, basically got to the node from the same edge twice
      if(visited[i] == 2){// got to the node from different edges, node is part of a cycle
         cyclicnodes++;
      }
    }
  }

  return;
}

void Graph::recursiveModDFS(int node, BST *bst)// recursion
{
  bst->insert(nodes[node].value);// inserting the node in the bst
  visited[node]++;//incrementing visited
  listOfObjects<Node *> *iterate = nodes[node].head;// adjacency lsit
  listOfObjects<Edge *> *edges = nodes[node].edgehead;
  while (iterate != nullptr)// iterating over the list
  {
    int index = iterate->object->value - 1;//index of adjacent node
    if (visited[index] < 2 && index != parents[0][node] && index != parents[1][node] && !edges->object->backtracked)
    {//not backtracked means edge is explored for the first time
      parents[visited[index]][index] = node;
      recursiveModDFS(index, bst);
      edges->object->backtracked = true;
    }
    else if (visited[index] < 2 && index != parents[0][node] && index != parents[1][node] && edges->object->backtracked)
    {//backtracked means came from an edge from which it had come earlier too
      parents[visited[index]][index] = node;
      recursiveModDFS(index, bst);
      visited[index]++;//visited set to 3
    }
    iterate = iterate->next;
    edges = edges->next;
  }
}

void Graph::printResults()
{//printing all the results
  cout << "Principal Components: " << connectedComps << endl
       << "Nodes visited once: " << visitedonce << endl
       << "Nodes visited twice: " << visitedtwice << endl
       << "Nodes in a cycle: " << cyclicnodes << endl;

  listOfObjects<BST *> *iterate = bsts;//printing all the bsts by iterating over the list
  int num = 1;
  while (iterate != nullptr)
  {
    cout << "BST number " << num << endl;
    iterate->object->printBST("");
    iterate = iterate->next;
    num++;
  }
  return;
}

#endif
