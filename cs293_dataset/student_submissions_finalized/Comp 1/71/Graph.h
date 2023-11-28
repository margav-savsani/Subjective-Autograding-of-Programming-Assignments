#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
using namespace std;


class TreeNode{
  public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int n){
    value=n;
    left=nullptr;
    right=nullptr;
  }

};
void printBinaryTree(TreeNode *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->value;
    cout << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│  " : "   "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│  " : "   "), false);
    root = curr;
  }
  // else {
  //   cout << "NULL tree" << endl;
  // }
}

class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  TreeNode* root;
  public:
  BST(){
    root=nullptr;
  }
  void insert(int n){
    if(root==nullptr) root=new TreeNode(n);
    else{
      TreeNode* cur=root;
      while(true){
        if(cur->value > n) {
          if(cur->left==nullptr) {
            cur->left=new TreeNode(n);
            break;
          }
          else cur=cur->left;
        }
        else{
          if(cur->right==nullptr) {
            cur->right=new TreeNode(n);
            break;
          }
          else cur=cur->right;
        }
      }
    }
  }

  void print(){
    printBinaryTree(root, "", false); return;
  }

};

class Node {
 public:
  int value;
  vector<Node*> AdjList;
  // insert other fields and methods as appropriate

  bool is_adj(Node* n){
    for(int i=0; i<AdjList.size(); i++){
      if(AdjList[i]==n){
        return true;
        break;
      }
    }
    return false;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node **nodes;
  int *conCompo;
  int numConnCompo;
  int *visited;
  int *inCycle;
  vector<int> dfsStack;
  vector<BST*> allBST;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    numConnCompo=0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    visited= new int[numNodes];
    inCycle = new int[numNodes];
    conCompo= new int[numNodes];
    nodes = new Node*[numNodes];

    if (conCompo == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      visited[i]=0;
      inCycle[i]=0;
      conCompo[i]=0;
      nodes[i]= new Node();
      nodes[i]->value = i+1;
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

      if(!nodes[n1]->is_adj(nodes[n2])){
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
        nodes[n1]->AdjList.push_back(nodes[n2]);
        nodes[n2]->AdjList.push_back(nodes[n1]);
      }
    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    delete[] conCompo;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  void dfs(int j, BST *b);
};

#endif
