#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::DFS(int v, int c, BST *tree) // auxillary DFS function to implement modified DFS
{

  component[v] = c;
  if (count_visited[v] == 0)
  {
    arrtime[v] = counter; // Updating the arrival times
    counter++;
  }
  count_visited[v]++;
  tree->insert(v + 1); // inserting the value in BST

  for (int i = 0; i < (nodes[v].a).size(); i++)
  {
    if (count_visited[nodes[v].a[i]->value - 1] == 0)
    {
      parents[nodes[v].a[i]->value - 1] = v;
      nodes[v].a[i]->parent = v;
      if (parents[v] != nodes[v].a[i]->value - 1)
        DFS(nodes[v].a[i]->value - 1, c, tree); // calling DFS again
    }
    else if (count_visited[nodes[v].a[i]->value - 1] == 1)
    {

      if ((arrtime[nodes[v].a[i]->value - 1] < arrtime[v]) && parents[v] != nodes[v].a[i]->value - 1) // if is ancestor but not parent
      {
        Node curr = nodes[v];
        incycle[curr.value - 1] = true;
        while (curr.value != nodes[v].a[i]->value) // updating in the cycle
        {
          incycle[curr.value - 1] = true;
          if (curr.parent == -1)
            break;

          curr = nodes[curr.parent];
        }
        incycle[curr.value - 1] = true;
      }
      if (parents[v] != nodes[v].a[i]->value - 1)
        DFS(nodes[v].a[i]->value - 1, c, tree);
    }
    else // visited twice
    {
      if ((arrtime[nodes[v].a[i]->value - 1] < arrtime[v]) && parents[v] != nodes[v].a[i]->value - 1) // if is ancestor but not parent
      {
        Node curr = nodes[v];
        incycle[curr.value - 1] = true;
        while (curr.value != nodes[v].a[i]->value) // updating in the cycle
        {
          incycle[curr.value - 1] = true;
          if (curr.parent == -1)
            break;

          curr = nodes[curr.parent];
        }
        incycle[curr.value - 1] = true;
      }
    }
  }
}
void Graph::modifiedDFS()
{
  static int currIndex = 0; // index where next DFS is to be called
  static int a = 1;         // component number
  BST *treep = new BST();   // tree pointer
  trees.push_back(treep);   // adding in the tree lists
  DFS(currIndex, a, treep);
  a++;
  currIndex++;
  for (int i = currIndex; i < numNodes; i++)
  {
    if (component[i] == 0)
    {
      currIndex = i;
      modifiedDFS(); // calling it again
      break;
    }
  }

  return;
}

void Graph::printResults()
{
  {
    cout << "No of connected components: " << trees.size() << endl;
    int count1 = 0, count2 = 0, count3 = 0;
    for (int i = 0; i < numNodes; i++)
    {
      if (incycle[i])
        count3++;
      if (count_visited[i] == 1)
        count1++;
      else if (count_visited[i] == 2)
        count2++;
    }

    cout << "No. of nodes visited once: " << count1 << endl;
    cout << "No. of nodes visited twice: " << count2 << endl;
    cout << "No. of nodes that are present in a cycle: " << count3 << endl;
    for (int i = 0; i < trees.size(); i++)
    {
      cout << "This is the tree number " << i + 1 << endl;
      trees[i]->printBST("");
      cout << endl;
    }
  }
}

#endif
