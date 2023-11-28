#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;
class treenode{
  public:
  int value;
  treenode *left,*right,*parent;
  treenode(int v){
    left=right=parent=nullptr;
    value=v;
  }
};
class BST {
  public:
  treenode* root;
  treenode* search(treenode* root, int m)
  {
    // Base Cases: root is null or value is present at root
    if (root == NULL || root->value == m)
       return root;
    
    // Key is greater than root's value
    if (root->value < m)
       return search(root->right, m);
 
    // Key is smaller than root's value
    return search(root->left, m);
  }
  void insert(treenode* root, int key)
  {
    treenode* node = new treenode(key);
    if (root==nullptr) {
        root = node;
        return;
    }
    treenode* prev = NULL;
    treenode* temp1 = root;
    while (temp1) {
        if (temp1->value > key) {
            prev = temp1;
            temp1 = temp1->left;
        }
        else if (temp1->value < key) {
            prev = temp1;
            temp1 = temp1->right;
        }
    }
    if (prev->value > key)
        prev->left = node;
    else
        prev->right = node;
  }
  // Feel free to use the printBST function used earlier
  void printBST(const string& prefix, bool isLeft=false)
  {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->value<<')' << endl;
        treenode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  }
};
class Node {
 public:
  int value;
};
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = nullptr;}
  // Destructor
  ~listOfObjects() {;}
};
class AdjacencyList {
public:
  listOfObjects<Node *> *adjacent;

  AdjacencyList() {
    adjacent = nullptr;
  }

  ~AdjacencyList() {
    listOfObjects<Node*> *currStnConnInfo;
    listOfObjects<Node*> *delStnConnInfo;

    currStnConnInfo = adjacent;
    while (currStnConnInfo != nullptr) {
      delStnConnInfo = currStnConnInfo;
      currStnConnInfo = currStnConnInfo->next;
      delete delStnConnInfo->object;
      delete delStnConnInfo;
    }
  }
};
class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  // Add appropriate fields as necessary for your implementation
  
 public:
  AdjacencyList* adj= new AdjacencyList[numNodes];
  int *visited=new int[numNodes];
  int* reset(int *a){
    for(int i=0;i<numNodes;i++){
      a[i]=0;
    }
  }
  Graph(int nNodes, int nEdges, string gFileName) {
    visited=reset(visited);
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

    srand(0);
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
      listOfObjects<Node*>*temp1=adj[n1].adjacent;
      do{
        if(temp1->object!=&nodes[n2]){
          temp1=temp1->next;
        }
        else break;
      }while (temp1->next!=nullptr);
      listOfObjects<Node*>*temp2=adj[n2].adjacent;
      do{
        if(temp2->object!=&nodes[n1]){
          temp2=temp2->next;
        }
        else break;
      }while (temp2->next!=nullptr);
      if(temp2->object!=&nodes[n1] && temp1->object!=&nodes[n2])
      {
        adj[n1].adjacent->next->object=&nodes[n2];
        adj[n2].adjacent->next->object=&nodes[n1];
        graphFile << n1+1 << " " << n2+1 << endl;
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
  void printResults();
  void dfs(int start, int *visited,BST tree);
};

#endif
