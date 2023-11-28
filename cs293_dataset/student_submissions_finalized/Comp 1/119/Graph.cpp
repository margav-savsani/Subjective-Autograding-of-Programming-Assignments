#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// -------------------------- BST insert and print --------------------------

void BST::insert(Node *v)
{
  if (v == NULL)
    return;
  if (root == NULL)
  {
    root = v;
    return;
  }

  // all nodes to be inserted will be unique, so no need to check for repetition
  Node *x = root;
  while (true)
  {
    if (x->value < v->value)
    {
      if (x->BSTright != NULL)
        x = x->BSTright;
      else
      {
        x->BSTright = v;
        break;
      }
    }
    else
    {
      if (x->BSTleft != NULL)
        x = x->BSTleft;
      else
      {
        x->BSTleft = v;
        break;
      }
    }
  }
}

void BST::printBST(Node *v, const string &prefix, bool isLeft)
{
  if (v != nullptr)
  {
    cout << prefix;
    cout << (isLeft ? "|--" : "|__");

    cout << v->value << endl;
    printBST(v->BSTleft, prefix + (isLeft ? "│   " : "    "), true);
    printBST(v->BSTright, prefix + (isLeft ? "│   " : "    "), false);
  }
  else
  {
    // cout << "NULL" << endl;
  }
}

// -------------------------- GRAPH dfs and finalPrint --------------------------

void Graph::modifiedDFS()
{

  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visits == 0)
    {
      BST *tree = new BST;
      connectedCompDFS(&nodes[i], NULL, tree);

      linkedListNode<BST *> *x = new linkedListNode<BST *>;
      x->value = tree;
      BSTtrees.insert(x);
    }
  }
}

bool checkPathAncestor(Node *u, Node *v)
{
  // check if u is ancestor of v
  Node *t = v->previous;

  while (t != NULL)
  {
    if (t == u)
      return 1;
    t = t->previous;
  }

  return 0;
}

void Graph::connectedCompDFS(Node *v, Node *p, BST *tree)
{
  if (v == NULL)
    return;

  v->visits++;
  v->previous = p;

  // cout << v->value << endl;
  tree->insert(v);

  linkedListNode<int> *temp_pointer = v->adjNodeIndexes.head;
  while (temp_pointer != NULL)
  {
    Node *u = &nodes[temp_pointer->value];
    if (u != p)
      if (u->visits < 2)
      {
        if (checkPathAncestor(u, v))
        {
          connectedCompDFS(u, u->previous, tree);
        }
        else
        {
          connectedCompDFS(u, v, tree);
        }
      }
    temp_pointer = temp_pointer->next;
  }
}

void Graph::printResults()
{
  linkedListNode<BST *> *temp = BSTtrees.head;

  while (temp != NULL)
  {
    temp->value->printBST(temp->value->root, "", 0);
    cout << "-------------------------------------------" << endl;
    temp = temp->next;
  }
}

#endif
