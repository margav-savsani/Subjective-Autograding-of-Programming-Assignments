#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif



// Add code as appropriate for your implementation
// void Graph::modifiedDFS() {
//   return;
// }

void Graph::printResults() {
  // printBinaryTree(tree->root,"",true);
  for (int i = 0; i < numNodes; i++)
  {
    if (treeList[i]->root!=nullptr)
    {
      printBinaryTree(treeList[i]->root,"",true);
    }
    cout << endl;
    
  }

  int count2 = 0; 
  int count1 = 0; 
  int countC = 0; 
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 2)
    {
      count2++;
    }

    if (visited[i]==1)
    count1++;

    if(treeList[i]->root != nullptr){
      countC++;
    }
  }

  cout << "once visited " << count1;
  cout << endl;
  cout << "twice visited " << count2; 
  cout << endl;
  cout << "number of nodes in cycles " << count2;
  cout << endl;
  cout << "connected component " << countC;
  cout << endl;

  return;
}

// int main(){
  // Graph g = Graph(10,12,"log.txt");
// }

int allVisited(int* visited,int numNodes){
  for(int i = 0; i < numNodes; i++){
    if (visited[i] == 0)
    {
      return i;
    } 
  }

  return -1;
}
void Graph::modifiedDFS(){
  int currVisited = allVisited(visited,numNodes);
  // treeList[currVisited] = new BST();
  while (currVisited != -1)
  {
    // cout << currVisited << endl;
    specialDFS(currVisited,treeList[currVisited]);
    currVisited = allVisited(visited,numNodes);
  }
   
}

void Graph::printBinaryTree(Node *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->value;
    cout << endl;
    Node *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    // cout << "NULL tree" << endl;
  }
}

void printList(int* l){
  for(int i = 0; i < 20; i++){
    cout << l[i] << ", ";
  }
  cout << endl;
}



void Graph::specialDFS(int node,BST* tree,int del ){
  // Node* ptr = getNode(node)
  visited[node] += 1;
  Node* temp = new Node(node);
  tree->insert(temp);
  bool temp_del = -1;

    // cout << node << " ";

  // int minNode = -1; 

  int temp_var = -1;
  for (int i = 0; i < numNodes; i++)
  {
    if(adj[node][i] == 1){
      temp_var = i;
    }
  }

  if (temp_var == -1 && del != -1)
  {
    adj[node][del] = 0;
  }
  

  
  for(int i = 0; i < numNodes; i++){

    if (adj[node][i] == 1 && visited[i] < 2)
    {
      specialDFS(i,tree,node);
    }

  }

  

  // cout << endl;
  // if(minNode == -1) return;
  // if(visited[minNode] == 2) return;
  return;

}

#endif
