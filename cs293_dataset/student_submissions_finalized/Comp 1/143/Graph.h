#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include <string>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  listOfObjects(T initValue) {object = initValue; next= nullptr;prev = nullptr;}
  ~listOfObjects() {;}

};



class Node {
 public:
  int value; //value stored in the node
  Node *left; //left used in BST
  Node *right;//right used in BST
  Node *parent;//parent used in BST
  int visited; //counts how many times node has been visited
  listOfObjects<Node*>*adjacency; //adjacency list of a node
  Node(int value_copy,Node *left_copy,Node *right_copy,Node *paren_copy){
    value = value_copy;
    left = left_copy;
    right =right_copy;
    parent = paren_copy;

  }
  Node(){;}
};



class BST {
  
  Node *root;
  public:
    void insert(int v){ //inserts the node with value v into BST
      if(root == nullptr){
        root = new Node(v,nullptr,nullptr,nullptr);
      }
      else{
        Node *root_copy = root;
        while(root_copy!=nullptr){
          if(v<=root_copy->value){
            if(root_copy->left==nullptr){
              root_copy->left = new Node(v,nullptr,nullptr,root_copy);
              return;
            }
            else{
              root_copy = root_copy->left;
            }
          }
          else{
            if(v>root_copy->value){
              if(root_copy->right == nullptr){
                root_copy->right = new Node(v,nullptr,nullptr,root_copy);
                return;
              }
              else{
                root_copy = root_copy->right;
              }
            }
          }
        }
      }
    }
   void printBST(const string& prefix, bool isLeft=false){ //used for printing the BST
     if( root != nullptr )
      {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value<< endl;
        Node *curr = root;
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
  
  int numNodes; //number of nodes in the graph
  int components = 0; //number of connected components
  int once_visited = 0; //number of nodes visited once
  int twice_visited = 0; //number of nodes visited twice
  int numEdges; //number of edges in the graph
  int incycle = 0; //number of nodes in a cycle
  fstream graphFile;

  Node *nodes;
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
      nodes[i].adjacency = new listOfObjects<Node*>(&nodes[i]);
      nodes[i].visited = 0;
    }
    
    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    bool exist = false;
    while (countEdges < numEdges) {
      do {
	        n1 = rand() % numNodes;
	        n2 = rand() % numNodes;
      } while (n1 == n2);
        listOfObjects<Node*>*node_copy = nodes[n1].adjacency;
        while(node_copy->next!=nullptr){
          if(node_copy->object == &nodes[n2]){ //checking if already the edge is existing or not
            exist = true; 
            break;
          }
          else{
            node_copy =  node_copy->next;
          }
        }
        if(node_copy->object == &nodes[n2]){
            exist = true;
        }

        if(!exist){ //if does not exist add the edge
          node_copy->next = new listOfObjects<Node*>(nodes[n2].adjacency->object);
          node_copy->next->prev = node_copy;
          listOfObjects<Node*>*node_copy1 = nodes[n2].adjacency;
          while(node_copy1->next!=nullptr){
            node_copy1 = node_copy1->next;
          }
          node_copy1->next = new listOfObjects<Node*>(nodes[n1].adjacency->object);
          node_copy1->next->prev = node_copy1;
          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;
          
        }
        exist = false;
       }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  

  void modifiedDFS();
  void printResults();
  void DFS(int vertex);
  bool pop(int vertex1,int vertex2);
  int size(int vertex);
};

#endif
