#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
int Graph::DFS(int init, BST *tree, int parent, int timestamp)
{
  static int recursionlevel = 0;
  recursionlevel++;
  static int *visits;
  timestamp++;
  if (recursionlevel == 1)
  {
    visits = new int[numNodes];
    for (int i = 0; i < numNodes; i++)
    {
      visits[i] = 0;
    }
  }

  listOfObjects<Node *> *list = nodes[init].adjacencylist;
  visits[init] += 1;
  while (list != nullptr)
  {
    int index = list->object->value - 1;
    int v = visits[index];
    if (v != 2 && index != parent)
    {
      if (v == 0)
      {
        nodes[index].arr[0] = timestamp;
        tree->insert(list->object->value);
        nodes[index].visit++;
        timestamp = DFS(index, tree, init, timestamp);
      }
      else
      {
        int pats1 = nodes[init].arr[0];
        int cats1 = nodes[index].arr[0];
        if (pats1 > cats1)
        {
          if (pats1 - cats1 != 1)
          {
            nodes[index].arr[1] = timestamp;
            tree->insert(list->object->value);
            nodes[index].visit++;
            timestamp = DFS(index, tree, init, timestamp);
          }
        }
        else
        {
          if (nodes[index].dep[0] != 0)
          {
            if (nodes[init].value == 1)
            {
              nodes[index].arr[1] = timestamp;
              tree->insert(list->object->value);
              nodes[index].visit++;
              timestamp = DFS(index, tree, init, timestamp);
            }
          }
          else
          {
            nodes[index].arr[1] = timestamp;
            tree->insert(list->object->value);
            nodes[index].visit++;
            timestamp = DFS(index, tree, init, timestamp);
          }
        }
      }
    }
    list = list->next;
  }
  nodes[init].visit--;
  if (recursionlevel == 1)
  {
    for (int i = 0; i < numNodes; i++)
    {
      if (visits[i] == 0)
      {
        continue;
      }
      nodes[i].visit = visits[i];
    }
  }
  if (visits[init] == 1)
  {
    nodes[init].dep[0] = timestamp;
    timestamp++;
  }
  else
  {
    nodes[init].dep[1] = timestamp;
    timestamp++;
  }

  recursionlevel--;
  return timestamp;
  // update visit in each node when ending 1st call
}

void Graph::modifiedDFS()
{
  for (int i = 0; i < numNodes; i++)
  {
    int timestamp = 1;
    if (nodes[i].visit == 0)
    {
      BSTNode *n = new BSTNode(nodes[i].value);
      BST *tree = new BST(n);
      if (Trees == nullptr)
      {
        Trees = new listOfObjects<BST *>(tree);
        nodes[i].arr[0] = timestamp;
        nodes[i].visit++;
        DFS(i, Trees->object, -1, timestamp);
      }
      else
      {
        listOfObjects<BST *> *temp = Trees;
        while (temp->next != nullptr)
        {
          temp = temp->next;
        }
        temp->next = new listOfObjects<BST *>(tree);
        temp = temp->next;
        nodes[i].arr[0] = timestamp;
        nodes[i].visit++;
        DFS(i, temp->object, -1, timestamp);
      }
    }
  }
}

void Graph::printResults()
{
  int connectedcomps = 0;
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].visit == 1)
    {
      v1++;
    }
    if (nodes[i].visit == 2)
    {
      v2++;
    }
  }
  listOfObjects<BST *> *tre = Trees;
  while (tre != nullptr)
  {
    connectedcomps++;
    tre = tre->next;
  }
  tre = Trees;

  cout << "No. of connected components: " << connectedcomps << endl;
  cout << "No. of nodes visited once: " << v1 << endl;
  cout << "No. of nodes visited twice: " << v2 << endl;
  cout << "No. of nodes that are present in a cycle: " << v2 << endl;
  while (tre != nullptr)
  {
    cout << "BST\n";
    tre->object->printBST("");
    cout << "\n";
    tre = tre->next;
  }
  return;
}

#endif
