#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;

// Add code as appropriate for your implementation

void BST::insert(int value)
{
  // Adding the first node
  if (root == NULL)
  {
    root = new TreeNode(value, NULL, NULL, NULL);
    return;
  }

  TreeNode *curr = root;
  while (true)
  {
    // Moving to the right, if price is greater
    if (value > curr->value)
    {
      if (curr->right != NULL)
      {
        curr = curr->right;
      }
      else
      {
        curr->right = new TreeNode(value, NULL, NULL, curr);
        break;
      }
    }
    else
    {
      // moving to left if its smaller
      if (curr->left != NULL)
      {
        curr = curr->left;
      }
      else
      {
        curr->left = new TreeNode(value, NULL, NULL, curr);
        break;
      }
    }
  }
}

void BST::printBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->value << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void Graph::modifiedDFS()
{
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 0)
    {
      // cout << "Starting New BST:" << endl;
      DFS(i, nodes);
      connected++;
    }
  }
  return;
}

void Graph::printResults()
{
  cout << "No. of connected components: " << connected << endl;

  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 1)
    {
      // cout << i + 1 << " ";
      once++;
    }
  }
  cout << "No. of nodes visited once: "<<once;


  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visited == 2)
    {
      twice++;
      // cout << i + 1 << " ";
    }
  }
    cout << endl
       << "No. of nodes visited twice: "<<twice;

  for (int i = 0; i < numNodes; i++)
  {
    if (cyclic[i] == 1)
    {
      nodes[i].cycle == 1;
      cyclicNodes++;
    }
  }

  cout << endl
       << "No. of nodes that are present in a cycle: " << cyclicNodes;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].cycle)
    {
      // cout << i + 1;
    }
  }

  cout << "\nEach BST that has been generated - " << endl;
  for (int i = 0; i < numNodes; i++)
  {
    if (Trees[i].root)
    {
      Trees[i].printBST("", true);
      cout << "\n\n\n";
    }
  }

  return;
}

void Graph::DFS(int c, Node *nodes)
{
  nodes[c].visited++;
  Trees[connected].insert(c + 1);

  // cout << nodes[c].value << endl;

  for (int i = 0; i < nodes[c].neighbours; i++)
  {

    if (nodes[c].parent1 != nodes[c].adjacent[i]->value - 1 and nodes[c].parent2 != nodes[c].adjacent[i]->value - 1)
    {

      if (nodes[c].adjacent[i]->visited != 2)
      {
        if (nodes[c].adjacent[i]->parent1 == -1)
        {
          nodes[c].adjacent[i]->parent1 = c;
        }
        else if (nodes[c].adjacent[i]->parent2 == -1 and nodes[c].adjacent[i]->parent1 != c)
        {
          nodes[c].adjacent[i]->parent2 = c;
        }
        presentStack[sizeStack] = nodes[c];
        sizeStack++;
        DFS(nodes[c].adjacent[i]->value - 1, nodes);
      }
    }
  }

  for (int i = 0; i < sizeStack; i++)
  {
    countStack[presentStack[i].value - 1]++;
  }

  for (int i = 0; i < numNodes; i++)
  {
    if (countStack[i] >= 2)
    {
      cyclic[i] = 1;
    }
  }

  for (int i = 0; i < numNodes; i++)
  {
    countStack[i] = 0;
  }
  sizeStack--;
  return;
}

#endif
