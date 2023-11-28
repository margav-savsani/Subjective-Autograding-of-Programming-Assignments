#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include <string>
#ifndef STD_HEADERS_H
#include<list>
#include<iterator>
#include "std_headers.h"
#endif
class TreeNode{
  public:
    int value=0;	// node value
    
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    
    // Constructors
  
    TreeNode() :value(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) :  value(val), left(nullptr), right(nullptr) {}
    TreeNode(int val,  TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) :  value(val), left(leftChild), right(rightChild), parent(parent) {}
    ~TreeNode() {}
};
class Node{
  public:
  int visited;
  int value;
  int count;
  ~Node() {}
};

class BST {

  private:
  TreeNode *root;
  public:
  
	BST(){root = NULL; }
	BST(TreeNode *root){this->root = root; }

  bool insert(int val){
    
    if(root == NULL){
        root = new TreeNode(val);
        return true;
  }
  TreeNode *curr = root;
  while(true){
    if(val > curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(val,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(val,NULL,NULL,curr);
                break;
                
            }
        }
    }
    return true;
  }
  void  printBST(const string& prefix,  bool isLeft=false){
    if( root != nullptr )
    {
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
  
};
  // Add your own field and members here

  // Feel free to use the printBST function used earlier




class Graph {
 
  int numNodes;
  int numEdges;
  fstream graphFile;
  int ** adjacent;
  Node* nodes;
  int *arr;
  BST* bst;
  int con;
  // Add appropriate fields as necessary for your implementation
  
 public:
  
  Graph(int nNodes, int nEdges, string gFileName) {

    numNodes = nNodes;
    numEdges = nEdges;
    con=0;
    graphFile.open(gFileName, ios::out);

    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }
    arr=new int[numNodes];
    
    adjacent = new int*[numNodes];
    
      for( int i=0; i< numNodes; i++){
        adjacent[i] = new int(numNodes);
        for( int j=0; j< numNodes; j++){
          adjacent[i][j] = 0;
        }
      }
    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      nodes[i].visited=0;
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
      
      
      
      // for(it2 = adj[n1+1].begin(); it2 != adj[n1+1].end(); ++it2) {
      //   if (*it2!=n2+1 && *it1!=n1+1 ){
      //     cout<<*it1<<"k"<<*it2<<endl;
      //     graphFile << n1+1 << " " << n2+1 << endl;
      //     countEdges++;
          
      //   }
      // }
      
      if (adjacent[n1][n2]==0 && adjacent[n2][n1]==0){
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
      adjacent[n1][n2]=1;
      adjacent[n2][n1]=1;
      
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
  void print();
  void DFS(int p);
  void modifiedDFS();
  void printResults();
  
  
  
};

#endif
