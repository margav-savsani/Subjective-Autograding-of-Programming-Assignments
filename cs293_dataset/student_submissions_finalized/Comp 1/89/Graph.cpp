#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;
// Add code as appropriate for your implementation

void Graph::DFS(int i, int j, BST &tree){ 
    
   v[i]++;   
   if(c[i]==1)
    {
         
      int node=j;
         int k = 0;	  
         cycle[node]=1; 
          while(node!=i)
           {
             if(k>numNodes) break; 
             node=parent[node];
             cycle[node]=1;
             k++;
            }
     }
     
   parent[i]=j;  
   c[i]=1;   
   listOfObjects<int>* e=nodes[i].edge->next; 
   while(e!=NULL){
      if(v[e->object]<2)
       {
        if(e->object!=j)
          {
            tree.insert(nodes[e->object].value); //inserting the value of the node in the adjacency list into the tree  
            DFS(e->object, i, tree);  // calling DFS for the nodes in the adjacency list with parent as i
           }
         }  
       e=e->next; 
     } 
  return; 
}           

void Graph::modifiedDFS() {
  for(int i=0; i<numNodes; i++)
     {
        cycle[i]=0;
        c[i]=0;
        v[i]=0;
      }  
  while(true){
    int a = 0;
    int i;
    for(i=0; i<numNodes; i++)   
       if(v[i]==0) {a=1;break;}
    if(a==0) break;
   BST tree;  // a tree is created every time we have a different connected component
    tree.insert(nodes[i].value);
    DFS(i, -10, tree); 
    
     // ading this tree to the list of BSTs
   if(trees==NULL)
       trees=new listOfObjects<BST>(tree);
   else
    {
      listOfObjects<BST>* trees1 = trees;
      while(trees1->next!=NULL)  
         trees1=trees1->next;
      trees1->next=new listOfObjects<BST>(tree);
     } 
   }  
  return;
}

void Graph::printResults() {
  int n=1;
    // no of connected components = no of BSTs in the list trees
  listOfObjects<BST>* T1 = trees;
  while(T1->next!=NULL){
    n = n+1; 
    T1=T1->next;
   } 
  cout<<"No. of connected components: "<<n<<endl;
  int p=0;
  int q=0;
  int r=0;
  for(int i=0; i<numNodes; i++) 
    {
      if(v[i]==1) p++;
      else if(v[i]==2) q++;
      if(cycle[i]==1) r++;
     } 
  cout<<"No. of nodes visited once: "<<p<<endl;
  cout<<"No. of nodes visited twice: "<<q<<endl; 
  cout<<"No. of nodes that are present in a cycle: "<<r<<endl;
  listOfObjects<BST>* T = trees;
    // printing the BSTs of the list(trees) 
  while(T!=NULL){  
    (T->object).printBST("");
    if(T->next==NULL) break;
    T=T->next;
   }
  return;
}

#endif
