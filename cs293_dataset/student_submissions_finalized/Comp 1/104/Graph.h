#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;	  // Left Child of this Node (NULL, if None)
	TreeNode *right;  // Right Child of this Node (NULL, if None)
	TreeNode *parent; // The Parent Node, NULL in case of Root

	// Constructors

	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
	TreeNode(int v, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : val(v), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
	TreeNode *root;

public:
	bool insert(int v)
	{

		// if an empty tree then create a root node
		if (root == nullptr)
		{
			root = new TreeNode(v);
			return true;
		}

		TreeNode *ptr = root;

		// search for required node
		while (true)
		{
			// go left if required key is less than or equal
			if (ptr->val >= v && ptr->left != nullptr)
			{
				ptr = ptr->left;
			}
			// go right if required key is strictly more
			else if (ptr->val < v && ptr->right != nullptr)
			{
				ptr = ptr->right;
			}
			// insert to left
			else if (ptr->val >= v && ptr->left == nullptr)
			{
				ptr->left = new TreeNode(v);
				ptr->left->parent = ptr;
				return true;
			}
			// insert to right
			else if (ptr->val < v && ptr->right == nullptr)
			{
				ptr->right = new TreeNode(v);
				ptr->right->parent = ptr;
				return true;
			}
		}
	}

	bool find(int v)
	{
		TreeNode *ptr = root;

		// same code as in insert
		while (true)
		{
			if (ptr == nullptr)
			{
				return false;
			}
			else if (ptr->val == v)
			{
				return true;
			}
			else if (ptr->val >= v)
			{
				ptr = ptr->left;
			}
			else
			{
				ptr = ptr->right;
			}
		}
	}

	void printBST(const string &prefix, bool isLeft = false)
	{
		if (root != nullptr)
		{
			cout << prefix;

			cout << (isLeft ? "|--" : "|__");

			// print the value of the node
			cout << root->val << endl;
			TreeNode *curr = root;
			root = root->left;
			// enter the next tree level - left and right branch
			printBST(prefix + (isLeft ? "│   " : "    "), true);
			root = curr->right;
			printBST(prefix + (isLeft ? "│   " : "    "), false);
			root = curr;
		}
	}

	BST()
	{
		root = nullptr;
	}
};

// doubly linked list
template <typename T>
class listOfObjects
{
public:
	T object;
	listOfObjects<T> *next;
	listOfObjects<T> *prev;

	// Constructor
	listOfObjects(T initValue)
	{
		object = initValue;
		next = prev = nullptr;
	}

	// Destructor
	~listOfObjects() { ; }
};

// helper function to insert at the head of listOfObjects
template <typename T>
void insertAtHead(listOfObjects<T> *&ptr, T x)
{
	if (ptr == nullptr)
	{
		ptr = new listOfObjects<T>(x);
	}
	else
	{
		listOfObjects<T> *temp = ptr;
		ptr = new listOfObjects<T>(x);
		ptr->next = temp;
		temp->prev = ptr;
	}
}

// helper function to insert at the tail of listOfObjects
template <typename T>
void insertAtTail(listOfObjects<T> *&ptr, T x)
{
	if (ptr == nullptr)
	{
		ptr = new listOfObjects<T>(x);
	}
	else
	{
		listOfObjects<T> *temp = ptr;

		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		temp->next = new listOfObjects<T>(x);
		temp->next->prev = temp;
	}
}

// helper function to check if a particular element is present in linked list
template <typename T>
bool isPresent(listOfObjects<T> *ptr, T x)
{
	listOfObjects<T> *temp = ptr;

	while (temp != nullptr)
	{
		if (temp->object == x)
		{
			return true;
		}

		temp = temp->next;
	}

	return false;
}

// node of the graph
class Node
{
public:
	int value;

	// linked list of adjacent nodes
	listOfObjects<int> *adjacency;

	// to add a new node to adjacency list
	void add(int v)
	{	
		// if node is already present then do nothing
		if (isPresent(adjacency, v))
		{
			return;
		}
		// else add the node to adjacency list
		else
		{
			insertAtHead(adjacency, v);
		}
	}

	Node()
	{
		value = -1;
		adjacency = nullptr;
	}

	Node(int v)
	{
		value = v;
		adjacency = nullptr;
	}
};

// class to hold graph
class Graph
{
	int numNodes;
	int numEdges;
	fstream graphFile;

	Node *nodes;

	// linked list to hold BSTs
	listOfObjects<BST *> *trees;

	int numConnectedComponents; // stores number of connected components
	int nodesOnce; // stores number of nodes that are visited once
	int nodesTwice; // stores number of nodes that are visited twice
	int nodesInCycle; // stores number of nodes that are in a cycle

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

		srand(1);
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

			// if edge is already present then don't add
			if (isPresent(nodes[n1].adjacency, n2 + 1) || isPresent(nodes[n2].adjacency, n1 + 1))
			{
				continue;
			}
			// if not already present then add the edge
			else
			{
				nodes[n1].add(n2 + 1);
				nodes[n2].add(n1 + 1);
			}

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

	void recDFS(int v, int *visited, int *parent1, int *parent2, int *DFSTree, bool *isInCycle, int *arrTime, int &time, int vp);

	void modifiedDFS();
	void printResults();
};

#endif
