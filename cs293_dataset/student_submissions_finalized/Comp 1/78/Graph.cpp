#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
// this function calls dfs on each component and also stores the component into bsts simultaneously
void Graph::modifiedDFS() {
    for(int i=0;i<numNodes;i++){
      Node n = nodes[i];  //copyy of node created
      if(visitcnt[n.value -1] == 0) {
        connected_comp++; //connected_comp incremented each time a BST created i.e, when visited_cnt = 0
        dfs(n, all_trees[i]);
        all_trees[i].insert(n.value);
        // all_trees[i].printBST("");
      }
    }
  return;
}

void Graph::printResults() {
    // to count nodes visited once or twice
    int nodes_visit_1 = 0;
    int nodes_visit_2 = 0;
    for (int i=0; i< numNodes; i++){
      if(visitcnt[i] == 1) nodes_visit_1 ++;
      else nodes_visit_2 ++;
    }
    // variable connected_comp stores connected components
    cout<< "No. of connected components : " << connected_comp << endl;
    cout<< "No. of nodes visited once : " << nodes_visit_1 <<endl;
    cout<< "No. of nodes visited twice : " << nodes_visit_2 <<endl;
    cout<< "No. of nodes that are present in a cycle : " << Cycles(cyclenumber) <<endl;
    cout<<"Component BSTs : "<<endl;
    //to print all the BSTs
    for(int i=0;i<numNodes;i++){
      all_trees[i].printBST("");
    } 
  return;
}


#endif
