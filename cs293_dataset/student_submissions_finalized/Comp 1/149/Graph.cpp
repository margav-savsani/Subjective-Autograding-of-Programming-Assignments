#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

int ti = 0;

/// @brief insert function for the BST.. usual one... comaparing and inserting
/// @param p node on which the new node might be inserted
/// @param t new node to be inserted
void addNode(Node *p, Node *t)
{
  if (p->value >= t->value && p->left == nullptr)
  {
    p->left = new Node(t->value);
    p->left->parent = p;
  }
  else if (p->value >= t->value && p->left != nullptr)
  {
    addNode(p->left, t);
  }
  else if (p->value < t->value && p->right == nullptr)
  {
    p->right = new Node(t->value);
    p->right->parent = p;
  }
  else if (p->value < t->value && p->right != nullptr)
  {
    addNode(p->right, t);
  }
}

void Graph::DFS(Node *n, Node *root)
{
  if (n->visited == 0)
  {
    ti++;
    n->time = ti;
  }
  n->visited++;
  listOfObjects<Node *> *currnode = n->adjacency;
  while (currnode != nullptr)
  {
    // check for the cycles in the node.. if a backedge is encounterd, travel the parents till we reach the node and make the cycle true for all the elements till there.
    if (currnode->object->visited > 0 && n->time > currnode->object->time && n->pred != currnode->object)
    {
      Node *c = n;
      while (c != currnode->object && c != nullptr)
      {
        c->cycle = true;
        c = c->pred;
      }
      currnode->object->cycle = true;
    }
    // call DFS and also attach the parent
    if (currnode->object->visited == 0 && n->pred != currnode->object)
    {
      if (currnode->object->pred == nullptr)
        currnode->object->pred = n;
      addNode(root, currnode->object);
      DFS(currnode->object, root);
    }
    // simply call the DFS
    else if (currnode->object->visited == 1 && n->pred != currnode->object)
    {
      addNode(root, currnode->object);
      DFS(currnode->object, root);
    }
    currnode = currnode->next;
  }
}

void Graph::modifiedDFS()
{
  B = new BST(&nodes[0]);
  components++;
  DFS(&nodes[0], B->root);
  BST *currnode = B;
  for (int i = 1; i < numNodes; i++)
  {
    /// calling DFS if aany of the node remains unvisited
    if (nodes[i].visited == 0)
    {
      components++;
      currnode->next = new BST(&nodes[i]);

      DFS(&nodes[i], currnode->next->root);
      currnode = currnode->next;
    }
  }
  return;
}

void Graph::printResults()
{
  cout << "Connected Components: " << components << endl;
  int once = 0, twice = 0, cycle = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 1)
      once++;
    else if (nodes[i].visited == 2)
      twice++;
    if (nodes[i].cycle)
    {
      cycle++;
    }
  }
  cout << "Number of nodes visited once: " << once << endl;
  cout << "Number of nodes visited twice: " << twice << endl;
  cout << "Number of nodes in a cycle: " << cycle << endl;
  int i = 0;
  while (B != nullptr)
  {
    cout << "Connected Component " << i + 1 << endl;
    B->printBST("");
    B = B->next;
    i++;
  }
  return;
}

#endif
