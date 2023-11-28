#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  // static bool statringConnected = true;
  //bool tempb = true;
  static int rec_level = 0;
  static int visit = 0;
  static int firstorsecond = 1;
  if (rec_level == 0){
    for (int x=0; x<numNodes; x++){
      if (visitedArr1[x] == 0){
        cout << "start: " << x+1 << endl;
        rec_level++;
        visit = x;
        modifiedDFS();
      }
    }
  }
  else{
    int temp = visit;
    if(firstorsecond == 1) visitedArr1[temp] = 1;
    else if(firstorsecond == 2) visitedArr2[temp] = 1;
    cout << temp+1<< endl;
    for(int i=0; i<nodes[temp].numAdj; i++){
      // statringConnected = false;
      int next = nodes[temp].adjInd[i];
      if(visitedArr1[next] == 0 ){
        firstorsecond = 1;
        parentInd[next] = temp;
        visit = next;
        rec_level++;
        modifiedDFS();
      }
      else if(visitedArr1[next] == 1 && visitedArr2[next] == 0 ){
        if (parentInd[temp] != next){
          firstorsecond = 2;
          visit = next;
          rec_level++;
          modifiedDFS();
        }
      }
    }
  }
  
  rec_level--;
  return;
}

void Graph::printResults() {
  for (int i=0; i<numNodes; i++){
    cout << i+1 << ": ";
    for (int j=0; j<nodes[i].numAdj; j++){
      cout << nodes[nodes[i].adjInd[j]].value << ", ";
    }
    cout << endl;
  }
  return;
}

#endif
