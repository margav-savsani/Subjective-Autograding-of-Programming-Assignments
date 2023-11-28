#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include<vector>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
struct TreeNode{
    int price;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : price(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice) : price(jrnyPrice), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice),left(leftChild), right(rightChild), parent(parent) {}
};
class BST {
  public:
    TreeNode *root;
    bool insert(int value);
    void printBST(const string &prefix, bool isLeft = false){
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->price << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
};

class Node {
 public:
  int value;
  vector<Node> adjacent;
  int adjacencynumbers=0;
  public:
  bool isincycle=false;
  int isvisited=0;
  bool alreadyexist(Node a){
    for(int i=0;i<adjacencynumbers;i++){
      if(adjacent[i].value==a.value){
        return true;
      }
    }
    return false;
  }
  bool operator<(Node a){
   if(value<a.value){return true;}
   return false;
  }
  void addadjacent(Node a){
    adjacent.push_back(a);
    sort(adjacent.begin(),adjacent.end());
    adjacencynumbers++;
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  BST* tree;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    tree=new BST[nNodes];
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
      if(!nodes[n1].alreadyexist(nodes[n2]))
      {
      graphFile << n1+1 << " " << n2+1 << endl;
      nodes[n1].addadjacent(nodes[n2]);
      nodes[n2].addadjacent(nodes[n1]);
      countEdges++;}
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
  void modifiedDFS(Node a,int r,vector<int> k);
  void modifiedDFS(Node a,Node b,int r,vector<int> k);
  void printResults();
};

#endif
