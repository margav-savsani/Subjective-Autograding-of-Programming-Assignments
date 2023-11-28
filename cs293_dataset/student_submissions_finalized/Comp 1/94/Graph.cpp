#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() { // modified dfs
  
  for(int i=0;i<numNodes;i++){//The DFS function which is implemented
    if(nodes[i].count_visit!=0) continue;
    else{
      //cout<<i+1<<endl;
      BST*t=new BST();  //Deleting the edge so it becomes directed
//Deleteing the edge when it backtraces
      connected_comp+=1;
      modifiedDFS_help(i,t);
      b->append(t);
    if(nodes[i].color==0) cycle(i,-1);
      
    }

  }
  
  return;
}
void Graph::cycle(int index,int p){//The adjacency list going iteratively
  nodes[index].color=1;
  nodes[index].time=time;//The adjacency list going iteratively
  time+=1;
  list*a=adj_temp[index]->next;//The adjacency list going iteratively
  
  while(a!=NULL){
    if(nodes[a->value].color==0){
      cycle(a->value,index);
    }
    if(nodes[a->value].color==1 && nodes[a->value].value!=p){//The adjacency list going iteratively
      for(int i=0;i<numNodes;i++){
        for(int j=nodes[a->value].time;j<time;j++){
          if(nodes[i].time==j){//The adjacency list going iteratively
              nodes[i].in_cyclic=true;
          }//The adjacency list going iteratively
        }
      }
    }
    a=a->next;
  }
  nodes[index].color=2;//The adjacency list going iteratively
  nodes[index].time=0;
  time-=1;
}
void Graph::modifiedDFS_help(int index,BST*b){
  nodes[index].count_visit+=1;
  if( nodes[index].count_visit==2) cyclic->append(index);//The adjacency list going iteratively
  b->insert(nodes[index].value);//The adjacency list going iteratively
  list *a=adj[index];
  
  while(a!=NULL){
    if(a->value==-1){//The adjacency list going iteratively
      a=a->next;
      continue;
    }
    if(nodes[a->value].count_visit<2 && adj[index]->check(a->value)){
        adj[a->value]->delete_edge(index);
        modifiedDFS_help(a->value,b);
        adj[index]->delete_edge(a->value);//The adjacency list going iteratively
    }
    
    a=a->next;

  }
 
  return;
}

void Graph::printResults() {
  cout<<"connected_comp:"<<connected_comp<<endl;
  int c1=0;
  int c2=0;
  int c3=0;
  for(int i=0;i<numNodes;i++){//Deleting the edge so it becomes directed
    if(nodes[i].count_visit==1){
      c1++;
    }
    
    if(nodes[i].count_visit==2){
      c2++;
    }
    if(nodes[i].in_cyclic){
      c3++;
    }

  }
  cout<<"visited once:"<<c1<<endl;
  cout<<"visited twice:"<<c2<<endl;
  cout<<"no of nodes in any of cycles:"<<c3<<endl;

  BSTstore*t=b;
  while(t!=NULL){
    t->b->printBST("");
    cout<<"----------------------------------------------------------------"<<endl;
    t=t->next;
  }
}

#endif
