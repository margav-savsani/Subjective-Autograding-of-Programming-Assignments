#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode{
  int value;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  TreeNode(int value){
    this->value = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

class BST {
  // Add your own field and members here
  public:
    TreeNode *root;
    BST();
    BST(TreeNode *root);
    void insert(int value);
    void printBST(const string& prefix, bool isLeft );
  // Feel free to use the printBST function used earlier
};

struct ListOfTrees{
  public:
    BST* tree;
    ListOfTrees* next;
    ListOfTrees* prev;
    ListOfTrees(BST* tree){
      this->tree = tree;
      next = nullptr;
      prev = nullptr;
    }
};

class results{
  public:
    int numConnectedComponents;
    int visitedOnce;
    int visitedTwice;
    int numInCycle;
    ListOfTrees* lstTrees;
};


class adjacencyList{
  public:
    int neighbourValue;
    adjacencyList* next;
    adjacencyList* prev; 
    adjacencyList(int nbr){
      this->neighbourValue = nbr;
      next = nullptr;
      prev = nullptr;
    }
};

class Node {
 public:
  int value;
  adjacencyList* adjacents;
  int tracker;
  Node(){
    value = -1;
    adjacents = nullptr;
    tracker = 0;
  }
  // insert other fields and methods as appropriate
};


class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  results result;
  Node *nodes;
  int numConnectedComponents;
  int *componentNumbers;
  ListOfTrees* lstTrees;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    lstTrees = nullptr;
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

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      int shouldContinue = 0;
      adjacencyList* n1Adjacents=nodes[n1].adjacents, *n2Adjacents = nodes[n2].adjacents;

      if(n1Adjacents == nullptr){
        nodes[n1].adjacents = new adjacencyList(n2);
        // //!!
        // cout<<"Inserted in adjacency list of n1"<<endl;
        // //!!
      }
      else{
        while(n1Adjacents->next!=nullptr){
          if(n1Adjacents->neighbourValue==n2){
            shouldContinue = 1;
            break;
          }
          n1Adjacents = n1Adjacents->next;
        }
        if(n1Adjacents->neighbourValue==n2){
            shouldContinue = 1;
            continue;
        }
        n1Adjacents->next = new adjacencyList(n2);
        // //!!
        // cout<<"Inserted in adjacency list of n1"<<endl;
        // //!!
      }

      if(shouldContinue==1) continue;
      
      if(n2Adjacents == nullptr){
        nodes[n2].adjacents = new adjacencyList(n1);
        // //!!
        // cout<<"Inserted in adjacency list of n2"<<endl;
        // //!!
      }
      else{
        while(n2Adjacents->next!=nullptr){
          n2Adjacents = n2Adjacents->next;
        }
        n2Adjacents->next = new adjacencyList(n1);
        // //!!
        // cout<<"Inserted in adjacency list of n2"<<endl;
        // //!!
      }

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }

    // Add appropriate code as necessary for your implementation
    numConnectedComponents = 1;
    componentNumbers = new int[numNodes];
    for(int i = 0;i<numNodes;i++){
      componentNumbers[i] = 0;
    }
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
  void DFS(int i, int *visited, int *inCycle, BST* tree, int* parent1, int* parent2);
};

#endif
