#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::myDFS(int i){ //for recursive implementation, it is called from the modified DFS
  trees->root->value.insert(i); //inserts node in the BST
    
  if(nodes[i-1].firstVisit==false ) nodes[i-1].firstVisit=true; //update the visit status
  else if(nodes[i-1].secondVisit==false) nodes[i-1].secondVisit = true; //update the visit status
  for(listStruct<int> *j = nodes[i-1].adjacencyList->root; j!=nullptr; j=j->next){ //looping over adjacency list
    int p1 = nodes[i-1].fromNode->root->value; //node from which current node is visited
    int p2 = nodes[i-1].fromNode->root->next->value; //other possible node from which current node is visited
    int q1 = nodes[j->value -1].fromNode->root->value; //node from which the "node to visit" was visited in history
    int q2 = nodes[j->value -1].fromNode->root->next->value; //node from which the "node to visit" was visited in history
      
    if(nodes[(j->value)-1].secondVisit == false && q2!=i && q1!= i){ //next node must not already be visited twice and i to j must have not happened in history
      if(nodes[i-1].secondVisit==true &&  ((j->value==p2 || j->value==p1) || (j->value!=p2 && j->value!=p1))){ // if i was visited from j in history then i can visit j only if i has now been visited twice already
        if(nodes[(j->value)-1].fromNode->root->next->value == 0){nodes[(j->value)-1].fromNode->root->next->value = i;}
        else {nodes[(j->value)-1].fromNode->root->value = i;}
        myDFS(j->value); //recursive call
      }
      else if(nodes[i-1].firstVisit==true && nodes[i-1].secondVisit == false && j->value!=p2 && j->value!=p1){ // if current node is visited for the first time, then the node we now visit must not be same as it came from i.e i to j to i cannot happen if i is visited only once. 
        if(nodes[(j->value)-1].fromNode->root->next->value == 0){nodes[(j->value)-1].fromNode->root->next->value = i;}
        else {nodes[(j->value)-1].fromNode->root->value = i;}
        myDFS(j->value); //recursive call
      }
    }
  }
}

void Graph::modifiedDFS() {
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].firstVisit==false){ //checks for the new components
      connectedComponents++; 
      BST tree;
      trees->push_front(tree);
      myDFS(i+1);
    }
  }
}

void Graph::printResults() {
  for(int i = 0; i<numNodes; i++){
    if(nodes[i].secondVisit == true) nodesVisitedTwice ++;
    else if(nodes[i].firstVisit == true) nodesVisitedOnce++;
  }
  // for(listStruct<BST> *i = trees->root; i = i->next; i!=nullptr) connectedComponents++;
  
  cout << "No. of connected components: " << connectedComponents << endl;
  cout << "No. of nodes visited once: " << nodesVisitedOnce << endl;
  cout << "No. of nodes visited twice: " << nodesVisitedTwice << endl;
  cout << "No. of nodes that are present in a cycle: " << nodesVisitedTwice << endl;
  cout << "Generated BSTs: " << endl;
  
  for(listStruct<BST> *i = trees->root; i!=nullptr; i = i->next){
    connectedComponents++;
    i->value.printBST("", false);
    cout << endl;
  }

//prints the adjacency list - helpful to generate the graph
  // for(int i = 0; i < numNodes; i++){
  //   cout << "root: " << i+1 << " - ";
    
  //   for(listStruct<int> * j=nodes[i].adjacencyList->root; j!=nullptr; j=j->next){
  //     cout << j->value << " " ;
  //   }
  // }

//prints from which nodes a particular node is visited
  // for(int i = 0; i < numNodes; i++){
  //   cout << "node: " << i+1 << ", visitedFrom: "<< nodes[i].fromNode->root->value << "," << nodes[i].fromNode->root->next->value << endl;
  // }
  return;
}


#endif
