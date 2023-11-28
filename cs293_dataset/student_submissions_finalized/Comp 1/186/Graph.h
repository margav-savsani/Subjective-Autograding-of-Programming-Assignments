#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

// Struct for Node of a BST
struct TreeNode{
	int value;		  // value stored in the Tree Node
	TreeNode *left;	  // Left Child of this Node (NULL, if None)
	TreeNode *right;  // Right Child of this Node (NULL, if None)
	TreeNode *parent; // The Parent Node, NULL in case of Root

	TreeNode(){		  // Default Constructor
		value = 0;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	TreeNode(int initValue){ 	// Constructor with an initial value
		value = initValue;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

// Binary Search Tree Class to store each Connected Component
class BST {
	TreeNode *root;		  // Root Node
public:
	BST(){	              // Constructors
		root = nullptr;
	}
	BST(TreeNode *root){
		this->root = root;
	}
	void printBST(const string &prefix, bool isLeft);		// Print full BST
	bool insert(int value);			// Insert a new Node with a given value into BST
};

// List of Objects class to create Linked lists of a given data type 
template <typename T>
class listOfObjects{
public:
	T object;					 //	Object to be stored
	listOfObjects<T> *next;		 // Pointer to the next element
	listOfObjects<T> *prev;		 // Pointer to the previous element

	listOfObjects(T initValue){	  // Constructor
		object = initValue;
		next = prev = nullptr;
	}
	~listOfObjects() { ; }		  // Destructor
};

// Node of the Graph
class Node {
public:
	int value;				// Value stored in this node
	bool inCycle;			// bool indicating if this nodes in in any cycle
	Node *parent;			// Parent node of this node
	int visited;			// Number of times this node has been visited
	listOfObjects<Node *> *adjacency;		// Adjacency list of the Node
	Node(){					// Constructor
		value = 0;
		visited = 0;
		inCycle = false;
		parent = nullptr;
		adjacency = nullptr;
	}
};

// Graph Class 
class Graph {
	int numNodes;			 // Number of nodes in the Graph
	int numEdges;			 // Number of edges in the Graph
	fstream graphFile;		 // Log File to store edges information 
	Node **nodes;			 // Array of Nodes contained in the Graph
	int connectedComponents; // Number of connected components
	int visOne;		 	     // Number of Nodes visited onces in the Graph
	int visTwice;			 // Number of Nodes visited twice in the Graph
	int numNodesInCycle;	 // Number of Nodes in any cycle in the Graph
	BST **trees;			 // Array of Trees of connected components
public:
	Graph(int nNodes, int nEdges, string gFileName){		// Constructer
		numNodes = nNodes;
		numEdges = nEdges;
		visOne = 0;
		visTwice = 0;
		connectedComponents = 0;
		numNodesInCycle = 0;
		trees = new BST *[numNodes];
		nodes = new Node *[numNodes];

		graphFile.open(gFileName, ios::out);
		if (!graphFile.is_open()){
			cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
			exit(-1);
		}

		graphFile << numNodes << endl;
		graphFile << numEdges << endl;

		if (nodes == nullptr){
			cerr << "Memory allocation failure." << endl;
			exit(-1);
		}

		for (int i = 0; i < numNodes; i++){			// Initializing array of Nodes and Trees
			nodes[i] = new Node();
			nodes[i]->value = i + 1;
			trees[i] = nullptr;
		}

		srand(time(0));		
		int n1, n2;
		int countEdges = 0;

		while (countEdges < numEdges){		// Initializing a random graph
			do{			// Generating random edges for the Graph
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
	
			listOfObjects<Node *> *node1Adj = nodes[n1]->adjacency;		// Iterator for adjacency list of first node (n1)
			listOfObjects<Node *> *checkAdj = nodes[n1]->adjacency;		// Iterator to check if an edge generated is already in the graph
			bool inserted = false;			// boolean indicating whether the edge is already in the graph
			while (checkAdj != nullptr){	// Checking if the edge to b inserted is already inserted before
				if (checkAdj->object->value == nodes[n2]->value){
					inserted = true;
					break;
				}
				checkAdj = checkAdj->next;
			}
			if (!inserted){				// insert into graph only if it was not inserted before
				graphFile << n1 + 1 << " " << n2 + 1 << endl;				// writing into graphFile
				listOfObjects<Node *> *node2Adj = nodes[n2]->adjacency;		// Adjacency list of Second node (n2)
				if (nodes[n1]->adjacency == nullptr){			// Inserting edge into adjacency list of first node
					nodes[n1]->adjacency = new listOfObjects<Node *>(nodes[n2]);
				}
				else{
					while (node1Adj->next != nullptr){
						node1Adj = node1Adj->next;
					}
					node1Adj->next = new listOfObjects<Node *>(nodes[n2]);
					node1Adj->next->prev = node1Adj;
				}
				if (nodes[n2]->adjacency == nullptr){
					nodes[n2]->adjacency = new listOfObjects<Node *>(nodes[n1]);
				}
				else{
					while (node2Adj->next != nullptr){			// Inserting edge into adjacency list of second node
						node2Adj = node2Adj->next;
					}
					node2Adj->next = new listOfObjects<Node *>(nodes[n1]);
					node2Adj->next->prev = node2Adj;
				}
				countEdges++;	
			}
		}
	}

	~Graph(){			// Destructor
		if (graphFile.is_open())
		{
			graphFile.close();
		}
		delete[] nodes;
		delete[] trees;
	}

	void modifiedDFS();					// Modified DFS Function
	void printResults();				// To Print all the required Results
	void dfs(Node *node, BST *tree);	// Helper recursive function for modified DFS

};

#endif
