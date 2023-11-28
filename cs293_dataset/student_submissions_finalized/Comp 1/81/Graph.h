#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include<list>
#include<vector>
#endif

struct TreeNode{
   	int value;	//value
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    TreeNode(int key){
      left = nullptr;
      right = nullptr;
      value = key;
      parent = nullptr;
    }
};

class BST {
  public:

  TreeNode *root;

  BST();

  void insert(int value);
  void printBST(const string& prefix, bool isLeft);
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  list<int> adjacency;
  int visited ;
  int parent;
};

class Graph {
  int numNodes;
  int numEdges;
  int connectedcomps=0;
  int cyclenumber;
  list<BST*> trees;
  fstream graphFile;

  Node *nodes;
  Node *nodes_c;
  public:

  static bool cmp(const Node& lhs, const Node& rhs)
  {
  return (lhs.value > rhs.value) ;
  }
  
  Graph(int nNodes, int nEdges, string gFileName) {
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
    nodes_c = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      nodes[i].visited = 0;
      nodes_c[i].value = i+1;
      nodes_c[i].visited = 0;
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
  ;
      if(nodes[n1].adjacency.empty() || nodes[n2].adjacency.empty()){
        nodes[n1].adjacency.push_back(n2+1);
        nodes[n2].adjacency.push_back(n1+1);
        nodes_c[n1].adjacency.push_back(n2+1);
        nodes_c[n2].adjacency.push_back(n1+1);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
      else {
        bool S_time = false;
        list<int>::iterator it;
        for(it = nodes[n1].adjacency.begin();it != nodes[n1].adjacency.end();++it){
          if(*it == (n2+1)){
            S_time = true;
            break; }
        }
        if(!S_time){
          nodes[n1].adjacency.push_back(n2+1);
          nodes[n2].adjacency.push_back(n1+1);
          nodes_c[n1].adjacency.push_back(n2+1);
          nodes_c[n2].adjacency.push_back(n1+1);
          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;}
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
  void cycle_checker(Node &node,int p,int par[]);
  void dfs(Node &node,BST* Tree,int parent);
  void modifiedDFS();
  void printResults();
};

#endif
