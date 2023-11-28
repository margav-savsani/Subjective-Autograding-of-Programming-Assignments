#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
#define COUNT 10
#include<vector>




// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++){
    if(visit[i]==0){
      DFSpart2(i+1);
      conncomp++;
    }
  }
  for(int i=0;i<numNodes;i++){
    if(visit[i]==1)once++;
    if(visit[i]==2)twice++;
    vector<int>arr;
    vector<int>parent;
    bool vis[numNodes];
    for(int j=0;j<numNodes;j++)vis[j]=false;
    int num=0;
    arr.push_back(i+1);
    parent.push_back(-1);

    while(arr.size()!=0){
    int a=arr[arr.size()-1];
    int p=parent[parent.size()-1];
    if(a==i+1)num++;
    parent.pop_back();
    arr.pop_back();
    if(vis[a-1])continue;
    else{
      vis[a-1]=true;
      list*adj=nodes[a-1].edge;
      while(adj!=NULL){
        if(adj->value==p){
          adj=adj->next;
          continue;
        }

        parent.push_back(a);
        arr.push_back(adj->value);
        adj=adj->next;
        }
      }
    }
    if(num>1)cyclenodes++;
  }
}

void Graph::DFSpart2(int x){
  BST b;
  vector<int>arr;
  vector<int>parent;
  arr.push_back(x);
  parent.push_back(-1);
  while(arr.size()!=0){
    int a=arr[arr.size()-1];
    int p=parent[parent.size()-1];
    parent.pop_back();
    arr.pop_back();
    if(visit[a-1]==2)continue;
    else{
      b.insert(a);
      visit[a-1]++;
      list*adj=nodes[a-1].edge;
      while(adj!=NULL){
        if(adj->value==p){
          adj=adj->next;
          continue;
        }
        parent.push_back(a);
        arr.push_back(adj->value);
        adj=adj->next;
      }
    }
  }
  bst.push_back(b);
  return;
}

void Graph::printResults() {
  cout<<conncomp<<endl;
  cout<<once<<endl;
  cout<<twice<<endl;
  cout<<cyclenodes<<endl;
  for(int i=0;i<bst.size();i++)bst[i].printBST("");
  return;
}

#endif