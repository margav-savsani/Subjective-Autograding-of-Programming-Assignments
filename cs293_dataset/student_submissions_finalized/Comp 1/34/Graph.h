#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
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

class BST
{
  // Add your own field and members here
  // Node *root;
  // Feel free to use the printBST function used earlier
  public:
  int value;
  BST *left;
  BST* right;
  BST* parent;
  BST(int value_){
    left = nullptr;
    right = nullptr; 
    parent = nullptr;
    value = value_;
  }

  void insert(int value){
    BST* root = this;
    while(true){
      if(root->value > value){
        if(root->left == nullptr){
          root->left = new BST(value);
          root->left->parent = root;
          return;
        }
        else root = root->left;
      }
      else{
        if(root->right == nullptr){
          root->right = new BST(value);
          root->right->parent = root;
          return;
        }
        else root = root->right;  
      }
    }
  }
  void printBST(const string &prefix, BST* root, bool isLeft = false)
{
    if (root != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        std::cout << root->value << endl;
        // TreeNode *curr = root;
        // root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), root->left, true);
        // root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), root->right, false);
        // root = curr;
    }
}
};

class Node
{
public:
  int value;
  // insert other fields and methods as appropriate
  bool visit1, visit2;
  int par1, par2, chainpar1, chainpar2;
  // list which stores the adjacent nodes of this node.
  listOfObjects<Node> *adjacent;
  Node()
  {
    visit1 = visit2 = false;
    value = -1;
    adjacent = nullptr;
    par1 = -1;
    par2 = -1;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  // Add appropriate fields as necessary for your implementation
  listOfObjects<BST*>* tree;
  int total_comp;
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
      
      if (isPresent(n1, n2, countEdges)){
        // cout << "Duplicate Found\n";
        continue;
      }
      // below code adds the adjacent node in adjacency list.
      listOfObjects<Node>* iter = nodes[n1].adjacent;
      if(iter == nullptr){
        nodes[n1].adjacent = new listOfObjects<Node>(nodes[n2]);
      }
      else{
        while(iter->next != nullptr)iter = iter->next;
        iter->next = new listOfObjects<Node>(nodes[n2]);
        iter->next->prev = iter;
      }
      iter = nodes[n2].adjacent;
      if(iter == nullptr){
        nodes[n2].adjacent = new listOfObjects<Node>(nodes[n1]);
      }
      else{
        while(iter->next != nullptr)iter = iter->next;
        iter->next = new listOfObjects<Node>(nodes[n1]);
        iter->next->prev = iter;
      }
      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }
    // Add appropriate code as necessary for your implementation
    // total connected components in the graph.
    total_comp = 0;
    // the list of object of tree to store all the tree.
    tree = nullptr;
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
  bool isPresent(int n1, int n2, int total_inserted);
  void DFS(int par,int source, bool start);
  void modifiedDFS();
  void printResults();
};

#endif
