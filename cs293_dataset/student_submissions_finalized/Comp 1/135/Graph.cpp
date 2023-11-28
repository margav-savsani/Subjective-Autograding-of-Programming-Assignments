#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::modDFS(int k){
  static BST myBST;
  static int reccursionlvl = 0;
  if(nodes[k].timesVisited<2){
    myBST.insert(nodes[k].value);
    // cout << "-->" << nodes[k].value << " ";
    nodes[k].timesVisited++;
    for(int i=0; i<nodes[k].numEdges(); i++){
      reccursionlvl++;
      string edge = to_string(k+1)+" "+to_string(nodes[k].adjecencyList[i]);
      if(edges[edge] == 0){
        edges[edge] = 1;
        modDFS(nodes[k].adjecencyList[i]);
      }
      reccursionlvl--;
    }
  }
  if(reccursionlvl == 0){
    // cout << k << "\n";
    cout << "BST for connected component " << nComponents << ":\n";
    myBST.printBST();
    myBST = *(new BST);
  }
  // cout << "\n";
  return;
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i=numNodes-1; i>=0; i--){
    if(nodes[i].timesVisited == 0){
      nComponents++;
      // cout << "Component no. " << nComponents << ": for " << i << "\n";
      modDFS(i);
    }
  }
  // modDFS(2);
  return;
}

void Graph::printResults() {
  cout << "No. of connected components: " << nComponents << "\n";
  int n=0;
  for(int i=0; i<numNodes; i++){
    if(nodes[i].timesVisited == 1) n++;
  }
  cout << "No. of nodes visited once: " << n << "\n";
  n=0;
  for(int i=0; i<numNodes; i++){
    if(nodes[i].timesVisited == 2) n++;
  }
  cout << "No. of nodes visited twice: " << n << "\n";
  cout << "No. of nodes that are present in a cycle: " << n << "\n";
  return;
}

#endif
