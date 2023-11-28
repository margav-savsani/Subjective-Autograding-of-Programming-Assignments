#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;

int Graph::func(int ind, int indnew ,int &num){
  int count = 1;
  color[ind]++;
  for(int j=0;j<numNodes;j++){
    if(*(adjmat + (ind) * numNodes + j)==1){ 
      if(color[j]!=2){
        if(*(parentcyc + ind * numNodes + j)!= 1){
          count++;
          if(j==indnew){
            num = count - num;
            break;}
          else{
            *(parentcyc + j * numNodes + ind)=1;
            count = count + func(j,indnew,num);
            }
        }
      }
    }
  } 
return count;

}

void Graph::DFS(int v , BST *t){
  visited[v-1]++;
  for(int j=0;j<numNodes;j++){
    if(*(adjmat + (v-1) * numNodes + j)==1){ 
      if(visited[j]!=2){
        if(*(parentmat + (v-1) * numNodes + j)!= 1){
          t->BSTInsert(t,j+1);
          *(parentmat + j * numNodes + (v-1))=1;
          DFS(j+1,t);
        }
      }
    }
  }
}

//DSF for connected component
void Graph::DFS_per_component(int c,Node* src){
  BST* tree = new BST(src->value);
  DFS(src->value,tree);
  tree->BSTPrint(tree,"",false);
  cout<<"--------------------------------------------------------------"<<endl;
}
void Graph::modifiedDFS() {
  int components = 1;
  Node* src = &(nodes[0]);
  cout<<"BST's generated:"<<endl;
  cout<<"--------------------------------------------------------------"<<endl;
  DFS_per_component(components,src);

  for(int k=0;k<numNodes;k++){
    if(visited[k]==0){
      components ++;
      DFS_per_component(components,&(nodes[k]));
    }
  }
  cout<<"No. of connected components:"<<components<<endl;
  
  return;
}

void Graph::printResults() {
  int once =0;
  int twice =0;
  bool a = false;
  

  for (int j =0 ;j<numNodes;j++){
    if(visited[j]==1){
      once++;
    }
    if(visited[j]==2){
      twice++;
    }
  }
  
  for(int l=0;l<numNodes;l++){
    if(visited[l]==2){
      a = true;
      int num = -1;
      int nodes_cycle=func(l,l,num);
      cout<<"No. of nodes that are present in some cycle are "<<num<<endl;
      break;
    }
  }

  if(!a){
    cout<<"No cycles are present" <<endl;
  }
 
  cout<<"No. of nodes visited once:"<<once<<endl;
  cout<<"No. of nodes visited twice:"<<twice<<endl;
  // for(int l=0;l<numNodes;l++){
  // cout<<parentdfs[l]<<endl;}
    
}

#endif
