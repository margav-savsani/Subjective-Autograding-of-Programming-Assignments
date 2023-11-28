#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class TreeNode{
public:
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  TreeNode(int value){
    val=value;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
  }
};

class BST {
public:
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  TreeNode* root;
  BST(){
    root=nullptr;
  }

  void insert(int val){
    TreeNode* node=new TreeNode(val);
    if(root==nullptr){
      root=node;
    }
    else{
      TreeNode* curr=root;
      while(true){

        if(curr->val<val){
          if(curr->left==nullptr){
            curr->left=node;
            node->parent=curr;
            break;
          }
          else{
            curr=curr->left;
          }
        }

        else{
          if(curr->right==nullptr){
            curr->right=node;
            node->parent=curr;
            break;
          }
          else{
            curr=curr->right;
          }
        }

      }
    }
  }

  void printBST(TreeNode *root, const string& prefix, bool isLeft)
  {
    if( root != nullptr )   {
      cout << prefix;
      
      cout << (isLeft ? "|--" : "|__" );
      
      // print the value of the node
      cout<<root->val;
      cout << endl;
      TreeNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST(root, prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(root, prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }
};

class AdjList{
public:
  int val;
  AdjList* next;
  AdjList(){
    val=0;
    next=nullptr;
  }
  AdjList(int value){
    val=value;
    next=nullptr;
  }
};

class Node {
 public:
  int val,prev[2];
  unsigned short visited;
  bool backtrack;
  AdjList* adjacent;
  Node (){
    prev[0]=0;
    prev[1]=0;
    visited=0;
    backtrack=false;
    val=0;
    adjacent=nullptr;
  }
  bool notfound(int value){
    bool check=true;
    AdjList* adjchecker=adjacent;
    while(adjchecker!=nullptr && check){
      if(adjchecker->val==value){
        check=false;
      }
      adjchecker=adjchecker->next;
    }
    return check;
  }

  ~Node(){
    AdjList* deleter=adjacent;
    while(deleter!=nullptr){
      adjacent=adjacent->next;
      delete deleter;
      deleter=adjacent;
    }
  }
};

class BSTList{
public:
  BST obj;
  BSTList* next;
  BSTList(){
    next=nullptr;
  }
};

class Graph {
  BSTList* bsts;
  int numNodes;
  int numEdges;
  int concomp=0;
  int node1=0;
  int node2=0;
  int nodecyc=0;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    bsts=nullptr;
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes+1];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].val = i+1;
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
      n1++;
      n2++;

      graphFile <<"GOT "<< n1 << " " << n2 << endl;

      if(nodes[n1].notfound(n2)){
        AdjList* adj1=new AdjList(n2);
        AdjList* adj2=new AdjList(n1);
        adj1->next=nodes[n1].adjacent;
        adj2->next=nodes[n2].adjacent;
        nodes[n1].adjacent=adj1;
        nodes[n2].adjacent=adj2;

        graphFile <<"ADDED "<< n1 << " " << n2 << endl;
        countEdges++;

      }
    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
};

#endif