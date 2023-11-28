#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include <vector>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class TreeNode {
  public:
  int value;
  TreeNode* right;
  TreeNode* left;
  TreeNode* parent;
  TreeNode(int val){
    value = val;
  }

};

class Node {
 public:
  int value;
  int color;
  vector <int> adjacentlist;
  
 
  // insert other fields and methods as appropriate
};

class BST {


TreeNode * root = nullptr;
public:
bool insert(TreeNode *node){
 
  if(root == nullptr){
    root = new TreeNode(node->value);
    root->parent = nullptr;
    root->right = nullptr;
    root->left = nullptr;
    
    return true;
  }
  TreeNode * curr = root;
  
    while(true){
       
       
        // Moving to the right, if value is greater
        if(node->value >= curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
             
                curr->right = new TreeNode(node->value);
                curr->right->parent = curr;
                curr->right->right = nullptr;
               
                curr->right->left = nullptr;
               
                return true;
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(node->value);
                curr->left->parent = curr;
                curr->left->right = nullptr;
                curr->left->left = nullptr;
                return true;
                break;
                
            }
        }
    } 
  }

void printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->value<<')' << endl;
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

  

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int numcomponenets = 0;
  int ov = 0;
  int tv = 0;
  int coun = 0;


  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
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
      bool flag = false;
      for(int i = 0 ; i < (nodes[n1].adjacentlist).size(); i++){
        if(nodes[n1].adjacentlist[i] == n2){
          flag = true;
          break;
        }
      }
      if(! flag ){
        nodes[n1].adjacentlist.push_back(n2);
        nodes[n2].adjacentlist.push_back(n1);
      }
      else{
        continue;
      }
      
      

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
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
  void DFS(Node &node,BST* tree);
  void cycle(Node node,bool visited[], int arr[]);
};

#endif
