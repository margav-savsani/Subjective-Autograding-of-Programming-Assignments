#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
// A graph can have as many connected components.
void Graph::modifiedDFS() {
  bool* visited1 = new bool[numNodes];
  bool* visited2 = new bool [numNodes];
  for (int v = 0; v < numNodes; v++)
  {
    visited1 [nodes[v].value] = false;
    visited2 [nodes[v].value] = false;
  }
  
  for (int v = 0; v < numNodes; v++)
  {
      
    if (visited1[nodes[v].value] == false )
    {
          // print all reachable vertices
          // from v
      
      DFS(nodes[v], visited1 ,visited2);
      //connect counts the no of connected components.
      connect ++;
      cout << "\n";
    }
  }
  //The no of nodes which are visited twice will give the total number of cycles presents in it.
  for(int v=0; v<numNodes; v++){
    if(visited2[nodes[v].value] == true)
    {
      NoOfCycles++;
    }
  }

  delete[] visited1;
  delete[] visited2;

   
  return;
}
void Graph::DFS(Node node, bool visited1[], bool visited2[])
{
  // Mark the current node as visited and print it
  // creating a BST to insert all the values of the nodes.
  BST tree;
  int value =node.value;
  if(visited1[value] != true){
    visited1[value] = true;
  }
  else{ 
    visited2[value] == true;
  }
  cout << value << " ";

  // Recur for all the vertices
  // adjacent to this vertex
  list<int> adjacentsnodes = adj.at(node.value);
  list<int > :: iterator i;
  for (i = adjacentsnodes.begin(); i != adjacentsnodes.end(); ++i){
    if (!visited2[*i]){
      tree.insert(*i);
      DFS(*i, visited1 , visited2);
    }
  }
  bst[connect]= tree;
}
void Graph::printResults() {
  cout<< "No. Of Connected Components"<< connect <<endl;
  cout<<"No. Of Cycles"<< NoOfCycles<<endl;
  cout<<"No. Of Nodes Visited Once"<<NoOfCycles<< endl;
  cout<<"No. Of Nodes Visited Twice"<<numNodes-NoOfCycles<<endl;
  for (int i = 0; i< connect; i++){
    bst[i].printPreorder(bst[i].root);
  }

  return;
}

#endif
