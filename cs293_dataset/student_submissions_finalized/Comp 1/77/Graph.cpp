#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
using namespace std;
// BST functions:
BST::BST()
{
  root = NULL;
}
BST::BST(TreeNode *root1)
{
  root = root1;
}
// To insert into BST
TreeNode *BST::insert(TreeNode *root, int data)
{
  if (root == NULL)
  {
    root = new TreeNode(data);
    return root;
  }
  if (data <= root->data)
  {
    root->left = insert(root->left, data);
  }
  else
  {
    root->right = insert(root->right, data);
  }
  return root;
}
// Used from lab 3
void BST::printBST(const string &prefix, bool isLeft = false)
{
  if (root != NULL)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->data << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}
void Graph::DFS2(BST *b, int u, int p)
{
  // If node is already visited twice it will return
  if (vis[u - 1] == 2)
  {
    return;
  }
  // If node is visited once already
  else if (vis[u - 1] == 1)
  {
    // Assign visited as 2
    vis[u - 1] = 2;
    // Inserts node into BST
    b->root = b->insert(b->root, u);
    for (int i = 1; i < nodes[u - 1].adjacent.size(); i++)
    {
      if (nodes[u - 1].adjacent[i] == par[u - 1])
      {
        continue;
      }
      DFS2(b, nodes[u - 1].adjacent[i], u);
    }
    return;
  }
  // If node is not visited that is first time
  else
  {
    // Assign parent to node
    par[u - 1] = p;
    // Assign visited as 1
    vis[u - 1] = 1;
    // Inserts node into BST
    b->root = b->insert(b->root, u);
    for (int i = 1; i < nodes[u - 1].adjacent.size(); i++)
    {
      if (nodes[u - 1].adjacent[i] == u)
      {
        continue;
      }
      if (nodes[u - 1].adjacent[i] == par[u - 1])
      {
        continue;
      }
      DFS2(b, nodes[u - 1].adjacent[i], u);
    }
  }
}

void Graph::modifiedDFS()
{
  for (int i = 0; i < numNodes; i++)
  {
    vis[i] = 0;
  }
  // While loop is to check all not covered (disconnected) sub graphs
  int j = 0;
  while (j < numNodes)
  {
    if (vis[j] == 0)
    {
      trees2.push_back(new BST());
      BST *b = new BST();
      DFS2(b, j + 1, par[j]);
      trees2[trees2.size() - 1]->root = b->root;
    }
    j++;
  }
  return;
}

void Graph::printResults()
{
  // Calculation of number of nodes in the cycle:
  int cycle_nodes[numNodes];
  for (int i = 0; i < numNodes; i++)
  {
    cycle_nodes[i] = nodes[i].adjacent.size() - 1;
  }
  bool a = false;
  while (true)
  {
    if (a)
    {
      break;
    }
    a = false;
    for (int i = 0; i < numNodes; i++)
    {
      if (cycle_nodes[i] == 0)
      {
        if (i + 1 == numNodes)
        {
          a = true;
        }
        continue;
      }
      if (cycle_nodes[i] == 1)
      {
        for (int j = 1; j < nodes[i].adjacent.size(); j++)
        {
          cycle_nodes[nodes[i].adjacent[j] - 1]--;
        }
        cycle_nodes[i] = 0;
        if (i + 1 == numNodes)
        {
          a = true;
        }
        break;
      }
      if (i + 1 == numNodes)
      {
        a = true;
      }
    }
  }
  int nodes_in_cycle = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (cycle_nodes[i] > 0)
    {
      nodes_in_cycle++;
    }
  }
  // Printing all required contents:
  cout << "No. of connected components:" << trees2.size() - 1 << endl;
  int visited_twice = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (vis[i] == 2)
    {
      visited_twice++;
    }
  }
  cout << "No. of nodes visited once: " << numNodes - visited_twice << endl;
  cout << "No. of nodes visited twice: " << visited_twice << endl;
  cout << "No. of nodes that are present in a cycle: " << nodes_in_cycle << endl;
  cout << "BSTs: " << endl;
  for (int i = 1; i < trees2.size(); i++)
  {
    trees2[i]->printBST("");
    cout << "              " << endl;
  }
  return;
}

#endif
