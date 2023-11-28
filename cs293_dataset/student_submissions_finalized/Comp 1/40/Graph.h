#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>       //added as I have used vectors

struct TreeNode{
    int value;       //value of treenode (BST)
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)

    // Constructors
  
    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
    TreeNode* root;
public:
    //constructors
    BST() {
      root = nullptr; 
    }
    BST(TreeNode *root) { 
      this->root=root; 
    }
    bool insert(int value){   //insert function for BST done in lab3
      TreeNode *x;
      TreeNode *y;
      x = root;
      y = NULL;
      while (x != NULL){      //iterating down till we find the correct location of value to be inserted
        y = x;
        if (value < x->value) x = x->left;
        else x = x->right;
      }
      if (y == NULL) root = new TreeNode(value);   //if empty BST
      else if (value < y->value) y->left = new TreeNode(value);   //adding nodes
      else y->right = new TreeNode(value); 
      return false;                            //holds no significance as such
    }

    void printBST(const string &prefix, bool isLeft = false){   //printBST function taken directly as provided
    if (root != NULL){
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = curr->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;   //value of node
  Node *left;	// Left Child of this Node (NULL, if None)
  Node *right;	// Right Child of this Node (NULL, if None)
  //constructors
  Node() : value(0), left(nullptr), right(nullptr) {}
  Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  
  //NOTE: I have represented nodes by an int instead of Node class like nodes[i] is represented by integer i and has value i+1
  //This has no effect on output its just to simplify things 

  vector<int> *adj;    //This is an adj array of vectors (adjacency list).    e.g. adj[4] is a vector containing all nodes adjacent to 4
  int *count;          //array representing number of times a node was visited
  int components;      //number of components in graph
  int visitedonce;     //number of nodes visited once
  int visitedtwice;    //number of nodes visited twice
  int nodesincycle;    //number of nodes in a cycle
  vector<BST> vecofbst; //vector of BSTs of different components of graph
  int *predecessor;     //predecessor array for nodes
  bool *ifcycle;        //boolean array representing if node is part of a cycle or not

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    components = 1;
    visitedonce = visitedtwice = nodesincycle = 0;  //initializing...
    adj = new vector<int>[nNodes];
    count = new int[nNodes];
    predecessor = new int[nNodes];
    ifcycle = new bool[nNodes];
    for(int i=0; i<nNodes; i++){
      count[i] = 0;
      predecessor[i] = -1;
      ifcycle[i] = false;
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

      if (std::find(adj[n1].begin(), adj[n1].end(), n2) == adj[n1].end()){    
        //as we are simultaneously updating adjacency list of both when creating edge, we just need to check if one is present in others' list
          adj[n1].push_back(n2);  
          adj[n2].push_back(n1);
          //we push back to both adjacency list as they are both adjacent to each other
          graphFile << n1+1 << " " << n2+1 << endl;         //writing to file
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

  void ourDFS(Node v);

};


#endif
