#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
// Add code as appropriate for your implementation
bool find_obj(listOfObjects<Edge> *edgelist, Edge e){
  listOfObjects<Edge> *ptr = edgelist;
  while(ptr != nullptr){
    if(ptr->object.isEqual(e)){
      return true;
    }
    ptr = ptr->next;
  }
  return false;
}

void Graph::DFS(Node v, Node pv, BST *T, listOfObjects<Edge> *edgeList)
{
  cout << v.value << " " << pv.value << endl;
  listOfObjects<Node> *ptr = v.getAdjNodes();
  Edge e = Edge(v, pv);
  if(edgeList == nullptr){
    edgeList = new listOfObjects<Edge>(e);
  }
  else{
  edgeList->insert(e);
  }
  visited_times[v.value - 1] = visited_times[v.value - 1] + 1;
  T->insert(v.value);
  while (ptr != nullptr)
  {
    Node w = ptr->object;
    // cout << "hi" << endl;
    if (w.value != pv.value)
    {
      if (visited_times[w.value - 1] < 2)
      {
        for (int i = 0; i < numNodes; i++)
        {
          if (nodes[i].value == w.value)
          {
            w = nodes[i];
            break;
          }
        }
        DFS(w, v, T, edgeList);
      }
    }
    ptr = ptr->next;
  }
  // cout << "DFS End" << endl;
  return;
}

void Graph::modifiedDFS()
{
  Node n = Node(-1);
  for (int i = 0; i < numNodes; i++)
  {
    if (visited_times[i] == 0)
    {
      numComponents++;
      BST *T = new BST();
      listOfObjects<Edge> *edgeList = new listOfObjects<Edge>();
      DFS(nodes[i], n, T, edgeList);
      cout<<"Component BST: "<<endl;
      T->printBST("");
      while(edgeList != nullptr){
        if(find_obj(edgeList->next, edgeList->object)){
          numCycles++;
        }
        edgeList = edgeList->next;
      }
    }
  }

  return;
}

void Graph::printResults()
{
  cout << "No of Components :" << numComponents << endl;
  int visited_once = 0;
  int visited_twice = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (visited_times[i] == 1)
      visited_once++;
    else if (visited_times[i] == 2)
      visited_twice++;
  }
  cout << "No of Nodes Visited Once: " << visited_once << endl;
  cout << "No of Nodes Visited Twice: " << visited_twice << endl;
  cout<<"No of Nodes in a Cycle: " << numCycles << endl;
  return;
}

#endif
