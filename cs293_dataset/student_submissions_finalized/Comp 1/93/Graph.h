#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BST{
	// Add your own field and members here
	BST* parent = NULL;
	BST* left = NULL;
	BST* right = NULL;
	int data;
	
public:
	BST(int d): data{d}{}

	//right side contians elements greater than or equal to the root 
	void insert(int d){
		if(d < data){
			if(left)
				return left->insert(d);
			left = new BST{d};
			left->parent = this;
			return;
		}
		if(right)
			return right->insert(d);
		right = new BST{d};
		right->parent = this;
		return;
	}
	// Feel free to use the printBST function used earlier
	void printBST(const string& prefix = "", bool isLeft=false){
		cout << prefix;
		cout << (isLeft ? "|--" : "|__" );
		// print the value of the node
		cout << data << endl;
		// enter the next tree level - left and right branch
		if(left)
			left->printBST( prefix + (isLeft ? "│   " : "    "), true);
		if(right)
			right->printBST( prefix + (isLeft ? "│   " : "    "), false);
	}
	// ~BST(){delete left; delete right;}
};

template <typename T>
class List{
public:
	List<T>* next = NULL;
	T data;
	List(T t):data{t}{}
};

template <typename T1, typename T2>
class Pair{
public:
	T1 first;
	T2 second;
	Pair(T1 f, T2 s):first{f}, second{s}{}
};

class Node{
public:
	int value;
	List<Node*>* adj = NULL;
	// insert other fields and methods as appropriate
	Node(int val = 0):value{val}{}
};

class Graph{
	int numNodes;
	int numEdges;
	fstream graphFile;

	Node *nodes = NULL;
	short* visit_status = NULL;

	List<BST*>* connected_components = NULL;
	// Add appropriate fields as necessary for your implementation

public:
	Graph(int nNodes, int nEdges, string gFileName){

		//check if the given number of edges is possible
		if(nEdges > nNodes*(nNodes-1)/2){
			cerr<<"invalid number of edges"<<endl;
			exit(-1);
		}

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
		if (nodes == nullptr){
			cerr << "Memory allocation failure." << endl;
			exit(-1);
		}

		for (int i = 0; i < numNodes; i++){
			nodes[i].value = i + 1;
		}

		srand(time(0));
		// srand(0);
		int n1, n2;
		int countEdges = 0;
		//.....................
		//testing code
		// int i = 0;
		// int a[numEdges] = {1, 2, 3, 4, 5, 6, 2, 2, 7, 6, 2, 10, 11};
		// int b[numEdges] = {2, 3, 4, 2, 2, 5, 6, 7, 8, 8, 9, 9, 10}; 
		//.......................
		while (countEdges < numEdges){
			do{
				n1 = rand() % numNodes;
				n2 = rand() % numNodes;
			} while (n1 == n2);

			//.....................
			//testing code
			// n1 = a[i]-1;
			// n2 = b[i]-1;
			// i++;
			//.......................
			// Create an undirected edge from n1 to n2 and store in appropriate
			// adjacency list(s).  If an undirected edge from n1 to n2 (or
			// equivalently from n2 to n1) already exists, you shouldn't add
			// an edge.  Only if such an undirected edge didn't exist earlier,
			// should you add the edge and increment countEdges; otherwise,
			// do not increment countEdges;
			// Every time an edge is created, we also add that information to
			// graphFile
			bool isPresent = 0;
			List<Node*>* ptr = nodes[n1].adj;
			while(ptr){
				if(ptr->data->value == n2+1){
					isPresent = 1;
					break;
				}
				ptr = ptr->next;
			}
			if(isPresent)
				continue;
			
			//add the new edge
			ptr = nodes[n1].adj;
			nodes[n1].adj = new List<Node*>{nodes+n2};
			nodes[n1].adj->next = ptr;

			ptr = nodes[n2].adj;
			nodes[n2].adj = new List<Node*>{nodes+n1};
			nodes[n2].adj->next = ptr;

			graphFile << n1 + 1 << " " << n2 + 1 << endl;
			countEdges++;
		}
		// Add appropriate code as necessary for your implementation
	}

	~Graph(){
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
