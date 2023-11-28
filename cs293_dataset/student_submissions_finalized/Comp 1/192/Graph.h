#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

// This class contains the definition of BST Node.
struct BSTNode{

    int value;
    BSTNode * left;
    BSTNode * right;
    BSTNode * parent;

    BSTNode(int value){
      this->value = value;
      this->left = nullptr;
      this->right = nullptr;
      this->parent = nullptr;
    }

};

//This class contains the definition of a Binary Search Tree.
//Only the insert function has been implemented along with appropriate
//constructors / destructors.
class BST {
 
  BSTNode * root;

  public:

    void insert(int value){
      BSTNode * newNode  = new BSTNode(value);
      if(!root){
        root = newNode;
      } else {
        BSTNode * currNode  = root;
        
        while(currNode){
          if (newNode->value >= currNode->value){
            if(!currNode->right){
              currNode->right = newNode;
              newNode->parent = currNode;
              break;
            } else {    
              currNode = currNode -> right;
             }
          } else if(newNode->value < currNode->value){
             if(!currNode->left){
              currNode->left = newNode;
              newNode->parent = currNode;
              break;
            } else {    
              currNode = currNode -> left;
            }
          }     
        }

        
      }

      return;
    }

    BST(){
      this->root = nullptr;
    }

    ~BST(){
      delete root;
    }
  // PrintBST function is as it is the part of the previous labs.

  void printBST(const string& prefix, bool isLeft=false)
  {
      if( root != nullptr )
      {
          cout << prefix;

          cout << (isLeft ? "|--" : "|__" );

          // print the value of the node
          cout << root->value << endl;
          BSTNode *curr = root;
          root = root->left;
          // enter the next tree level - left and right branch
          printBST( prefix + (isLeft ? "│   " : "    "), true);
          root = curr->right;
          printBST( prefix + (isLeft ? "│   " : "    "), false);
          root = curr;
      }
  }
};


// Definition of a ListNode.
// Contains a field for a predecessor so that we can store the node 
//encountered before the current node.
struct ListNode{
    int value;
    int predec;
    ListNode * next;


    ListNode(int value){
      this->value = value;
    }
};


//Node of a graph.
class Node {
 public:
  int value;

  // insert other fields and methods as appropriate

};

// Definition of a graph
// Contains adjacencyList, number of Elements in a cycle and numConnected components as a part of its implementation.
class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  ListNode ** adjacencyList;

  int numInCycle = 0;
  int numConnected = 0;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    adjacencyList = new ListNode * [nNodes];

    for(int i = 0; i < numNodes; i++){
        adjacencyList[i] = NULL;
    }
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

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      ListNode* currptr = adjacencyList[n1];

      

      bool found = false;
      // check if the edge is already present in the adjacency list.
      
      while(currptr && !found){
        if (currptr->value == n2 + 1){
          found = true;
        }

        currptr = currptr -> next;
      }
      // If the edge is not present, add it to the adj list of both the vertices.
      if (!found){

        //Adding to the first adj list.
        ListNode * edge1 = new ListNode(n2 + 1);
        edge1->next = adjacencyList[n1];
        adjacencyList[n1] = edge1;


        //Adding to the second adjacency list.
        ListNode * edge2 = new ListNode(n1 + 1);
        edge2->next = adjacencyList[n2];
        adjacencyList[n2] = edge2;

        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;

      }

      
    }

    
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
 
    for (int i = 0; i < numEdges; i++){
      delete adjacencyList[i];
    }
  }


  void modifiedDFS();
  void printResults();
};

#endif
