#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
struct TreeNode{
  public:
  int value;
  TreeNode *left;	// Left Child of this Node (NULL, if None) in BST
  TreeNode *right;	// Right Child of this Node (NULL, if None) in BST
  TreeNode *parent;	// parent of this node in BST
  TreeNode(int v, TreeNode *left, TreeNode *right, TreeNode *parent){
    value = v;
    this->left=left;
    this->right=right;
    this->parent=parent;
  }
};

class BST {
  TreeNode *root=nullptr;
	vector<string> result;

  public:
  BST(){root = NULL;}
  BST(TreeNode *root){this->root = root;}

  void insert_node(int value){
    if(root == NULL){
      root = new TreeNode(value,NULL,NULL,NULL);
    }
    TreeNode *current = root;
    while(true){
      if(value > current->value){
        if(current->right!=NULL){
          current = current->right;
        }
        else{
          current->right = new TreeNode(value,NULL,NULL,current);
          break;
        }
      }
      else{
        if(current->left!=NULL){
          current = current->left;
        }
        else{
          current->left = new TreeNode(value,NULL,NULL,current);
          break;
        }
      }
    }
    return;
  }
  void printBST(const string& prefix, bool isLeft);
};

void BST::printBST(const string& prefix, bool isLeft=false){
  if( root != nullptr ){
    cout << prefix;
    cout << (isLeft ? "|--" : "|__" );
    // print the value of the node
    cout << root->value << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST( prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST( prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

class Node {
  public:
  int value;
  Node * adjacent_nodes;
};

int comp=0;
bool c1=false;
bool c2=false;
//bool con=false;
  
class Graph {
  public:
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  map<int, int> visited;
  map<int, list<int> > adj;
  //tuple <int, int, bool> route;
  //iterating through the created map to print out the key and value pairs from the map
  BST b;
  void travel(int v,int par){
    cout<<v<<" ";
    visited[v]++;
    b.insert_node(v);
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
      if((visited[*i]==0 || visited[*i]==1) && (*i)!=par ){
        //cout<<*i<<" "<<par<<endl;
        travel(*i,v);
      }
    }
    return;
  }
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    for(int i=1;i<=numNodes;i++){
      if(visited.find(i) == visited.end()){
        visited[i] = 0;
      }
    }

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
   // cout<<"1"<<endl;
   
    // cout<<"11"<<endl;
    for (auto v : adj[n1+1]){
      if(v==n2+1){c1=true;}
    }
    for (auto v : adj[n2+1]){
      if(v==n1+1){c2=true;}
    }
     
    // cout<<"111"<<endl;
     if(!(c1||c2)){
      //cout<<"iugyftd"<<endl;
        adj[n1+1].push_back(n2+1);
        adj[n2+1].push_back(n1+1);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
    //cout<<"jjjjjjjjj"<<endl; 
    }
    
 // cout<<"llllllll"<<endl;
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }
  
  void modifiedDFS();
  void printResults();
};

#endif
