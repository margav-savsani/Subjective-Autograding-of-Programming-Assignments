#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
class Node {
 public:
  int value;
    
  Node *left;	// Left Child of this Node (NULL, if None)
  Node *right;	// Right Child of this Node (NULL, if None)
  Node *parent;	// The Parent Node, NULL in case of Root
  
    // Constructors
  int val(){return value;};
  Node() : value(0), left(nullptr), right(nullptr), parent(nullptr){}
  Node(int value) : value(value),  left(nullptr), right(nullptr) {}
  Node(int value, Node *leftChild, Node *rightChild, Node *parent) : value(value), left(leftChild), right(rightChild), parent(parent) {}
  // insert other fields and methods as appropriate
};
class BST {
  public:
  Node *root;
  BST():root(nullptr){}
  bool BSTLessThan(Node* leftArg, Node *rightArg) 
  {
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
      bool result = (leftArg->value < rightArg->value);
      return result;
    }
    else {
      
      exit(-1);
    }
  }

  void insert(int n)
  { Node *currNode = root, *parentOfCurrNode = nullptr;
    Node* node;
    node=new Node(n);

    if(root==nullptr)
    {
      root=new Node(n);
      return ;
    }

    
    while (currNode != nullptr) 
    {
      if (BSTLessThan(currNode,node)) 
      {
        
        parentOfCurrNode = currNode;
        currNode = currNode->right;
        
        
      }
      else if (BSTLessThan(node,currNode)) 
      {
        
        parentOfCurrNode = currNode;
        currNode = currNode->left;
        
        
      }
      else // currNode->JourneyCode == JourneyCode
      return ;
      
    }
    if(currNode== nullptr)
    {
      currNode=new Node(n);
      
      if (BSTLessThan(currNode,parentOfCurrNode))
      {
        parentOfCurrNode->left=currNode;
        return;
      }
      else
      {
        parentOfCurrNode->right=currNode;
        return ;
      }
      
    }  
    
  }

  void printPreorder(Node* node)
  {
    if (node == NULL)
        return;
 
    /* first print data of node */
    cout << node->value << " ";
 
    /* then recur on left subtree */
    printPreorder(node->left);
 
    /* now recur on right subtree */
    printPreorder(node->right);
  }     

    // Feel free to use the printBST function used earlier
};

class Graph {
  int numNodes; 
  int numEdges;
  fstream graphFile;
  Node *nodes;
  int connect;
  map<int, list<int> > adj;
  BST* bst;
  int NoOfCycles;
  int NoOfNodesOnce;
  int NoOfNodesTwice;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName){
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()){
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
    bst = new BST[numNodes];
    if (bst == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i+1;
    }
    
    srand(time(0));
    int n1, n2;
    int countEdges = 0;
      
    while (countEdges < numEdges){
      do{
	      n1 = rand() % numNodes;
	      n2 = rand() % numNodes;
      } 
      while (n1 == n2);
      

      if(n1 != n2)
      {
        auto it1 = adj.find(nodes[n1].value);
        list<int> l = it1->second;
        list < int> ::iterator pos;
        pos = find(l.begin() , l.end() , nodes[n2].value);
        if(pos == l.end() )
        {

          adj[nodes[n1].value].push_back(nodes[n2].value);
        }
      }

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
  void DFS(Node node, bool visited1[], bool visited2[]);

  void modifiedDFS();
  void printResults();
};

#endif
