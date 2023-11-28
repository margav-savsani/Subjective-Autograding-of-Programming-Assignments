#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void Graph::DFS(int p){

  nodes[p].visited++; // increment of number of visits of each node

  bst->insert(nodes[p].value); // insertion of node in BST

  for (int i = 0; i < numNodes; i++)
  {
    if (adjacent[p][i])
    {
      if (nodes[i].visited < 2)
      {
        adjacent[i][p] = 0; // to avoid backtracking to the same element(parent)

        DFS(i); // iterating over the adjacency list
        adjacent[i][p] = 0;
      }
    }
  }
}

void Graph::modifiedDFS() {
  
  
 
  int k=0;
  for(int i=0;i<numNodes;i++){
      
      if(nodes[i].visited==0){
        
        bst=new BST;//seperate bst for unconnected components
        con++;//to keep a count on number of connections
        DFS(i);
        cout<<"connected_component:"<<con<<endl;
        bst->printBST("");
        cout<<endl;
      }
      
  }
  
  return ;
}

void Graph::printResults() {
  int con1=0,con2=0;
  
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited==1) //counting number of nodes visited once
      con1++;
    if(nodes[i].visited==2){//counting number of nodes visited twice
      con2++;
    }
  }
  
  cout<<"No. of connected components:"<<con<<endl;
  cout<<"No. of nodes visited once:"<<con1<<endl;
  cout<<"No. of nodes visited twice:"<<con2<<endl;
  cout<<"No. of nodes that are present in a cycle:"<<con2<<endl;
  return;
}

#endif
