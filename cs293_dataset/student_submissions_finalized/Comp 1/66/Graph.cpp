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
  for(int i=0;i<numNodes;i++){
    BST *bst;
    if(nodes[i].no_of_visits==0){
      bst = new BST;
      DFS_visit(&nodes[i],bst);
      b.push(bst);
    }
  }
  return;
}

void Graph::printResults() {
   LinkedList_node<BST *> *x = b.node;
   int i=0;
   while(x!=nullptr){
    i++;
    x = x->next;
   }
   cout << "No. of connected components: " << i << endl;
    
   int no[2];no[0]=0;no[1]=0;
   for(int j=0;j<numNodes;j++){
    no[nodes[j].no_of_visits-1]++;
   }
   cout << "No. of nodes visited once: "<< no[0] <<endl;
   cout << "No. of nodes visited twice: "<<no[1]<<endl;
   cout << "No. of nodes that are present in a cycle: "<<no_of_nodes()<<endl;
   i =1;
   x = b.node;
   cout  << "Following are BSTs different connected components:"<<endl;
   while(x!=nullptr){
    cout << "BST No - "<<i<<endl;
    i++;
     x->a->printBST("");
     x = x->next;
   }

}

#endif
