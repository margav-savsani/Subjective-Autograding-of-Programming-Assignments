#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


// Add code as appropriate for your implementation
void Graph:: DFS(Node *node, int val,BST* t,int* k){
  if(node->visit>2) return;
  node->visit++;
  *k = *k+1;
  node->num=*k;
  for(int i=0; i<node->neighbours;i++){

    if(nodes[node->adjacency[i]].visit < 3 && (node->adjacency[i] != node->parent1 && node->adjacency[i] != node->parent2) ){ 
      if(nodes[node->adjacency[i]].visit==1 && node->visit==1){ 
        cycl=node->num-nodes[node->adjacency[i]].num+1; //subtracting the index of the traversal for getting the cycle length
      }
      if(nodes[node->adjacency[i]].visit==0)  nodes[node->adjacency[i]].parent1= val; //updating parent
      if(nodes[node->adjacency[i]].visit==1)  nodes[node->adjacency[i]].parent2= val;
      if(nodes[node->adjacency[i]].visit<2){
        t->insert(node->adjacency[i]+1); // inserting node into BST
        DFS(&nodes[node->adjacency[i]],node->adjacency[i],t,k);
      }
    }
  }
}

void Graph::modifiedDFS()
{
  for(int i=0; i<numNodes; i++){
    if(nodes[i].visit==0){  // because if the node is already visited then  everything is already traversed through that
     BST* t = new BST(i+1); // inserting the node into the tree
     connectedcomp++; 
     int *k= new int(0);
     DFS(&nodes[i],i,t,k);
     cout<<"Tree No: "<<connectedcomp<<endl;
     cout<<endl;
     t->printBST(""); //prints the BST tree
     cout<<endl; // for a better look on terminal
     cout<<endl;
    }
    
  } 
  return;
}

void Graph::printResults()
{
  int v1=0,v2=0;
  for(int i=0; i<numNodes; i++){
    if(nodes[i].visit==1) v1++;
    if(nodes[i].visit==2) v2++;
  }
  cout<<"No of Nodes visted once  : "<<v1<<endl; //printing the required things
  cout<<"No of Nodes visted twice  : "<<v2<<endl;
  cout<<"Connected components : "<<connectedcomp<<endl;
  cout<<"No of nodes in cycles : "<<cycl<<endl;
  return;
}

#endif