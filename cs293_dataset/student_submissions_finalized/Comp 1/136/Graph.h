#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include <list>
using namespace std;
#include <iterator>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <time.h>
#include <stack>
#include <vector>
#endif

struct TreeNode{
  int value;	
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
                   
  TreeNode() :value(0), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyCode) :value(jrnyCode), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyCode,TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) :value(jrnyCode), left(leftChild), right(rightChild), parent(parent) {};
};

class BST{
  public:
  TreeNode *root;
  vector<string> result;
  stack<int> *s;
  BST() {root = nullptr; }
  BST(TreeNode *curr_root) {root = curr_root;}
  bool insert(int value)
  {
    struct TreeNode *nodeToInsert = new TreeNode(value, nullptr, nullptr, nullptr);
    struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;   
    if (root == nullptr) {
      root = nodeToInsert;
      return true;
    }
    else {
      while (currNode != nullptr) {
        if (value < currNode->value) {
          parentOfCurrNode = currNode;
          currNode = currNode->left;
        }
        else{
          parentOfCurrNode = currNode;
          currNode = currNode->right;
        }
      }
      if(parentOfCurrNode->value>value){
        parentOfCurrNode->left=new TreeNode(value);
      }
      else{
        parentOfCurrNode->right=new TreeNode(value);
      }
      //cout<<"inserted "<<value<<" at end of "<<parentOfCurrNode->value<<endl;
      return true;
    }
  }
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
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
    else {
      cout << "NULL tree" << endl;
    }
  }
};

bool present_in_list(list<int>* l,int a){
  list<int>::iterator it;
  for(it = l->begin(); it != l->end(); ++it){
    if(*it==a){
     return true;
    }
  }
  return false;
}

class edge{
  public:
  int n1;
  int n2;
  bool directed;
  int direction;
  edge(int n1,int n2){
    direction=-1;
    directed=false;
    this->n1=n1;
    this->n2=n2;
  }
  bool check(int i,int j){
    if((n1==i && n2==j)||(n1==j && n2==i)){
      //cout<<"found  edge between "<<n1+1<<" and "<<n2+1<<" directed towrds "<<direction+1<<endl;
      if(directed){     
        if(direction==j){
          return true;
        }
      }
      else{
        direction=j;
        directed=true;
        return true;
      }
    }
    return false;
  }
};

class Node {
 public:
  int value;
  list<int> *neighbours;
  Node(){
    neighbours=nullptr;
  }
  bool addNeighbour(int a){
    if(neighbours!=nullptr){
      if(!present_in_list(neighbours,a))
      {neighbours->push_back(a);}
      else{return false;}
    }
    else{
      neighbours=new list<int>;
      neighbours->push_back(a);
    }
    return true;
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int* visited;
  Node *nodes;
  list<BST*> *tree;
  int number_of_connected_components;
  list<int> cyclic;
  list<edge*> *edges;
  stack<int>*s=new stack<int>;
  // Add appropriate fields as necessary for your implementation
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    number_of_connected_components=0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }
    tree=new list<BST*>;
    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    visited=new int[numNodes];
    edges=new list<edge*>;
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
      graphFile << n1+1 << " " << n2+1 << endl;
      if(nodes[n1].addNeighbour(n2) && nodes[n2].addNeighbour(n1)){
        //cout<<"edge added between "<<n1+1<<" and "<<n2+1<<endl;
        edges->push_back(new edge(n1,n2));
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
  void DFS(int i,BST *b);
  void printResults();
  int check();
  int number_of_components_visited_once();
  int number_of_components_visited_twice();
  void print_number_of_nodes_in_a_cycle();
  void printBSTs();
  void store_cyclic_elements(stack<int> *s,int i);
  bool check_edge_match(int n1,int n2);
};

#endif
