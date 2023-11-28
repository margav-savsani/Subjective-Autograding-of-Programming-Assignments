#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

int counter = 0;
void Graph::myDFS(int v, int prev){// v is the index of the node
  visited[v] ++;
  arr[v] = counter; counter++; // counts the arrival time
  forest.tail->object->insert(v+1); // 
  if(v==prev){
    return;
  }
  if(prev!=-1 && deleteParent(&nodes[v], &nodes[prev])==1){
    parentArray[v] = nodes[prev];
  }
  Node* inList = nodes[v].list;
  while(inList!=nullptr){
    if (inList->value == NEG_INF){
          inList = inList->next;
          continue;
        }
    if (nodes[v].backtrack.find(inList->value-1)){
      inList = inList->next;
      continue;
    }
    if(visited[inList->value -1]<2){
      
      myDFS(inList->value-1, v);
      nodes[v].backtrack.add(inList->value-1);
    }
    inList = inList->next;
  }
}
void Graph::modifiedDFS() {
  int connected_pointer = 0;

  while(true){
    BST *tree = new BST();
    forest.add(tree);
    
    myDFS(connected_pointer, -1);

    // after finishing DFS on one component, advance the connected_pinter to the index for which visited[i] = 0
    while(visited[connected_pointer]!=0 && connected_pointer<numNodes){
      connected_pointer++;
    }
    if(connected_pointer == numNodes){
      break;
    }
  }
}

void Graph::printResults() {
  int visit0 = 0;
  int visit1 = 0;
  int visit2 = 0;
  int cycle = 0;
  for (int i = 0 ; i<numNodes;i++){
    if(visited[i] == 1){visit1++;}
    else if(visited[i] == 2){visit2++;}
    else if (visited[i] == 0){visit0++;}
    if(inCycle[i] == true){cycle++;}
  }
  cout<<"-------------------------------------------------------------------------"<<endl;
  cout<<"No. of connected components:"<<forest.size<<endl;
  cout<<"No. of nodes visited once: "<<visit1<<endl;
  cout<<"No. of nodes visited twice: "<<visit2<<endl;
  cout<<"No. of nodes in a cycle: "<<visit2<<endl;
  cout<<"-------------------------------------------------------------------------"<<endl;
  forest.print();
  return;
}

#endif
