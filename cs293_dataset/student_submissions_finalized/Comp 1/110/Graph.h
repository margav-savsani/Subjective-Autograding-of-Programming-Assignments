#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class TreeNode
{
public:
  int value;
  TreeNode*  left = NULL;
  TreeNode*  right = NULL;
  TreeNode*  parent = NULL;
  // insert other fields and methods as appropriate
  public:
    TreeNode(int value){
      this->value = value;
    }
    TreeNode(){}
};

class BST
{
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  int key;
  TreeNode* root= NULL;

  public:
  BST(){}
  
  BST(int val){
    root = new TreeNode(val);
    this->root = root;
    int key = root-> value;
  }
  void insert(int price){
    root  = insertelement(root,price);
  }

  TreeNode* insertelement(TreeNode* node,int key){     // defining new function for using recursion
    if(node == NULL){
        TreeNode* n = new TreeNode(key);
        node = n;
        return node;
    }
    else if(node->value<key){
        node->right = insertelement(node->right,key);
        node->right->parent= node;
    }
    else{
        node->left = insertelement(node->left,key);
        node->left->parent = node;
    }
    return node;  
  }

  void printBST(const string& prefix, bool isLeft=false)
  {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the TreeNode
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
};



class Node
{
public:
  int value;
  int visit = 0; // indicates the visiting status
  int* adjacency = new int(); //stores indices of adjacent nodes
  int neighbours=0; // counts no of neighbours
  int parent1 =-1; // stores the parent while traversing
  int parent2 =-2; // stores the other parent while traversing if possible
  int num; // stores the number while traversing for finding the no of nodes in cycles
  // insert other fields and methods as appropriate
    
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  int connectedcomp=0;
  Node *nodes;
  int cycl=0;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
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
      bool p = true;
      for(int i=0;i<nodes[n1].neighbours;i++){
        if(nodes[n1].adjacency[i]==n2) p = false; //edge already exists
      }

      if(p){
        int nei1 = nodes[n1].neighbours;  //adding to adjacency of node n1
        nodes[n1].adjacency[nei1] = n2;
        nodes[n1].neighbours++;

        int nei2 = nodes[n2].neighbours; //adding to adjacency of node n2
        nodes[n2].adjacency[nei2] = n1;
        nodes[n2].neighbours++;
        graphFile << n1 + 1 << " " << n2 + 1 << endl; //adding to file 
        countEdges++;
      }

      
    }

    // Add appropriate code as necessary for your implementation
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void DFS(Node* nd,int val,BST* t,int* k); 
  void printResults();
};

#endif
