#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::dfs(int i, int * max){ //main dfs
  nodes[i-1].visited=true;
  if(*max < i){*max=i;}
  for(listStruct<int>*j=nodes[i-1].AdjacencyList->root; j!=nullptr; j=j->next){
    if(!nodes[j->value-1].visited)dfs(j->value, max);
  }
}
void Graph::dfs2(int i, int max){ //dfs for calculating maximum value
  nodes[i-1].visited=true;
  nodes[i-1].value = max;
  for(listStruct<int>*j=nodes[i-1].AdjacencyList->root; j!=nullptr; j=j->next){
    if(!nodes[j->value-1].visited)dfs2(j->value, max);
  }
}


int Graph::findSimilar(int v1, int v2){ //finds similarity realtion of the second condition
  if(!nodes[v1-1].SimilarNodes->Exists(v2) || !nodes[v2-1].SimilarNodes->Exists(v1)){
    int v = 0;
    for(listStruct<int> *i = nodes[v1-1].IncomingEdges->root; i!=nullptr; i=i->next){
      for(listStruct<int> *j = nodes[v2-1].IncomingEdges->root; j!=nullptr; j=j->next){
        if(nodes[i->value-1].SimilarNodes->Exists(j->value)){ v++; break;}
      }
    }

    int w = 0;
    for(listStruct<int> *i = nodes[v2-1].IncomingEdges->root; i!=nullptr; i=i->next){
      for(listStruct<int> *j = nodes[v1-1].IncomingEdges->root; j!=nullptr; j=j->next){
        if(nodes[i->value-1].SimilarNodes->Exists(j->value)){ w++; break;}
      }
    }

    if(v==nodes[v1-1].IncomingEdges->count() && w==nodes[v2-1].IncomingEdges->count() && v!=0 && w!=0){
      if(!nodes[v1-1].SimilarNodes->Exists(v2))nodes[v1-1].SimilarNodes->push_front(v2);
      if(!nodes[v2-1].SimilarNodes->Exists(v1))nodes[v2-1].SimilarNodes->push_front(v1);
      return 1;
    }
  }
  return -1;
}

void Graph::printResults() {
  ofstream file;
  file.open("outgraph.txt");

  file << "Source nodes: ";
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].sourceNode()) file << i+1 << " ";
  }

  file << endl;
  
int q = 1;
while(q==1){
    for(int i = 0; i < numNodes; i++){
      for(int j = 0; j < numNodes; j++){
        // file << "looped" << endl;
        q = findSimilar(i+1,j+1);
      }
    }
}

  file << "Similar node pairs: ";
  for(int i = 0; i < numNodes; i++){
    for(listStruct<int> * j = nodes[i].SimilarNodes->root; j!=nullptr; j=j->next){
      if(!nodes[i].AdjacencyList->Exists(j->value) && i+1!=j->value)  nodes[i].AdjacencyList->push_front(j->value);
      if(!nodes[j->value-1].AdjacencyList->Exists(i+1) && i+1!=j->value) nodes[j->value-1].AdjacencyList->push_front(i+1);
      file << "(" << i+1 << "," << j->value << ")" << " ";
    }
  }
  file << endl;
  file << "Collapsed graph:" << endl;

  // for(int i = 0; i < numNodes; i++){
  //   file << "Node " << i+1 << ": " ;
  //   for(listStruct<int>* j = nodes[i].AdjacencyList->root; j!=nullptr; j=j->next){
  //     file << j->value << " ";
  //   }
  //   file << endl;
  // }

  for(int i = 0; i < numNodes; i++){ //dfs on the undirected graph
    if(nodes[i].visited==false) {
      connectedComponents++;
      int max = 0;
      nodes[i].visited = true;
      if(nodes[i].AdjacencyList->root!=nullptr){
        int j = nodes[i].AdjacencyList->root->value;
        dfs(j, &max);
        maxValues->push_front(max);
      }
      else{
        maxValues->push_front(i+1);
      }
    }
  }
  for(int i = 0l; i < numNodes; i++){
    nodes[i].visited = false;
  }


  listStruct<int> *itr = maxValues->root;
  listStruct<int> *itr2 = nullptr;
  while(itr!=nullptr){
    itr2 = itr;
    itr = itr->next;
  }
  file << connectedComponents << ": " ; //prints final number of nodes after collapse in the graph
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].visited==false) {
      int max = itr2->value;
      nodes[i].visited = true;
      nodes[i].value = max;
      if(nodes[i].AdjacencyList->root!=nullptr){
        int j = nodes[i].AdjacencyList->root->value;
        dfs2(j, max);
        itr2 = itr2->prev;
      }
      else{
        itr2 = itr2->prev;
      }
    }
  }

  for(int i = 0; i < numNodes; i++){
    for(listStruct<int> * j = nodes[i].OutgoingEdges->root; j!=nullptr; j=j->next){
      if(nodes[j->value-1].value!=j->value) {
          j->value = nodes[j->value-1].value;
      }
    }
  }
  for(listStruct<int> * i = maxValues->root; i!=nullptr; i=i->next){
    file << i->value << " " ;
  }
  file << endl;

  newNodes = new Node[numNodes]; //new nodes after collapse
  
  for(int i = 0; i < numNodes; i++){
    for(listStruct<int> * j = nodes[i].OutgoingEdges->root; j!=nullptr; j=j->next){
      if(!newNodes[nodes[i].value-1].NewOutGoing->Exists(j->value) && nodes[i].value!=j->value) newNodes[nodes[i].value-1].NewOutGoing->push_front(j->value);
    }
  }
  
  for(listStruct<int> *k = maxValues->root; k != nullptr; k = k->next){
    for(listStruct<int> *j = newNodes[k->value-1].NewOutGoing->root; j!=nullptr; j=j->next){
      file <<  k->value << " " << j->value << endl;
    }
  }


  

//prints the adjacency list - helpful to generate the graph
  // for(int i = 0; i < numNodes; i++){
  //   file << "root: " << i+1 << " - ";
    
  //   for(listStruct<int> * j=nodes[i].adjacencyList->root; j!=nullptr; j=j->next){
  //     file << j->value << " " ;
  //   }
  // }

//prints from which nodes a particular node is visited
  // for(int i = 0; i < numNodes; i++){
  //   file << "node: " << i+1 << ", visitedFrom: "<< nodes[i].fromNode->root->value << "," << nodes[i].fromNode->root->next->value << endl;
  // }
  return;
}


#endif

