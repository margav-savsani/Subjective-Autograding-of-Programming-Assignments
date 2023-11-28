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
      int components = 0 , onetime = 0 , twice = 0 , cyclicnodes = 0 ; 
      for ( int i = 0 ; i < numNodes ; i++ ) { 
           if ( nodes[i].visited == 0) { 
                 BST* t = new BST(nodes[i].value);
                 nodes[i].arrtime = 0 ;
                 //the recursive dfs call in Graph.h
                 DFS(i,0,t);
                 cout<<"BST Tree "<<endl ;
                 t->printBST("");
                 components++ ; 
           }
      }
      for ( int i = 0 ; i < numNodes ; i++ ) {  
          if ( nodes[i].visited == 2) twice ++ ; 
          else onetime++ ; 
          if ( cycle[i] ) {  cyclicnodes++ ; }
      }
      
      cout << "Total number of connected components : " << components << endl;
      cout << "Total number of once visited :  " << onetime << endl;
      cout << "Total number of twice visited : " << twice << endl;
      cout << "No. of nodes in a cycle : " << cyclicnodes << endl;
}

void Graph::printResults() {
  return;
}

#endif
