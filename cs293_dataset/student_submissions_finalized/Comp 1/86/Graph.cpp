#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
int count = 1;

BST *Graph::DFS(Node *v, BST *tree, Node *u)
{
  v->color = 1;
  v->visit = v->visit + 1;
  listOfObjects<Node *> *temp = v->adj_lists;
  
  if(u != nullptr)
  {
    while(temp != nullptr)
    {
      if(v->adj_lists->object == u)
      {
        v->adj_lists = temp->next;
        if(temp->next != nullptr) v->adj_lists->prev = nullptr;
        break;
      }
      if(temp->object == u)
      {
        temp->prev->next = temp->next;
        if(temp->next != nullptr) temp->next->prev = temp->prev;
        break;
      }
      temp = temp->next;
    }
  }
  listOfObjects<Node *> *store = v->adj_lists;
  tree->insert(v->value);

  while(store != nullptr)
  {
    if(store->object->visit < 1)
    {
      DFS(store->object, tree, v);
    }
    else if(store->object->visit < 2)
    {
      if(store->object->color == 1)
      {
        inCycle[store->object->value - 1] = true;
      }
      DFS(store->object,tree, v);
    }
    store = store->next;
  }
  v->color = 2;
  return tree;
}

void Graph::modifiedDFS()
{
  int k = 0;
  while(k < numNodes)
  {
    BST *Tree = new BST();
    Tree = DFS(&nodes[k], Tree, nullptr);
    AllTrees[count - 1] = *Tree;
    //Tree->printBST("", left);
    int i;
    for(i = k + 1; i < numNodes; i++)
    {
      if(nodes[i].visit == 0)
      {
        k = i;
        count++;
        break;
      }
    }
    if(i == numNodes)
    {
      return;
    }
  }
  return;
}

void Graph::printResults()
{
  cout<<"No. of connected components: "<<count<<endl;
  int vis1 = 0, vis2 = 0;
  for(int i = 0; i < numNodes; i++)
  {
    if(nodes[i].visit == 1)
    {
      vis1++;
    }
    else if(nodes[i].visit == 2)
    {
      vis2++;
    }
  }

  cout<<"No. of nodes visited once: "<<vis1<<endl;
  cout<<"No. of nodes visited twice: "<<vis2<<endl;
  cout<<"No. of nodes that are present in a cycle: ";
  for(int i =0; i < numNodes;i++)
  {
    Graph *B = this;
    BST *Tree = new BST();
    DFS(&B->nodes[i],Tree,nullptr);
    for(int j=0; j < numNodes; j++)
    {
      if(B->inCycle[j])
      {
        inCycle[j] = true;
      }
    }
  }
  int nodesincycle = 0;
  for(int i = 0; i < numNodes; i++)
  {
    if(inCycle[i])
    {
      nodesincycle++;
    }
  }
  cout<<nodesincycle<<endl;
  for(int i = 0; i < count; i++)
  {
    AllTrees[i].printBST("", false);
  }
  return;
}

#endif
