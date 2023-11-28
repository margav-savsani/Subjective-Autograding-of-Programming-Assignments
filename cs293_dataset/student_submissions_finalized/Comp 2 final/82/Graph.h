#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif



template <typename T> class adjacencyList{
	public:
		T Node;
		adjacencyList<T>* next;
		adjacencyList(){
			next = nullptr;
		}
		adjacencyList(T node){
			Node = node;
			next = nullptr;
		}
};


class Node
{
public:
	int value;
	adjacencyList<Node*>* adjOutNodes;
	adjacencyList<Node*>* adjInNodes;

	Node(){
		value = -1;
		adjOutNodes = nullptr;
		adjInNodes = nullptr;
	}
	Node(int val){
		this->value = val;
		adjOutNodes = nullptr;
		adjInNodes = nullptr;
	}
	Node(int val, adjacencyList<Node*>* adjOutList, adjacencyList<Node*>* adjInList){
		this->value = val;
		adjOutNodes = adjOutList;
		adjInNodes = adjInList;
	}
	bool find(Node *node){
			adjacencyList<Node*>* curr = adjOutNodes;
			while(curr != nullptr){
				if(curr->Node->value == node->value) return true;
				curr = curr->next;
			}
			return false;
	}
	void insertOut(Node* node){
		if(adjOutNodes == nullptr){
			adjOutNodes = new adjacencyList<Node*>(node);
			return;
		}
		adjacencyList<Node*>* curr = adjOutNodes;
	
		while(curr->next != nullptr){
			curr = curr->next;
		}
		curr->next = new adjacencyList<Node*>(node);
	}
	void insertIn(Node* node){
		if(adjInNodes == nullptr){
			adjInNodes = new adjacencyList<Node*>(node);
			return;
		}
		adjacencyList<Node*>* curr = adjInNodes;
	
		while(curr->next != nullptr){
			curr = curr->next;
		}
		curr->next = new adjacencyList<Node*>(node);
	}
	// insert other fields and methods as appropriate
};

class Pair{
	public:
		int x;
		int y;
		Pair(){
			x = -1;
			y = -1;
		}
		Pair(int x, int y){
			this->x = x;
			this->y = y;
		}
};

class Graph
{
	int numNodes;
	int numEdges;
	Node *nodes;
	Node* srcNodes;
	int numNodeInCycle;
	int** similarMatrix;
	adjacencyList<Pair*>* input = nullptr;
	// Add appropriate fields as necessary for your implementation

public:
	ofstream graphFile;
	int numSrcNodes;
	Graph(string filename)
	{
		// INITIALIZAION
		graphFile.open(filename);
		//-------------
		numEdges = 0;
		cin >> numNodes;

		nodes = new Node[numNodes];
		for (int i = 0; i < numNodes; i++)
		{
			nodes[i].value = i + 1;
		}

		similarMatrix = new int*[numNodes];
		for(int i=0; i<numNodes; i++){
			similarMatrix[i] = new int[numNodes];
		}

		//-------------

		int n1, n2;
		int countEdges = 0;
		cin >> n1 >> n2;
		do
		{
			if(input == nullptr){
				input = new adjacencyList<Pair*>;
				input->Node = new Pair(n1, n2);
			}
			else{
				adjacencyList<Pair*>* curr = input;
				while(curr->next != nullptr){
					curr = curr->next;
				}
				curr->next = new adjacencyList<Pair*>;
				curr->next->Node = new Pair(n1, n2);

			}
			if(!nodes[n1 - 1].find(&nodes[n2 - 1])){
				nodes[n1 - 1].insertOut(&nodes[n2 - 1]);
				nodes[n2 - 1].insertIn(&nodes[n1 - 1]);
				countEdges++;
			}
			// Create an undirected edge from n1 to n2 and store in appropriate
			// adjacency list(s).  If an undirected edge from n1 to n2 (or
			// equivalently from n2 to n1) already exists, you shouldn't add
			// an edge.  Only if such an undirected edge didn't exist earlier,
			// should you add the edge and increment countEdges; otherwise,
			// do not increment countEdges;
			// Every time an edge is created, we also add that information to
			// graphFile

			cin >> n1 >> n2;
		}while(n1 != -1 && n2 != -1);
		numEdges = countEdges;

		// similar nodes (row, col) ==> row ~ col

		cin >> n1 >> n2;
		do{
			similarMatrix[n1 - 1][n2 - 1] = 1;
			cin >> n1 >> n2;
		}while(n1 != -1 && n2 != -1);

		// Add appropriate code as necessary for your implementation
	}

	~Graph()
	{
		delete[] nodes;
		// Add appropriate code as necessary for your implementation
	}

	// Add appropriate method declarations as necessary for your implementation
	int getNumNodes(){
		return numNodes;
	}
	int* getSourceNodes();
	void fillSimilarNodes(int* srcNodes);
	void collapseSimilarNodes();
	void printResults();
	void getDepth(Node* node, int &depth, int visited[], int d);
	void mainDFS(Node* node, adjacencyList<int>* similar[], int visited[], int depth);
	bool condition2(int a, int b);
	void printCollapsed();
	void storeComp(adjacencyList<int>* &comp, int k, int visited[]);
};

#endif
