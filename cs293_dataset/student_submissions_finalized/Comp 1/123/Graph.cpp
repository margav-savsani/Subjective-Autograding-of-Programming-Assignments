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
  trees = nullptr;
  count = 0;

  for (int i = 0; i < numNodes; i++)
  {
    // Atleast one visit per node
    if (visits[i] == 0)
    {
      BST *tree = new BST(); // Making a tree to add nodes
      // Adding tree to list of trees obtained
      if (trees == nullptr)
      {
        trees = new listOfObjects<BST *>(tree);
      }
      else
      {
        listOfObjects<BST *> *it = trees;
        while (it->next != nullptr)
        {
          it = it->next;
        }
        listOfObjects<BST *> *treer = new listOfObjects<BST *>(tree);
        it->next = treer;
        treer->prev = it;
      }
      Node p_node;
      // Calling other DFS
      DFS(nodes[i], tree, p_node);
      // Count which maintains no. of connected components
      count++;
    }
  }
}

void Graph::printResults()
{
  cout << "No. of connected components: " << count << endl;
  int vis1 = 0;  // No. of nodes visited once
  int vis2 = 0;  // No. of nodes visited twice
  int cyclu = 0; // No. of nodes in a cycle
  for (int i = 0; i < numNodes; i++)
  {
    if (visits[i] == 1)
    {
      vis1++;
    }
    else if (visits[i] == 2)
    {
      vis2++;
    }
    else
    {
      cout << "Something fishy" << endl;
    }
    if (cycle[i])
    {
      cyclu++;
    }
  }
  cout << "No. of nodes visited once: " << vis1 << endl;
  cout << "No. of nodes visited twice: " << vis2 << endl;
  // cout << sizeof(cycle) / sizeof(bool) << endl;
  if (cyclu != 0 && cyclu != numNodes)
  {
    cout << "No. of nodes that are present in a cycle: " << cyclu + 1 << endl;
  }
  else
  {
    cout << "No. of nodes that are present in a cycle: " << cyclu << endl;
  }
  // Printing trees
  listOfObjects<BST *> *it = trees;
  while (it != nullptr)
  {
    cout << "Tree" << endl;
    it->object->printBST(" ", false);
    it = it->next;
  }
}
bool Graph::DFS(Node node, BST *tree, Node p_node)
{
  // Updating visits array
  visits[node.value - 1]++;
  tree->insert(node); // Insert node into tree
  for (int i = 0; i < numNodes; i++)
  {
    // Making sure that parent node is not visited twice
    if (i != p_node.value - 1)
    {
      if (visits[i] < 2 && node.neighbours[i] != 0)
      {
        bool val = DFS(nodes[i], tree, node);
        if (!cycle[i])
        {
          cycle[i] = val; // Updating the cycle array when path encounter previously encountered node
        }
      }
      else
      {
        if (nodes[i].value != p_node.value && node.neighbours[i] != 0)
        {
          cycle[i] = true;
        }
      }
    }
  }
  return cycle[node.value - 1];
}
#endif
