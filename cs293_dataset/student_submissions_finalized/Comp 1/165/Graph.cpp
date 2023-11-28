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

  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 0)
    {
      
      // this creates new BFS trees for all connected components
      DFStree[countTrees] = new BST(countTrees);
      modifiedRecursiveDFS(&nodes[i]);
      countTrees++;//stores number of connected components0
    }
  }
  return;
}

bool Graph::member(Node *node, LinkedList *list)//helper function
{ // to checkk if node is part of the LinkedList
  LinkedList *list1 = list;
  while (list1 != nullptr)
  {
    if (node->value == list1->Listnode->value)
    {
      return true;
    }
    list1 = list1->next;
  }
  return false;
}

void Graph::modifiedRecursiveDFS(Node *startnode)
{

  startnode->visited++;
  DFStree[countTrees]->insert(startnode->value);//insering into BST
  LinkedList *adjacent = startnode->adjList;
  LinkedList *predecessorlist = startnode->predecessors;
  while (adjacent != nullptr)//traversing the adjacent list
  {

    if (adjacent->Listnode->visited <2 && !member(adjacent->Listnode, predecessorlist) && !member(adjacent->Listnode,startnode->backtrack)){
      //only elements of cycle get visited twice as we restrict it to visit adjacent nodes which are not immediate predecssors and not have not backtracked to this node
      LinkedList *temp = adjacent->Listnode->predecessors;
      if (adjacent->Listnode->predecessors == nullptr)//formation of the predecessor list
      {
        adjacent->Listnode->predecessors = new LinkedList(startnode);
        adjacent->Listnode->tailpredecessor = adjacent->Listnode->predecessors;
      }
      else
      {
        adjacent->Listnode->tailpredecessor->next = new LinkedList(startnode);
        adjacent->Listnode->tailpredecessor->next->prev = adjacent->Listnode->tailpredecessor;
        adjacent->Listnode->tailpredecessor = adjacent->Listnode->tailpredecessor->next;
      }
      modifiedRecursiveDFS(adjacent->Listnode);
      LinkedList* tailbacktrack;
      if (startnode->backtrack == nullptr)//formation of the backtracking list
      {
        startnode->backtrack = new LinkedList(adjacent->Listnode);
        startnode->tailbacktrack = startnode->backtrack;
      }
      else
      {
        startnode->tailbacktrack->next = new LinkedList(adjacent->Listnode);
        startnode->tailbacktrack->next->prev = startnode->tailbacktrack;
        startnode->tailbacktrack = startnode->tailbacktrack->next;
      }
    }
    if (adjacent->Listnode->visited <2 && !member(adjacent->Listnode, predecessorlist) && member(adjacent->Listnode,startnode->backtrack)){
      //to calculate twice visited elemnts, we restrict only visiting immdeiate predecessors
      LinkedList *temp = adjacent->Listnode->predecessors;
      if (adjacent->Listnode->predecessors == nullptr)//formation of predecessor list
      {
        adjacent->Listnode->predecessors = new LinkedList(startnode);
        adjacent->Listnode->tailpredecessor = adjacent->Listnode->predecessors;
      }
      else
      {
        adjacent->Listnode->tailpredecessor->next = new LinkedList(startnode);
        adjacent->Listnode->tailpredecessor->next->prev = adjacent->Listnode->tailpredecessor;
        adjacent->Listnode->tailpredecessor = adjacent->Listnode->tailpredecessor->next;
      }
      modifiedRecursiveDFS(adjacent->Listnode);
      adjacent->Listnode->visited++;//here we increment visited to create a distinction bw visited twice and cycle
      LinkedList* tailbacktrack;
      if (startnode->backtrack == nullptr)//formation of backtrack
      {
        startnode->backtrack = new LinkedList(adjacent->Listnode);
        startnode->tailbacktrack = startnode->backtrack;
      }
      else
      {
        startnode->tailbacktrack->next = new LinkedList(adjacent->Listnode);
        startnode->tailbacktrack->next->prev = startnode->tailbacktrack;
        startnode->tailbacktrack = startnode->tailbacktrack->next;
      }
    }
    adjacent = adjacent->next;
  }
}

int Graph::calculateOnevisits()
{
  int count = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 1)
    {
      count++;
    }
  }
  return count;
}
int Graph::calculatecycle()
{
  int count = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 2)//cycle has visited 2 whereas visited twice has values 2 and 3, we created this distinction 
    {
      count++;
    }
  }
  return count;
}
void Graph::printResults()
{
  
  cout << "No. of connected components:" << countTrees << endl;
  int onevisit = calculateOnevisits();
  cout << "No. of nodes visited once:" << onevisit << endl;
  cout << "No. of nodes visited twice:" << numNodes - onevisit << endl;
  cout<<"No. of nodes that are present in a cycle:"<<calculatecycle()<<endl;
  for(int i = 0;i<countTrees;i++){
    DFStree[i]->printBST("",false);
  }

  return;
}

void BST::insert(int value)
{

  Node *nodeToInsert = new Node(value); // stores the new node to be inserted
  Node *temp = root;                    // initialize temp as root of the tree

  Node *prev = NULL; // stores the prvious temp

  while (temp != NULL) // loop for finding location for insertion
  {
    prev = temp;
    if (value < temp->value)
      temp = temp->left;
    else
      temp = temp->right;
  }

  // If the root is NULL i.e the tree is empty
  // The new node is the root node
  if (prev == NULL)
  {
    root = nodeToInsert;
    return;
  }

  // If the new key is less than the leaf node key
  // Assign the new node to be its left child
  else if (value < prev->value)
  {
    prev->left = nodeToInsert;
    prev->left->parent = prev;
  }
  // else assign the new node its right child
  else
  {
    prev->right = nodeToInsert;
    prev->right->parent = prev;
  }
  numElems++;
  return;
}

void BST::printBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->value << endl;
    Node *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

#endif
