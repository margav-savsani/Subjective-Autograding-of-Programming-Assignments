#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BST {
	// Add your own field and members here
	BST* left;
	BST* right;
	public:
	int value;
	// Feel free to use the printBST function used earlier
	BST(int value){
		left = nullptr;
		right = nullptr;
		this->value = value;
	}
	void insert(int n){
		BST* toAdd = new BST(n);
		BST* curr = this;
		while(curr){
			if(n<=curr->value){
				if(curr->left){
					curr = curr->left;
					continue;
				}
				curr->left = toAdd;
				return;
			}
			if(curr->right){
				curr = curr->right;
				continue;
			}
			curr->right = toAdd;
			return;
		}
	}
	// Adapted from Adrian Schneider's code on StackOverflow
	void printBST(const string& prefix, bool isLeft=false)
	{
		cout << prefix;

		cout << (isLeft ? "|--" : "|__" );

		// print the value of the node
		cout<<value<<endl;
		// enter the next tree level - left and right branch
		if(left)
			left->printBST( prefix + (isLeft ? "│   " : "    "), true);
		if(right)
			right->printBST( prefix + (isLeft ? "│   " : "    "), false);
	}

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

class Node {
 public:
	int value;
	listOfObjects<int>* adjacencyList; // stores the index of adjacent node
	// insert other fields and methods as appropriate
};

class Graph {
	int numNodes;
	int numEdges;
	fstream graphFile;
	listOfObjects<BST*>* trees;
	Node *nodes;
	int nConnectedComponents;
	int* visitCount;
	bool isCycleFound;
	int nInCycle;
	bool* isInStack;
	bool* isInCycle;
	// Add appropriate fields as necessary for your implementation
	
 public:
	Graph(int nNodes, int nEdges, string gFileName) {
		nInCycle = 0;
		isCycleFound = 0;
		visitCount = new int[nNodes];
		isInStack = new bool[nNodes];
		isInCycle = new bool[nNodes];
		for(int i=0;i<nNodes;i++){
			visitCount[i] = 0;
			isInStack[i] = false;
			isInCycle[i] = false;
		}
		nConnectedComponents = 0;
		trees = nullptr;
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
			// adjacency list(s).	If an undirected edge from n1 to n2 (or
			// equivalently from n2 to n1) already exists, you shouldn't add
			// an edge.	Only if such an undirected edge didn't exist earlier,
			// should you add the edge and increment countEdges; otherwise,
			// do not increment countEdges;
			// Every time an edge is created, we also add that information to
			// graphFile
			listOfObjects<int>* curr = nodes[n1].adjacencyList;
			bool isFound = 0;
			while(curr){
				if(curr->object== n2){
					isFound = true;
					break;
				}
				curr = curr->next;
			}
			if(isFound){
				continue;
			}
			listOfObjects<int>* toAdd1= new listOfObjects<int>(n2);
			listOfObjects<int>* toAdd2= new listOfObjects<int>(n1);
			toAdd1 -> next = nodes[n1].adjacencyList;
			nodes[n1].adjacencyList = toAdd1;
			toAdd2 -> next = nodes[n2].adjacencyList;
			nodes[n2].adjacencyList = toAdd2;
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
	void doDFS(int caller,int idx,int*visitCount,BST* &tree);
	void modifiedDFS();
	void printResults();
};

#endif
