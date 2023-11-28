#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BST {
	int value;
	BST* left = nullptr;
	BST* right = nullptr;
	BST* parent = nullptr;

public:
	BST(int value): value(value){}
	BST(int value, BST*parent): value(value), parent(parent){}
	void insert(int v){
		if(v>=value){
			if(right==nullptr) right = new BST(v, this);
			else right->insert(v);
		}
		else{
			if(left == nullptr) left = new BST(v, this);
			else left->insert(v);
		}
	}
	~BST(){
		if(right!=nullptr) delete right;
		if(left!=nullptr) delete left;
	}
	void printBST(const string& prefix, bool isLeft){
		cout << prefix;
    	cout << (isLeft ? "|--" : "|__" );
    	// print the value of the node
    	cout<<value << endl;
		if(left!= nullptr)
			left->printBST(prefix + (isLeft ? "│   " : "    "), true);
		if(right!=nullptr)
			right->printBST(prefix + (isLeft ? "│   " : "    "), false);
	}
};

template <typename T> class LL{
	public:
	T obj;
	LL<T> * next = nullptr;
	LL(T obj): obj(obj){}
	bool insert(T n){
		if(obj == n) return false;
		if(next != nullptr) return next->insert(n);
		next = new LL(n);
		return true;
	}
	~LL(){
		if (next != nullptr) delete next;
	}
};

class Node {
public:
	int value;
	LL<int>* adjacency = nullptr;

	Node(){}
	Node(int value): value(value){}
	bool insert(int node){
		if(adjacency != nullptr) return adjacency->insert(node);
		adjacency = new LL<int>(node);
		return true;
	}
	~Node(){
		if(adjacency != nullptr) delete adjacency;
	}
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

  	LL<BST*> *bstLL = nullptr;
	int* visited;
	bool* cyclic;

 public:
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

	  if(nodes[n1].insert(n2)){
		nodes[n2].insert(n1);
		graphFile << n1+1 << " " << n2+1 << endl;
		countEdges++;
	  }
    }

    // Add appropriate code as necessary for your implementation

	// int node1[numEdges] = {1, 2, 3, 4, 5, 6, 2, 2, 7, 6, 2, 10, 11};
	// int node2[numEdges] = {2, 3, 4, 2, 2, 5, 6, 7, 8, 8, 9, 9, 10};
	// // int node1[numEdges] = {0, 1, 2, 3, 4, 5, 3};
	// // int node2[numEdges] = {1, 2, 3, 4, 1, 1, 5};

	// for(int i=0; i<numEdges; i++){
	// 	nodes[node1[i]- 1].insert(node2[i]-1);
	// 	nodes[node2[i]-1].insert(node1[i]-1);
	// }

	cyclic = new bool[numNodes];
	visited = new int[numNodes];

  }

  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
	delete[] visited;
	delete[] cyclic;
	if(bstLL != nullptr) delete bstLL;
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS(int node = 0);
  void printResults();
};

#endif
