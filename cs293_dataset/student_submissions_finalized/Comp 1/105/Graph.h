#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif
    
struct TreeNode{
    int value;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    int sizeOfTree = 1;
    // Constructors
  
    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyVal) : value(jrnyVal), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyVal, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(jrnyVal), left(leftChild), right(rightChild), parent(parent) {}
};

class BST{
	TreeNode *root;

public:
	BST(){
    root = nullptr;
  };
	//BST(TreeNode *root);
  void printBST(const string& prefix, bool isLeft=false){
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

	bool insert(int value){ 
    if(root == NULL){
        root = new TreeNode(value,NULL,NULL,NULL);
        return true;
    }
    TreeNode *curr = root;
    while(true){
        curr->sizeOfTree++; 

        if(value >= curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(value,NULL,NULL,curr);
                break;
            }
        }else{
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(value,NULL,NULL,curr);
                break;
            }
        }
    }
    return true;
  }
};

class Adjacency {
  public:
    int object;
    Adjacency *next;
    Adjacency *prev;
    Adjacency(int initValue){object = initValue; next = prev = nullptr;}
};

class Node {
 public:
  int value;
  Adjacency *leo;
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
  public:
    int* v;
    Graph(int nNodes, int nEdges, string gFileName) {
      numNodes = nNodes;
      numEdges = nEdges;
      graphFile.open(gFileName, ios::out);
      if (!graphFile.is_open()) {
        cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
        exit(-1);
      }
      v=new int[numNodes];
      for(int i=0;i<numNodes;i++){
        v[i]=0;
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
        bool b=0;
        
        if(nodes[n1].leo==nullptr && nodes[n2].leo==nullptr){
          if(nodes[n1].leo==nullptr){
            nodes[n1].leo = new Adjacency(n2);
          }
          if(nodes[n2].leo==nullptr){
            nodes[n2].leo = new Adjacency(n1);
          }   
          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;
        }     
        else{  
          if(nodes[n1].leo==nullptr){
            nodes[n1].leo = new Adjacency(n2);
          }
          else if(nodes[n1].leo->object==n2)b=1;
          if(nodes[n2].leo==nullptr){
            nodes[n2].leo = new Adjacency(n1);
          }   
          else if(nodes[n2].leo->object==n1)b=1;
          Adjacency *leo1 = nodes[n1].leo;
          Adjacency *leo2 = nodes[n2].leo;
          while(leo1->next!=nullptr){
            leo1=leo1->next;
            if(leo1->object==n2){
              b=1;
              break;
            }
          }
          while(leo2->next!=nullptr){
            leo2=leo2->next;    
            if(leo2->object==n1){
              b=1;
              break;
            }      
          }
          if(b==0){
            leo2->next=new Adjacency(n1);
            leo1->next=new Adjacency(n2);
            graphFile << n1+1 << " " << n2+1 << endl;
            countEdges++;
          }
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
    void DFS(BST *bst,int x,int p);
    void modifiedDFS();
    void printResults();
};

#endif