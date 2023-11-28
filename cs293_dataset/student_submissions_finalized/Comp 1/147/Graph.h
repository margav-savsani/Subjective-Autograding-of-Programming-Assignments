#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <vector>
#include <set>
#endif
using namespace std;

// helper classes bst (30L - written with spaces) and ll (11L)

// just a linear bst (a dll would be a better analogy since parent ~ prev ptr)
class ll {
  typedef ll* ptr;
public:
  int _value;
  ptr next = nullptr;
  ll(int value): _value(value){}
  void insert(int value){
    if (!next) next = new ll(value); else next->insert(value);
  }
  ~ll(){ delete next; }
  operator int(){ return _value; }
};

class BST {
  typedef BST* ptr;

  int _value;
  ptr left = nullptr, right = nullptr;
  bool allowDuplicates;
public:
  BST(int value, bool allowDuplicates = true): _value(value), allowDuplicates(allowDuplicates){}

  // Recursively deletes all nodes in the binary tree rooted at currNode
	~BST(){ delete left; delete right; }

  bool insert(int value){
    if (value == _value && !allowDuplicates) return false;
    
    if (value < _value)
      if (left) return left->insert(value); 
      else left = new BST(value, allowDuplicates); // so all inserts have the same allowDuplicates variable.
    else
      if (right) return right->insert(value); 
      else right = new BST(value, allowDuplicates);
    return true;
  }

  void print(const string &offset="", bool isLeftChild=true) const{
    cout << offset << (isLeftChild? "|__": "|--") << _value << endl;
    if (left) left->print(offset + "|  ", true);
    if (right) right->print(offset + "|  ", false);
  }

  ll *inorder(ll *ans = nullptr) const{
    if (left) ans = left->inorder(ans);
    if (!ans) ans = new ll(_value); else ans->insert(_value);
    if (right) ans = right->inorder(ans);
    return ans;
  }
};


class Node {
 public:
  int value;
  // insert other fields and methods as appropriate
};

class Graph {
  Node *nodes = nullptr; // array of nodes
  int numNodes;
  int numEdges;
  vector<BST *> adj; // the adjancency list of the node in index i in `nodes`
  fstream graphFile;

  // specific to utility
  vector<char> visited;
  vector<BST *> dfsforest;
  vector<bool> is_grey;
  vector<int> part_of_a_cycle;
  bool time_to_label = false;
  int who_set_it_off = -1;

  // Add appropriate fields as necessary for your implementation
 public:
  Graph(int nNodes, int nEdges, const string &gFileName): numNodes(nNodes), numEdges(nEdges), adj(numNodes, nullptr), visited(numNodes), is_grey(numNodes), part_of_a_cycle(numNodes){
    
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

    for (int i = 0; i < numNodes; i++)
      nodes[i].value = i + 1;

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

      if (adj[n1] && !adj[n1]->insert(n2))
        continue;

      if (!adj[n1]) adj[n1] = new BST(n2, false); // if adj[n1] then n2 is already inserted.
      if (!adj[n2]) adj[n2] = new BST(n1, false); else adj[n2]->insert(n1);
      
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;

    // Add appropriate code as necessary for your implementation
    for (BST *tree: dfsforest) delete tree;
    for (BST *adjlist: adj) delete adjlist;
  }

  // Add appropriate method declarations as necessary for your implementation
  BST *dfs_visit(int src, int parent, BST *dfstree);
  void modifiedDFS();
  void printResults();
};

#endif
