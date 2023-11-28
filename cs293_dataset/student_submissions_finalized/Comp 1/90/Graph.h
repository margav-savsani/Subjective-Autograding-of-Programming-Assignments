#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

// #include<vector>
#include<cassert>
using namespace std;


// Using the idea of growth arrays
// From the first few weeks of DSA
// when the size of the list 
// is full we double its size
template<typename T> 
class list{

    T* array;
    int cap, strength;
public:
    // Initialising an initial capacity of 1 element
    // and dynamically allocating storage
    list(){
      array = new T[1];
      cap = 1;
      strength = 0;
    } 

    // Adds an element at the end of the list
    void push(T value){
      if(strength == cap){
        //Then grow the array
          T* tmp = new T[2*cap];

          // copying old elements to the new array
          for(int i = 0; i < cap; i++) {
            tmp[i] = array[i];
          }
          // deleting previous array
          delete[] array;
          cap *= 2;
          array = tmp;
      }
      // Inserting the value
      array[strength++] = value;
    }

    // Returns the element at the given index
    T get(int index){
      // Ensuring index within bound
      assert(index < strength);
      return array[index];        
    }

    int size(){ 
      return strength;
    }
};


// Building blocks of a Binary Search Tree
class TreeNode{
  public:
  int value; //value stored in the node
  //following are the pointers to 
  // parent, left and right children
  TreeNode* parent;
  TreeNode* left;
  TreeNode* right;

  //Constructor
  TreeNode(int val){
    parent = right = left = nullptr;
    value = val;
  }
};

// Binary Search Tree
class BST {
public:
  TreeNode* root; //root node of the BST
  void insert(int val); //Insert a new node with value = val
  void printBST(const string& prefix, bool isLeft); //Prints BST

  //Constructor
  BST(){
    root = nullptr;
  }
};

// Building blocks of a graph
class Node {
 public:
  int value; // value stored in a node
  // The adjacency list for the given node
  // contains the pointers to nodes
  // adjacent to this node
  list<Node*> adjacency;
  int visited; // to record the number of times visited
  Node* predecessor; // predecessor node of this node
  bool incycle; // to record whether this node is a part of a cycle

  // Constructor
  Node(){
    visited = 0;
    incycle = false;
    predecessor = nullptr;
  }

  // Returns true if value "val" is present in
  // the adjacency list
  bool present_in_adjacency(int val){
    for(int i=0;i < adjacency.size(); i++){
      if(adjacency.get(i)->value == val) return true;
    }
    return false;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  int numConnectedComp; // Number of connected components
  int numNodesinCycle; // Number of Nodes part of some cycle in the graph
  // vector<BST*> trees;
  // A list to store the pointers
  // to Binary Search Trees of different 
  // connected components of a graph
  list<BST*> trees;
  fstream graphFile;
  Node *nodes;
   
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    numConnectedComp = numNodesinCycle = 0;

    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    // Checking if input is valid
    if(numEdges > (numNodes)*(numNodes-1)/2){
      cout << "Number of edges can't be greater than nC2.\n";
      exit(-1);
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
    // srand(0);
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;

        // Use the code below if you want
        // to insert edges manually
        // cin >> n1 >> n2;
        // n1--;n2--;
      } 
      while (n1 == n2);

      // If n2 is present in adjacency of n1, or vice versa
      // Then ignore this case and iterate the while loop
      // again
      if(nodes[n1].present_in_adjacency(nodes[n2].value)){
        continue;
      }
      // Else add n1 and n2 in the adjacency lists of 
      // each other and increment number of edges
      nodes[n1].adjacency.push(&nodes[n2]);
      nodes[n2].adjacency.push(&nodes[n1]);

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
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  // Performs a DFS with specified modifications
  void DFS(Node* node, BST* tree);
  // Calls the DFS function for differnt connected components
  void modifiedDFS();
  void printResults();
};

#endif
