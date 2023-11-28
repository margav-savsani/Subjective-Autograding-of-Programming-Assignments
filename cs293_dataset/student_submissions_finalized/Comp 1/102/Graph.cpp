#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include <bits/stdc++.h>
using namespace std;

// Add code as appropriate for your implementation


void Graph::DFS(int v,BST*B){
  vector<int> adj=path[v];
  vector<int>::iterator i;
  // cout<<"v is "<<v<<endl;
  if(!adj.empty()){
    for (i = adj.begin(); i != adj.end(); ++i){
      // cout<<"*i is "<<*i<<endl;
      if(!nodes[*i].visited_Twice ){
        if(nodes[*i].visited_Once){
          nodes[*i].visited_Twice=true;
        }
        else{
          nodes[*i].visited_Once=true;
        }
        // cout<<"this is INserted "<<*i<<endl;
        B->insert(*i+1);
        
        DFS(*i,B);
      }

    }
  }
  else if(adj.empty()){
    nodes[v].visited_Once=true;
    B->insert(v+1);
  }

  return;
}

void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++){
    if(!nodes[i].visited_Once){//if not even visited once,means; we are starting new connected component
      components++;
      // nodes[i].visited_Once=true;
      BST*BT_HO_GYI=new BST();
      // vector<int> adj=path[i];
      // for (int x=0;x<adj.size();x++){

      // }
      // vector<int>::iterator i;
      // for (i = adj.begin(); i != adj.end(); ++i){
      //   // if (!visited[*i]){
      //   //     DFS(*i);
      //   // }

      //   cout<<*i<<" ";
      // }
      
      DFS(i,BT_HO_GYI);
      // Node*currN=BT_HO_GYI->root;
      // while(true){
      //   cout<<currN->value<<endl;
      //   currN=currN->left;
      // }
      // cout<<"Creating\n";
      cout<<"[ CREATING NEW BST ]\n";
      BT_HO_GYI->printBST("",false);
    }
  }
  return;
}

void Graph::printResults() {
  int onceVisited=0;
  // for(int i=0;i<numNodes;i++){
  //   if(nodes[i].visited_Once && !nodes->visited_Twice){
  //     onceVisited++;
  //   }
  // }
  int twiceVisited=0;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited_Twice){
      twiceVisited++;
    }
  }
  onceVisited=numNodes-twiceVisited;
  
  cout<<"No. of connected components: "<<components<<endl;
  cout<<"No. of nodes visited once:" <<onceVisited<<endl;
  cout<<"No. of nodes visited twice: "<<twiceVisited<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<twiceVisited<<endl;
  return;
}

#endif
