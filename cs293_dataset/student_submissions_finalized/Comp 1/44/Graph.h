#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class TreeNode{ //Struct for BST
public:
  int value;
  TreeNode * left;
  TreeNode * right;
  TreeNode * parent;
  TreeNode(int value){this->value = value; left = nullptr; right = nullptr; parent = nullptr;}
};

class BST { //BST
  // Add your own field and members here
public:
  TreeNode * root;
  BST(){root=nullptr;}
  
  void insert(int value){ //BST insert function
    TreeNode * node = root;
    TreeNode * trailingPointer = node;
    bool left = false;
    if(node!=nullptr){
      while(node!=nullptr){
        trailingPointer = node;
        if(value <= node->value){ node = node->left; left = true;}
        else if(node->value < value){ node = node->right; left = false;}
      }
      node = new TreeNode(value);
      node->parent = trailingPointer;
      if(left == true) trailingPointer->left = node;
      else trailingPointer->right = node;
    }
    else root = new TreeNode(value);
  }

  void printBST(const string& prefix, bool isLeft=false) //function to print BST
  {
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
  // Feel free to use the printBST function used earlier
};

template <typename T>
class listStruct{ //struct for a list
public:
  T value;
  listStruct* next;
  listStruct* prev;
  listStruct(T value){this->value = value; next = nullptr; prev = nullptr;}
};

template <typename T>
class list{ //linked list with stack like functionality
public:
  listStruct<T> * root;
  list(){
    root = nullptr;
  }
  list(int val){
    root = new listStruct<T>(val);
  }
  void push_front(T val){ //pushes the element to the front of the list
    if(root!=nullptr){
      listStruct<T> * element = new listStruct<T>(val);
      listStruct<T> * presentFirst = root; //could be null
      root = element;
      element->next = presentFirst; //could be null
      if(presentFirst!=nullptr) presentFirst->prev = element;
    }
    else root = new listStruct<T>(val);
    // cout << "pushed : " << val << "at: " << root << endl;
  }

  bool Exists(T val){ //if the edge already exists in the list it will return true
    listStruct<T> * itr = root;
    while(itr!=nullptr){
      if(itr->value == val) return true;
      itr = itr->next;
    }
    return false;
  }

};

class Node {
 public:
  int value;

  //start//
  bool firstVisit;
  list<int> *fromNode; //stores the nodes from which a particular node is reached, by default it is zero
  bool secondVisit;
  list<int> *adjacencyList;
  Node(){firstVisit = false; secondVisit = false; adjacencyList = new list<int>(); fromNode = new list<int>(0); fromNode->push_front(0);}
  //end//

  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
  list<int> * Stack;
  int nodesVisitedOnce;
  int nodesVisitedTwice;
  int connectedComponents;
  list<BST> * trees;
  bool newNode;

 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    nodesVisitedOnce = 0;
    nodesVisitedTwice = 0;
    connectedComponents = 0;
    Stack = new list<int>();
    trees = new list<BST>();
    // backtrack = false;

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
      
      

      if(nodes[n1].adjacencyList->Exists(n2+1)) continue;
      // if(!nodes[n2].adjacencyList->Exists(n1)) 
      nodes[n1].adjacencyList->push_front(n2+1);
      nodes[n2].adjacencyList->push_front(n1+1);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;

      /* yet to implement following thing */
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
  void myDFS(int i);
  void printResults();
};

#endif
