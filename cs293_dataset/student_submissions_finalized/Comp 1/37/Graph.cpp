#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::dfs(int curr,BST * tree,int last){
  static int time_=1;
  time_++;
  time1[curr]=time_;
  
  
  // if(tree==nullptr) cout<<"qyhwfc";
  // tree->insert(curr);
  if(nvisited[curr]==2) return;
  nvisited[curr]++;
  tree->insert(curr);
  //nvist=0
  if(nvisited[curr]==1){
    
    
    if(nodes[curr].nadjacent==0){
      
      return;
    }
    
    
    listofnodes* adjnode=nodes[curr].adjacent;
    while (adjnode !=nullptr)
    {
      if(adjnode->index != last){
        if(nvisited[adjnode->index]==0){
          predecessor[adjnode->index]=curr;
          
          dfs(adjnode->index,tree,curr);
        }


      }
      adjnode=adjnode->next;
    }
    adjnode=nodes[curr].adjacent;
    while (adjnode !=nullptr)
    {
      if(adjnode->index != last){
        if(nvisited[adjnode->index]==1){
          
          dfs(adjnode->index,tree,curr);
        }


      }
      adjnode=adjnode->next;
    }
    
    return;
  }
  if(nvisited[curr]==2){
    if(nvisited[last]==1){
      int p=predecessor[curr];
      isincycle[predecessor[last]]=true;
      isincycle[last]=true;
      isincycle[curr]=true;
      int i=0;
      int l=last,r=p;
      while (r!= -1 && i < numEdges)
      {
        /* code */
        r=predecessor[r];
        i++;
      }
      if(r!=-1){
        while(p!=predecessor[last] && p!=-1 && p!= curr && i < numEdges){
          isincycle[p]=true;
          p=predecessor[p];
          
        }
      }
      else{
        r=p;
        while(l!=-1){
          r=p;
          if(l==r)break;
          while(r!=-1){
            r=predecessor[r];
            if(l==r)break;
          }


          l=predecessor[l];
        }
        int lca=l;
        l=last;
        r=p;
        while(l!=lca || r!=lca){
          isincycle[l]=true;
          isincycle[r]=true;
          if(l!=lca && r!=lca ){
            l=predecessor[l];
            r=predecessor[r];
          }
          if(l==lca && r!=lca){
            r=predecessor[r];
          }
          else{
            l=predecessor[l];
          }

        }
      }
      listofnodes* adjnode=nodes[curr].adjacent;
      while (adjnode !=nullptr)
      {
        if(adjnode->index != last){
          if(nvisited[adjnode->index]==0){
            predecessor[adjnode->index]=curr;
            
            dfs(adjnode->index,tree,curr);
          }
          else if(nvisited[adjnode->index]==1){       
            dfs(adjnode->index,tree,curr);
          }
          
        }
        adjnode=adjnode->next;
      }
      return;
    }

    if(nvisited[last]==2){
      listofnodes* adjnode=nodes[curr].adjacent;
      while (adjnode !=nullptr)
      {
        if(adjnode->index != last){
          if(nvisited[adjnode->index]==0){
            predecessor[adjnode->index]=curr;
            dfs(adjnode->index,tree,curr);
          }
          else if(nvisited[adjnode->index]==1){       
            dfs(adjnode->index,tree,curr);
          }
          
        }
         adjnode=adjnode->next;
      }
      return;
    }

  
  
    return;
  }



}

void Graph::modifiedDFS() {
 
  int root=rand() % numNodes; //start of the DFS
  BST *temp=new BST();
  cout<< "root is:" <<root<<endl;
  nconnected++;
  dfs(root,temp,-1);
  trees = new Trees(temp);

    Trees* curr=trees;  
    for(int i=0;i<numNodes;i++)
    {
      if(nvisited[i]==0){
        temp=new BST();
        
        
        dfs(i,temp,-1);
        curr->next=new Trees(temp);
        nconnected++;
      }

    }
  
  
  // for(int i=0;i<numNodes;i++)
  // {
  //   cout<<nvisited[i]<<" ";

  // }
  // cout<<endl;
  // for(int i=0;i<numNodes;i++)
  // {
  //   cout<<isincycle[i]<<" ";

  // }
  // cout<<endl;
  return;
}

void Graph::printResults() {
  cout<<"No. of connected components:"<<nconnected<<endl;
  int j=0;
  int cyc=0;
  for(int i=0 ; i< numNodes; i++){
    if(nvisited[i]==1)j++;
    if(isincycle[i])cyc++;
  }
  cout<<"No. of nodes visited once:"<<j<<endl;
  cout<<"No. of nodes visited twice:"<<numNodes-j<<endl;
  cout<<"No. of nodes that are present in a cycle:"<<cyc<<endl;
  Trees* curr=trees; 
  while (curr!=nullptr)
  {
    curr->tree->printBST("");
    curr=curr->next;
  }
  

  return;
}

#endif
