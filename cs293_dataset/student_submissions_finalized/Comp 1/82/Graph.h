#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BSTNode{
	public:
		int value;
		BSTNode* left;
		BSTNode* right;
		BSTNode* par;

		BSTNode(int val){
			left = nullptr;
			right = nullptr;
			par = nullptr;
			value = val;
		}
};


class BST
{
	public:
	BSTNode* root;

	BST(){
		root = nullptr;
	}

	void insert(int val, BSTNode* node){
		if(node == nullptr){
			root = new BSTNode(val);
		}
		else{
			if(val <= node->value && node->left == nullptr){
				node->left = new BSTNode(val);
				node->left->par = node;
				return;
			}
			else if(val > node->value && node->right == nullptr){
				node->right = new BSTNode(val);
				node->right->par = node;
				return;
			}
			if(val > node->value){
				insert(val, node->right);
			}
			else{
				insert(val, node->left);
			}
		}
	}

	void printBST(const string& prefix, bool isLeft=false)
	{
		if( root != nullptr )
		{
			cout << prefix;

			cout << (isLeft ? "|--" : "|__" );

			// print the value of the node
			cout << root->value << endl;
			BSTNode *curr = root;
			root = root->left;
			// enter the next tree level - left and right branch
			printBST( prefix + (isLeft ? "│   " : "    "), true);
			root = curr->right;
			printBST( prefix + (isLeft ? "│   " : "    "), false);
			root = curr;
		}
	}
	// Add your own field and members here

	// Feel free to use the printBST function used earlier
};


template <typename T> class adjacencyList{
	public:
		T Node;
		adjacencyList<T>* next;
		adjacencyList(T node){
			Node = node;
			next = nullptr;
		}
};


class Node
{
public:
	int value;
	adjacencyList<Node*>* adjNodes;

	Node(){
		value = -1;
		adjNodes = nullptr;
	}
	Node(int val){
		this->value = val;
		adjNodes = nullptr;
	}
	Node(int val, adjacencyList<Node*>* adjList){
		this->value = val;
		adjNodes = adjList;
	}
	bool find(Node *node){
			adjacencyList<Node*>* curr = adjNodes;
			while(curr != nullptr){
				if(curr->Node->value == node->value) return true;
				curr = curr->next;
			}
			return false;
	}
	void insertAdj(Node* node){
		if(adjNodes == nullptr){
			adjNodes = new adjacencyList<Node*>(node);
			return;
		}
		adjacencyList<Node*>* curr = adjNodes;
	
		while(curr->next != nullptr){
			curr = curr->next;
		}
		curr->next = new adjacencyList<Node*>(node);
	}
	// insert other fields and methods as appropriate
};

class Graph
{
	int numNodes;
	int numEdges;
	fstream graphFile;

	Node *nodes;
	adjacencyList<BST*>* listOfTrees;

	int numConnectedComp;
	int numNodes1;
	int numNodes2;
	int numNodeInCycle;	
	// Add appropriate fields as necessary for your implementation

public:
	Graph(int nNodes, int nEdges, string gFileName)
	{
		srand(10);

		//-------------
		numConnectedComp = 0;		
		numNodes1 = 0;
		numNodes2 = 0;
		numNodeInCycle = 0;
		//-------------

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

			if(!nodes[n1].find(&nodes[n2])){
				nodes[n1].insertAdj(&nodes[n2]);
			}
			
			if(!nodes[n2].find(&nodes[n1])){
				nodes[n2].insertAdj(&nodes[n1]);
			}
			// Create an undirected edge from n1 to n2 and store in appropriate
			// adjacency list(s).  If an undirected edge from n1 to n2 (or
			// equivalently from n2 to n1) already exists, you shouldn't add
			// an edge.  Only if such an undirected edge didn't exist earlier,
			// should you add the edge and increment countEdges; otherwise,
			// do not increment countEdges;
			// Every time an edge is created, we also add that information to
			// graphFile

			graphFile << n1 + 1 << " " << n2 + 1 << endl;
			countEdges++;
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
	void printResults();
};

#endif
