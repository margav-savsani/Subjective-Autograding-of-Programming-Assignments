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
int n1= rand()%numNodes;
    BST* b=new BST();
    adjlist *path;
    path=new adjlist(0);
    DFS(nodes[n1].value-1 , b,path);
    adjlist *temp=path;
    
    
    int size=length(temp);
    
    int *arr=new int[size];
    for(int i=0;i<size;i++){
      arr[i]=temp->value;
      //cout<<arr[i]<<"elem"<<endl;
      temp=temp->next;
    }
    for(int i=1;i<size;i++){
     // cout<<"strat"<<endl;
      for(int j=i+1;j<size;j++){
        //cout<<"strat2"<<endl;
        if(arr[i]==arr[j]){
          //cout<<arr[i]<<" == "<<arr[j]<<endl;
          for(int k=i;k<j+1;k++){
            cycle[arr[k]-1]=1;
          }
        }
      }
    }
  
    cout<<"BST"<<endl;
    b->printBST("",false);
  
    while(!completed(visited,numNodes)){
    //cout<<"damn"<<endl;
    int n2;
    for(int i=0;i<numNodes;i++){
      if(visited[i]==0){
          n2=i;
      }
    }
    conncomp++;
    BST *b1=new BST();
    adjlist *path1;
    path1=new adjlist(0);
    DFS(nodes[n2].value-1,b1,path1);
        adjlist *temp1=path1;
    int size1=length(temp1);
    int *arr1=new int[length(temp1)];
    for(int i=0;i<length(temp1);i++){
      arr1[i]=temp1->value;
      temp1=temp1->next;
    }
    for(int i=1;i<size1;i++){
      for(int j=0;j>i && j<size1;j++){
        if(arr1[i]==arr1[j]){
          for(int k=i;k<j+1;k++){
            cycle[arr1[k]-1]=1;
          }
        }
      }
    }
    cout<<"BST"<<endl;
    b1->printBST("",false);
    }
    return;
}

void Graph::printResults() {
   cout<<"NO.OF CONNECTED COMPONENTS : "<<conncomp<<endl;
    int once=0;
    int twice=0;
    for(int i=0;i<numNodes;i++){
      if(visited[i]==1){once++;}
      if(visited[i]==2){twice++;}
    }
    cout<<"No. of nodes visited once: "<<once<<endl;
    cout<<"No. of nodes visited twice: "<<twice<<endl;
    int ncy=0;
    for(int i=0;i<numNodes;i++){
      if(cycle[i]==1){ncy++;}
    }
    cout<<"No. of nodes that are present in a cycle: "<<ncy<<endl;
  return;
}

#endif
