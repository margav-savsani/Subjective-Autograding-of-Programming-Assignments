#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct TreeNode{
  int value;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;

  TreeNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
  TreeNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
  TreeNode(int val, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}
}; 

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class BST {
  // Add your own field and members here
  TreeNode *root;

  public:
    BST(){
      root=nullptr;
    }
    BST(TreeNode *root);
    void printBST(const string& prefix, bool isLeft);
    void getBst(const string& prefix, bool isLeft);
    void clearResult();

    bool insert(int value);
    bool find(int value);
    bool remove(int value);
  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  listOfObjects<int>* adjacencyList = nullptr;
  int numOfVisits;
  listOfObjects<int>* prevNode;
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  int numComponents=0;
  fstream graphFile;
  bool* isCycle = new bool[numNodes];
  listOfObjects<int>* path;

  Node *nodes;
  BST* tree;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    tree=nullptr;
    path=nullptr;
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
      nodes[i].numOfVisits=0;
      nodes[i].prevNode=nullptr;
      isCycle[i]=false;
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


      if(nodes[n1].adjacencyList){
        listOfObjects<int>* temp= nodes[n1].adjacencyList;
        bool found=false;
        while(true){
          if(temp->object==n2){
            found=true;
            break;
          }
          else{
            if(temp->next){
              temp=temp->next;
            }
            else{
              break;
            }
          }
        }
        if(found){
          continue;
        }
        else{
          temp->next=new listOfObjects<int>(n2);
          temp->next->prev=temp;
        }
      }
      else{
        nodes[n1].adjacencyList=new listOfObjects<int>(n2);
      }

      if(nodes[n2].adjacencyList){
        listOfObjects<int>* temp=nodes[n2].adjacencyList;
        while(true){
          if(temp->next){
            temp=temp->next;
          }
          else{
            break;
          }
        }
        temp->next=new listOfObjects<int>(n1);
        temp->next->prev=temp;
      }
      else{
        nodes[n2].adjacencyList=new listOfObjects<int>(n1);
      }

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
  BST * DFS(int index,int index_parent, bool visited_once[], bool visited_twice[]);
  void printResults();
  void modifiedDFSfromNode(int n);
};

#endif
