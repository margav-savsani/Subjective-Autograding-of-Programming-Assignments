#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::dfs(int n,BST* b){
  dfsStack.push_back(n);
  b->insert(n+1);
  conCompo[n]=1;
  visited[n]++;
  for(int j=0; j<nodes[n]->AdjList.size(); j++){
    if(visited[nodes[n]->AdjList[j]->value -1] < 2){
      if(dfsStack.size() > 2){
        bool yes=false;
        int f=0;
        for(int k=dfsStack.size()-3; k>=0; k--){
          if(dfsStack[k]==nodes[n]->AdjList[j]->value -1) {
            if(dfsStack[k+1]!=n){
              f=k;
              yes=true;
            }
            break;
          }
        }
        if(yes){
          for(int k=f; k<dfsStack.size(); k++) {
            inCycle[dfsStack[k]]=1;
          }
        }
      }
      bool go=true;
      for(int l=dfsStack.size()-2; l>=0; l--){
        if(dfsStack[l]==nodes[n]->AdjList[j]->value-1 && dfsStack[l+1]==n) {
          go=false;
          break;
        }
      }
      if(go) dfs(nodes[n]->AdjList[j]->value -1,b);
    }
  }
  dfsStack.pop_back();
}

void Graph::modifiedDFS() {  
  int k=rand()%numNodes;
  for(int i=0; i<numNodes; i++){
    if(!conCompo[k]) {
      numConnCompo++;
      BST *b = new BST();
      dfs(k,b);
      allBST.push_back(b);
    }
    k=(k+1)%numNodes;
  }
}

void Graph::printResults() {
  cout<<"No. of connected components: "<<numConnCompo<<endl;
  int n1=0,n2=0,nc=0;
  for(int j=0; j<numNodes; j++){
    if(visited[j]==1) n1++;
    else n2++;
    if(inCycle[j]) nc++;
  }
  cout<<"No. of nodes visited once: "<<n1<<endl;
  cout<<"No. of nodes visited twice: "<<n2<<endl;
  cout<<"NO. of nodes that are present in a cycle: "<<nc<<endl;
  cout<<"    CONNECTED COMPONENTS"<<endl<<endl<<endl;
  for(int i=0; i<allBST.size(); i++){
    cout<<"CONECTED COMPONENT: "<<i+1<<endl<<endl;
    allBST[i]->print();
    cout<<endl<<endl;
  }
}

#endif
