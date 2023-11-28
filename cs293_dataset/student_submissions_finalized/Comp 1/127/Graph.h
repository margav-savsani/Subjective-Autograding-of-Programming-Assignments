#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <map>
#include <list>
#include <vector>
#endif

class Node {
 public:
  int value;
  Node* left;
  Node* right;

  Node() {
    value=0;
  }

  Node(int v) {
    value=v;
    left=nullptr;
    right=nullptr;
  }

};

class BST {
  
  public:
  
    Node* root;

    BST() {
      root=nullptr;
    }

    void insert(int val) {

      Node* new_node = new Node(val);
      Node* search_node=root;

      if(search_node==nullptr){
        root=new Node(val);
        return;
      }

      while(true) {
        if(val<=search_node->value) {
          if(search_node->left==nullptr) {
            search_node->left=new_node;
            break;
          }
          else {
            search_node=search_node->left;
          }
        }
        else {
          if(search_node->right==nullptr) {
            search_node->right=new_node;
            break;
          }
          else {
            search_node=search_node->right;
          }
        }
      }

      return;

    }

    void printBST(Node* root, const string& prefix, bool isLeft) {
      if(root!=nullptr )   {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );
        std::cout << root->value+1;
        std::cout << endl;
        Node* curr = root;
        root = curr->left;
        printBST(root, prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(root, prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
      }
    }

};



class Graph {
  int numNodes;
  int numEdges;
  int numComponents;
  std::vector<BST> BST_list;
  fstream graphFile;

  map<int, int> visited;
  map<int, list<int>> adjacency_list;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    numComponents=0;

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
    bool edge_exists;
    
    while (countEdges < numEdges) {


      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      do {
	      n1 = rand() % numNodes;
	      n2 = rand() % numNodes;
      } while (n1 == n2);

      edge_exists=false;
      for(std::list<int>::iterator it=adjacency_list[n1].begin(); it!=adjacency_list[n1].end(); it++) {
        if(*it==n2) {
          edge_exists=true;
          break;
        }
      }

      if(!edge_exists) {
        adjacency_list[n1].push_back(n2);
        adjacency_list[n2].push_back(n1);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges+=1;
      }

    }

    for(int theta=0; theta<numNodes; theta++) {
      visited[theta]=0;
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
