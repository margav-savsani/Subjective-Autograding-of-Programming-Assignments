#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
   


void  Graph::cycle(Node node,bool visited[], int arr[]){
  int a = (node.adjacentlist).size() ;
  static vector<int> v;
  static vector<int>v1;
  visited[node.value-1] = true;
  arr[node.value-1] = 1;
  for(int i = 0 ; i < a; i++){

    if(visited[node.adjacentlist[i]] == false){

     cycle(nodes[node.adjacentlist[i]],visited,arr) ;
     v.push_back(node.adjacentlist[i]);
    }
    else if(visited[node.adjacentlist[i]] == true & node.adjacentlist[i]  == node.value -1 ){
      continue;
    }
    else{
      int l = 0;
      for(int i = 0; i < v.size();i++){
        if(v[i] == node.adjacentlist[i]){
          l = a;
        }
        if(i >= l){
          bool flu = false;
          for(int j = 0 ; j < v1.size(); j++){
            if(v1[j] == v[i]){
              flu = true;
              break;
            }
          }
          if(! flu){
            v1.push_back(v[i]);
          }
        }
      }

    }
  }
  coun += v1.size();
}

void Graph:: DFS(Node &node,BST* tree){

  int a = (node.adjacentlist).size() ;
  for(int i = 0 ; i < a; i++){
    if(nodes[node.adjacentlist[i]].color == 0){
      TreeNode *pt = new TreeNode(nodes[node.adjacentlist[i]].value); 
      
      bool flag = tree->insert(pt);
      
    
      nodes[node.adjacentlist[i]].color = 1;
      DFS(nodes[node.adjacentlist[i]],tree);
    }
    else if(nodes[node.adjacentlist[i]].color == 1){
      
      nodes[node.adjacentlist[i]].color = 2;
      DFS(nodes[node.adjacentlist[i]],tree);
    }
    else {
      continue;
    }
  }
  
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i = 0; i < numNodes; i++){
    nodes[i].color == 0;
  }
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].color == 0){
      nodes[i].color = 1;
      
      BST tree;
      TreeNode* ptr = new TreeNode(nodes[i].value);
      bool flag = tree.insert(ptr);
      DFS(nodes[i], & tree);
      bool visited[numNodes];
      int arr[numNodes];
      for(int i = 0 ; i < numNodes;i++){
      visited[numNodes] = false;
      arr[i] = 0;
      }
     
      cycle(nodes[i],visited,arr);

      numcomponenets++;
      tree.printBST("\n");
  }
   
}
for(int i = 0 ; i < numNodes;i++){
        if(nodes[i].color == 1){
          ov ++;
      }
      else{
        tv++;
      }
  }
}


void Graph::printResults() {
  cout << numcomponenets << endl;
  cout << ov << endl;
  cout << tv << endl;
  cout << coun << endl;

}

#endif
