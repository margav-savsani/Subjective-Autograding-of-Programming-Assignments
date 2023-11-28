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
  static int recursion_depth = 0;
  int parent = currNode->value - 1;
  static Node* prevNode = currNode;
  static int c = 0;
  int inCycle = 0;
  static bool *flag = new bool[numNodes];
  if(recursion_depth==0){
    c=0;
  }
  recursion_depth++;
  c++;

  if(recursion_depth == 1 ){
    if (numTrees==0){
      trees = new BST();
      numTrees++;
    }
    
  }
  // cout<<currNode->value<<endl;
  visited[currNode->value-1]++;
  if(visited[currNode->value-1]<=2){
    if(visited[currNode->value -1]==1){
      flag[currNode->value-1]=true;
    }
    BST *t = trees;
    while(t->next!=nullptr){
      t = t->next;
    }
    // cout<<"insert "<<currNode->value<<endl;
    t->insert(currNode->value);
  }

  adjacencyList *temp = currNode->adjStart;
  parent = prevNode->value-1;
  int par = currNode->value - 1;
  inCycle = 0;
  while(temp != nullptr){

    // cout<<"currNode->value "<<currNode->value<<endl;
    if( temp->direction == 0 && visited[temp->nodeIndex] <= 2 ){

      if( c == 1 ){

        prevNode = currNode;
        currNode = &nodes[temp->nodeIndex];
        modifiedDFS();
        temp->direction = 1;
        // backtraced[currNode->value - 1] = true;
        // cout<<"parent"<<parent+1<<" par "<<par+1<<endl;
        prevNode = &nodes[parent];
        currNode = &nodes[par];
        
      }
      else if( temp->nodeIndex != parent ){

        prevNode = currNode;
        currNode = &nodes[temp->nodeIndex]; 

        int *vis = &visited[temp->nodeIndex];
        int flag = *vis == 1; //if i am going to do dfs on such a node which is already visited once, means my current node is in cycle
        modifiedDFS(); 

        temp->direction = 1;
        // backtraced[currNode->value - 1] = true;
        prevNode = &nodes[parent];
        currNode = &nodes[par];
        if(visited[temp->nodeIndex]>=2 && flag) {
          // cout<<"entering here\n";
          cycle[currNode->value - 1] = true;
        }

      }

    }

    temp = temp->next;
  }
  
  if(recursion_depth == 1){
    int once = 0;
    recursion_depth = 0;
    int i = currNode->value - 1;
    int g = i;
    while(true){
      if( visited[i] == 0 ){
        if( once == 0 ){
              
          BST *bst = trees;
          int j = numTrees - 1;
          while(j--){
            bst = bst->next;
          }
          bst->next = new BST();
          numTrees++;
          once++;
        
        }
        currNode = &nodes[i];
        modifiedDFS();
        currNode = &nodes[g];
      }
      i++;
      i = i%numNodes;
      if(i==g)break;
    }
  }

  recursion_depth--;
  return;
}

void Graph::printResults() {
  int once=0, twice=0, cyc=0;
  for(int i=0; i<numNodes; i++){
    if( visited[i]==1 ){
      once++;
    }
    else
      twice++;
  }
 

  cout<<"No. of Connected component: "<<numTrees<<endl;
  cout<<"No. of nodes visited once: "<<once<<" (";
    int hhh=0;
    for(int i=0; i<numNodes; i++){
      if( visited[i]==1 ){
        hhh++;
        if(hhh>1) cout<<", ";
        cout<<i+1;
      }
    }
  cout<<")"<<endl;
  cout<<"No. of nodes visited twice: "<<twice<<" (";
    hhh=0;
    for(int i=0; i<numNodes; i++){
      if( visited[i]>=2 ){
        hhh++;
        cycle[i] = true;
        if(hhh>1) cout<<", ";
        cout<<i+1;
      }
    }
  cout<<")"<<endl;
     for(int i=0; i<numNodes; i++){
        if( cycle[i]==true ){
          cyc++;
          cout<<" - "<<i+1<<" - "<<endl;
        }
    }
  cout<<"No. of nodes present in any cycle: "<<cyc<<endl;
  BST *bst = trees;
  int j = numTrees ;
  while(j-- && bst){
    bst->printBST("", 0);
    cout<<"\n";
    bst = bst->next;
  }
  return;
}

#endif
