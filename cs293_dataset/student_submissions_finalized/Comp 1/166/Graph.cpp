#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void goon(Node *curr,BST tree,int n1,int n2,int n3){ //the modified dfs function which can be used for recursion
  cout<<"yes"<<endl;
  //if the visits are 0, it means it was not visited atleast once
  //So if we face these nodes, We can increase total number of nodes
  //when we visit them, we are also increasing the nodes with one visit
  //if the node we reach has already one visit, then by the time we cross it,
  //number of nodes with single visit decreases by one
  //number of nodes with 2 visits increases by one
  if(curr->visits=0){n1++;n2++;} 
  if(curr->visits=1){n2--;n3++;}
  if(curr->visits>1){return;}
  else if(curr->visits<=1)
    curr->visits=curr->visits+1;
    tree.insert(curr->value);
    listOfObjects<Node *> *rey;
    rey=curr->elist;
    listOfObjects<Node *> *rey2;
    rey2=curr->elist;
    while(rey!=nullptr){
       //once we reach a node, removing the current node from the adjacency list of the 
       //elements present in the adjacency list of the current node so that the code doesn't        
       //go backwards in th egraph uneccessarily
      Node *temper;
      temper=rey->object;
      listOfObjects<Node *> *ray;
      ray=temper->elist;
      while(ray!=nullptr){
        if(ray->object==curr){
          if(ray->prev==nullptr && ray->next==nullptr){
            ray=nullptr;
          }
          else if(ray->prev!=nullptr && ray->next==nullptr){
            ray->prev->next==nullptr;
            ray=nullptr;
          }
          else if(ray->prev==nullptr && ray->next!=nullptr){
            ray->next->prev=nullptr;
            ray=nullptr; 
          }
          else{
            ray->prev->next=ray->next;
            ray->next->prev=ray->prev;
            ray=nullptr;
          }
        }
        else{ray=ray->next;}
      }   
      rey=rey->next;
    }
    while(rey2!=nullptr && rey2->object->visits<2){
      goon(rey2->object,tree,n1,n2,n3);
      rey2=rey2->next;
    } //recursive calling 
    return; 
}
// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  
  BST tree;

  listOfObjects<Node *> *ite;
  Node *simp;
  
  int n1 = rand() % numNodes;
  simp=&(nodes[n1]); //starting node is choosen randomly
  goon(simp,tree,totn,v1,v2); //starting the dfs
  listOfObjects<BST *> *tutu;
  tutu->object=&tree;
  tutu->next=nullptr;
  tutu->prev=nullptr; //first BST
  blist=tutu; //appending it to the BST list
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visits=0){ //searching if there are any nodes left unvisited
      BST tree1;
      comp++;
      goon(&(nodes[i]),tree1,totn,v1,v2);
      listOfObjects<BST *> *blast;
      blast->object=&tree;
      blist->next=blast; //creating and adding the remaining bsts
    }
  }
  return;
}

void Graph::printResults() {
  cout<<comp<<endl; //number of components
  cout<<v1<<endl; //number of nodes with 1 visit
  cout<<v2<<endl;  //number of nodes with 2 visits
  cout<<totn<<endl; //total number of nodes
  while(blist!=nullptr){
    if(blist->object!=nullptr){
    blist->object->printBST(" ",false);}
  } //printing all the BSTs
}

#endif
