#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Helper DFS function for modified dfs
void Graph::doDFS(int x, BST *b){

  //updating visited
  visited[x-1]++;

  //traversing all the adjacent vertex
  DLLNode *temp = nodes[x-1].adjacent.head;
  while (temp!=nullptr){
    
    int y = temp->value;

    // which not visited twice and not parent
    if (visited[y-1]<2 && parent[x-1]!=y){
      // inserting node in BST
      b->insert(y);

      // cout<< y << " "<< x << " " << color[y-1] << " " << parent[y-1] << endl;
      
      // updating parent and color for the first time coming to this point/vertex
      if (color[y-1] == 'w'){
        parent[y-1] = x;
        color[y-1] = 'g';
      }
      // recursive call and updating the color of node
      doDFS(y,b);
      color[y-1] = 'b';

    }
    temp = temp->next;
  }

  return;
}

// actual outer loop of modified DFS and counting connected components and printing the BSTs
void Graph::modifiedDFS() {
  int connectedcomp=0;
  for (int i=0; i<numNodes; i++){

    // if node not visited yet then do a dfs on it along with printing the BST and counting the number of connected components
    if (!visited[i]){
      connectedcomp ++;
      BST *b = new BST(i+1);
      color[i]='g';
      doDFS(i+1,b);
      cout << "Connected Component number :- " << connectedcomp << endl;
      b->printBST("");
    }
  }
  cout << "Number of Connected Components :- " << connectedcomp << endl;
  
  return;
}

// same as above just not using the BST
void Graph::DoDFS(int x){
  visited[x-1]++;

  DLLNode *temp = nodes[x-1].adjacent.head;

  while (temp!=nullptr){
    if (color[temp->value-1]=='w'){
      parent[temp->value-1] = x;
      color[temp->value-1]='g';
      DoDFS(temp->value);
      color[temp->value-1]='b';
    }
    else if (color[temp->value-1]=='g' && parent[x-1] != temp->value){
      int curr = x;
      while(curr != temp->value){
        incycle[curr-1]=true;
        curr = parent[curr-1];
      }
      incycle[curr-1]=true;
    }
    temp = temp->next;
  }
  return;
}

void Graph::printResults() {
  int v1 = 0;
  int v2 = 0;
  int c = 0;

  // calculating the number of single and twice visited nodes based on arrays calculated in DFS 
  for (int i=0; i<numNodes; i++){
    if (visited[i]==1){
      v1++;
    }
    else{
      v2++;
    }
  }

  //printing the details
  cout << "Number of nodes visited once :- " << v1 << endl;
  cout << "Number of nodes visited twice :- " << v2 << endl;

  //updating the previous details it case we do a dfs again
  for (int i = 0; i < numNodes; i++) {
    color[i]='w';
    visited[i] = 0;
    incycle[i] = false;
    parent[i] = 0;
  }

  // calculating the number of nodes in cycle based on the array incycle[]
  c=0;
  for (int i=0; i<numNodes; i++){
    if (!visited[i]){     
      DoDFS(i+1);
    }
    if (incycle[i]){
      c++;
    }
  }
  

  cout << "Number of nodes part of a cycle :- " << c << endl;

  return;
}

#endif
