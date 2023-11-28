#ifndef GRAPH_H
#define GRAPH_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

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
	Node *parent;			// Parent node of this node
	int level;				// Level of Node in DFS Tree
	bool visited;			// Number of times this node has been visited
	listOfObjects<Node *> *adjacency;		// Adjacency list of the Node
	listOfObjects<Node *> *inAdjacency;		// List of nodes which are parent of this Nodes
 	Node(){					// Constructor
		value = 0;
		visited = false;
		parent = nullptr;
		level = 0;
		adjacency = nullptr;
		inAdjacency = nullptr;
	}
};

// Graph Class 
class Graph {
	int numNodes;			 // Number of nodes in the Graph
	fstream outFile;		 // Log File to store edges information 
	Node **nodes;			 // Array of Nodes contained in the Graph
	int **similarMatrix;	 // Matrix to store similarity relations
							 // Matrix[i][j] = 1 if node[i] ~ node[j], else = 0

public:
	Graph(string outFileName){		// Constructer
		numNodes = 0;
		outFile.open(outFileName, ios::out);
		if (!outFile.is_open()){
			cerr << "Couldn't open graph file " << outFileName << ". Aborting ..." << endl;
			exit(-1);
		}
		cin >> numNodes;
		nodes = new Node *[numNodes];
		similarMatrix = new int*[numNodes];
		if (nodes == nullptr){
			cerr << "Memory allocation failure." << endl;
			exit(-1);
		}

		for (int i = 0; i < numNodes; i++){		// Initializing array of Nodes and similar Matrix
			nodes[i] = new Node();
			nodes[i]->value = i + 1;
			similarMatrix[i] = new int[numNodes];
			for(int j = 0; j < numNodes; j++){
				similarMatrix[i][j] = 0;
			}
		}

		int val1, val2, n1, n2;
		while (true){		// Initializing a Graph Edges
			cin >> val1 >> val2;
			n1 = val1 - 1;
			n2 = val2 - 1;
			if(val1 == -1 && val2 == -1){
				break;
			}
			listOfObjects<Node *> *node1Adj = nodes[n1]->adjacency;		// Iterator for adjacency list of first node (n1)
			listOfObjects<Node *> *checkAdj = nodes[n1]->adjacency;		// Iterator to check if an edge generated is already in the graph
			listOfObjects<Node *> *node2Adj = nodes[n2]->inAdjacency;		// InAdjacency list of Second node (n2)
			if (nodes[n1]->adjacency == nullptr){							// Inserting edge into adjacency list of first node
				nodes[n1]->adjacency = new listOfObjects<Node *>(nodes[n2]);
			}
			else{
				while (node1Adj->next != nullptr){
					node1Adj = node1Adj->next;
				}
				node1Adj->next = new listOfObjects<Node *>(nodes[n2]);
				node1Adj->next->prev = node1Adj;
			}
			if (nodes[n2]->inAdjacency == nullptr){
				nodes[n2]->inAdjacency = new listOfObjects<Node *>(nodes[n1]);
			}
			else{
				while (node2Adj->next != nullptr){			// Inserting edge into InAdjacency list of second node
					node2Adj = node2Adj->next;
				}
				node2Adj->next = new listOfObjects<Node *>(nodes[n1]);
				node2Adj->next->prev = node2Adj;
			}
		}
		while(true){		// Make Nodes similar as said by user
			cin >> val1 >> val2;
			n1 = val1 - 1;
			n2 = val2 - 1;
			if(val1 == -1 && val2 == -1){
				break;
			}
			similarMatrix[n1][n2] = 1;
		}
	}

	~Graph(){			// Destructor
		if (outFile.is_open()){
			outFile.close();
		}
		delete[] nodes;
	}

	void DFS();					// DFS
	void printResults();		// To Print all the required Results
	void dfs(Node *node);		// Helper recursive function for DFS to start from a given source Node
};

#endif
