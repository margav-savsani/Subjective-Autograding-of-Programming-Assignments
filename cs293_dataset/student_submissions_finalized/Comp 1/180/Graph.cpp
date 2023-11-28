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
  for(int i = 0; i < numNodes; i++){          //iterate on all list
    if(nodes[i].visit == 0){
      cc++;                                   // if this node isn't visited it means it is not connected to any other components
        //WE GOT NEW CONNECTED COMPONENT SO INCREMENT NUMBER OF CONNECTED COMPONENTS
      BST* bst = new BST();
      if(bstheads == nullptr){
        bstheads = new listOfObjects<BST*>(bst);
        //start DFS on this node 
        dfs(i,-10);
      }
      else{
        listOfObjects<BST*>* end = bstheads;
        while(bstheads->next != nullptr){
          bstheads = bstheads->next;
        }
        bstheads->next = new listOfObjects<BST*>(bst);
        bstheads = bstheads->next;
        dfs(i,-10);
        bstheads = end;
      }
      
      
    }
  }
  return;
}

void Graph::printResults() {
  cout << "NUMBER OF CONNECTED COMPONENTS = " << cc << endl;
  cout << "NUMBER OF NODES VISITED ONCE = " << nodes_visited_once << endl;
  cout << "NUMBER OF NODES VISITED TWICE = " << nodes_visited_twice << endl;
  cout << "NUMBER OF NODES IN CYCLE = " << nodes_visited_twice << endl;
  listOfObjects<BST*>* trees = bstheads;
  while(trees != nullptr){
    trees->object->printBST("",false);
    trees = trees->next;
  }
  return;
}

#endif
