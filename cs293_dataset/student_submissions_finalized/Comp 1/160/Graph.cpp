#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
bool BST::insert(int value)
{
  // Adding the first node
  if (root == NULL)
  {
    root = new TreeNode(value);
    return true;
  }
  // Checking if similar node already exists
  TreeNode *curr = root;
  while (true)
  {
    // incrementing Size of subtree which is rooted at this node
    // Moving to the right, if price is greater
    if (value > curr->value)
    {
      if (curr->right != NULL)
      {
        curr = curr->right;
      }
      else
      {
        curr->right = new TreeNode(value);
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
        curr->left = new TreeNode(value);
        break;
      }
    }
  }
  return true;
}

void BST::printBST(const string &prefix, bool isLeft)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << '(' << root->value << ')' << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}
// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visitcount == 0)
    {
      if (start == nullptr)
      {
        start = new connected();
        end = start;
      }
      else
      {
        connected *tail = new connected();
        end->next = tail;
        end = tail;
      }
      cycle(i + 1, 0);
      DFS(i + 1, end->tree, i + 1);
    }
  }

  return;
}
// implementing DFS using previous node while traversing
void Graph::DFS(int vertex, BST *tree, int prev)
{
  if (nodes[vertex - 1].visitcount < 2)
  {
    nodes[vertex - 1].visitcount++;
    tree->insert(vertex);
    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[vertex - 1].adjacency[i] == 1 && i + 1 != prev && nodes[i].path[vertex - 1] != 1)
      {
        nodes[vertex - 1].path[i] = 1;
        DFS(i + 1, tree, vertex);
      }
    }
  }
  return;
}
// find the cycle using DFS and updating present_cycle correspondingly
void Graph::cycle(int vertex, int prev_vertex)
{
  if (nodes[vertex - 1].colour == 2)
  {
    return;
  }
  if (nodes[vertex - 1].colour == 1)
  {
    int cur = prev_vertex;
    nodes[cur - 1].present_cycle = 1;
    while (cur != vertex)
    {
      cur = nodes[cur - 1].previous;
      nodes[cur - 1].present_cycle = 1;
    }
    return;
  }
  nodes[vertex - 1].previous = prev_vertex;
  nodes[vertex - 1].colour = 1;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[vertex - 1].adjacency[i] == 1 && nodes[vertex - 1].previous != (i + 1))
    {
      cycle(i + 1, vertex);
    }
  }
  nodes[vertex - 1].colour = 2;
}

void Graph::printResults()
{
  cout << " BST that has been generated for each component:" << endl;
  connected *Tree = start;
  while (Tree != NULL)
  {
    connected_component++;
    cout << "Component - " << connected_component << " :" << endl;
    Tree->tree->printBST("");
    cout << endl;
    Tree = Tree->next;
  }
  cout << "Total Number Of Components : " << connected_component << endl;
  int x = 0, y = 0, z = 0;
  // cycle(1, 0);
  for (int k = 0; k < numNodes; k++)
  {
    if (nodes[k].visitcount == 2)
      x++;
    if (nodes[k].present_cycle)
      z++;
    if (nodes[k].visitcount == 1)
      y++;
  }
  cout << "Number of nodes visited twice : " << x << endl;
  cout << "Number of nodes visited once : " << y << endl;
  cout << "Number of nodes which are present in atleast one cycle : " << z << endl;
  return;
}

#endif
