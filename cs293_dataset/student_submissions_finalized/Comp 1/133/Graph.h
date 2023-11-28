#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// forward declaration
class Node;                                                   // An implementation of graph vertex and of a TreeNode in BST

class list_node {                                             // An implementation of an adjacency_linked_list_node
  public:                                                     
  Node* node;                                                 // Graph vertex
  list_node* next;                                            // pointer to next adjacency_linked_list_node
  list_node(Node* node){this->node = node; next = nullptr;}   // constructor 
};

class adjacency_list{                                         // A linked list which stores the adjacent nodes of a vertex
  public:  
  list_node* adj_nodes = nullptr;                             // head of the linked list
  list_node* tail = nullptr;                                  // tail of the linked list
  adjacency_list(){adj_nodes = nullptr; tail = nullptr;}      // default constructor
  void add(Node* node){                                       // adds a vertex(node) in the list
    if(adj_nodes == nullptr){                                 
      adj_nodes = new list_node(node);
      tail = adj_nodes;
    } else{
      tail->next = new list_node(node);
      tail = tail->next;
    }
  }
  bool is_pre(int value);                                     // checks whether a vertex(node) with the given value is present or not
};

class Node {                                                  // An implementation of a graph vertex and also a BSTnode
 public:
  int value;                                                  // value 0of the node
  Node* right;                                                // right child of the node
  Node* left;                                                 // left child of the node
  Node* parent;                                               // parent of the node
  adjacency_list* adj_list = new adjacency_list();            // adjcency list of the vertex(node)
  Node(){right = nullptr; left = nullptr; parent = nullptr;}  // default constructor
  Node(int value){this->value = value;right = nullptr; left = nullptr; parent = nullptr;}  //constructor
  ~Node(){}
  // insert other fields and methods as appropriate
};

bool adjacency_list::is_pre(int value){                       // implementation of a member function of the adjacency_list class
  list_node* temp=adj_nodes;
  while(temp != nullptr){
    if(temp->node->value == value) return true;               // return true if a node with the given value is present
    temp = temp->next;
  }
  return false;                                               // else returns false
}

class BST {                                                   // An implementation of binary search tree
  // Add your own field and members here
  public:
  Node* root;                                                 // root of the binary search tree
  BST(Node* root){this->root = root;}                         // constructor
  void insert(int value);                                     // insert a node with the given value in the tree
  
  void recursiveDelete(Node *currNode) {                      // deletes all the nodes in the tree
    if (currNode != nullptr) {
      Node *leftChild = currNode->left;
      Node *rightChild = currNode->right;    
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }    
    return;
  }
  ~BST(){recursiveDelete(root);}                              // destructor
  // Feel free to use the printBST function used earlier
};

void printBST(const string& prefix, bool isLeft, Node* r_node);  // prints a tree with the root as the given node

class Graph {
  int numNodes;                                               // number of vertices in the graph
  int numEdges;                                               // number of edges in the graph
  fstream graphFile;                                          
  Node *nodes;                                                // vertices(nodes) of the graph
  int n_comp=0;                                               // number of components of the graph
  int n_cycl=0;                                               // number of vertices(nodes) which are in a cylce
  int ones=0;                                                 // number of nodes which are visited once 
  int twice=0;                                                // number of nodes which are visited twice
  int counter = 0;                                            // a time counter 
  int* visited;                                               // an array which store the visit freq of each node
  int* arrv;                                                  // an array which stores the minimum arrival time of each node
  bool* coun_cycl;                                            // an array which a node in a cycle is counted or not
  int** parents;                                              // a 2d which stors the parents of each node(atmost two parents are possible) 
  adjacency_list* root_list = new adjacency_list();           // stores the root of each new binary tree created
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {           // constructor
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;
    
    parents = new int*[numNodes];
    visited = new int[numNodes];
    arrv = new int[numNodes];
    coun_cycl = new bool[numNodes];
    nodes = new Node[numNodes];
    if (nodes == nullptr || visited == nullptr || parents == nullptr || arrv == nullptr || coun_cycl == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {                      
      nodes[i].value = i+1;                                   // assign values to the nodes
      visited[i] = 0;                                         // all are not visited initially
      parents[i] = new int[2];                                // parents array
      parents[i][0]=0; parents[i][1]=0;                       // parents of each node are null
      arrv[i] = 2*numNodes;                                   // assign max possible value for each node
      coun_cycl[i] = 0;                                       // all are not counted initially
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
        //cin>>n1;
        //cin>>n2;
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

      if(nodes[n1].adj_list->is_pre(n2+1)) continue;          // if n1+1,n2+1 is already an edge, the continue
      else{
        nodes[n1].adj_list->add(&nodes[n2]);                  // else add node n2+1 to adjacency list of n1+1
        nodes[n2].adj_list->add(&nodes[n1]);                  // add node n1+1 to adjaceny list of n2+1
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
    delete[] visited;
    delete[] arrv;
    delete[] coun_cycl;
    delete[] parents;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  int DFS(Node *node,BST* tree);                              // returns the arrival time of the deepest back edge
  void modifiedDFS();                                         // runs the dfs until all the nodes are visited
  void printResults();                                        // prints required the result
};

#endif
