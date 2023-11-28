#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<string>

#include<fstream>
using namespace std;
class Node;

//TreeNode class declared here
class TreeNode{
public:
	int object;
	TreeNode *left, *right;
	TreeNode *parent;
	
	TreeNode(int n){
		this->object =n;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

//BST class declared here
class BST {

private:  
	TreeNode *root;
public:
	BST(){
		root = nullptr;
	}	
	void insert(int n);
	~BST(){
		recursiveDelete(root);
	}
	void printBST(std::ostream &os, const std::string& prefix, bool isLeft);
	void recursiveDelete(TreeNode* curr);
};

//ListNode class declared here
template<typename T>
class ListNode{
public:
	T node;
	ListNode* prev;
	ListNode *next;
	
	ListNode(T x){
		node = x;
		prev = nullptr;
		next = nullptr;
	}
	
	~ListNode(){}
	
};

//List class declared here
template<typename T>
class List{
public:
	ListNode<T> *start;
	ListNode<T> *end;
	
	List(T n){
		start = new ListNode<T>(n);
		end = start;
	}	
	
	List(){
		start = nullptr;
		end = nullptr;
	}
	
	~List(){}
		
	void insert(T n);
	bool find(T n);
	
};

//Node class declared here
class Node {
public:
	int value;
	List<int> *adjacent;
	
	int index; // index in the nodes array
	int arr[2]; // arrival time (two in number because of modiifed DFS)
  	int dep[2];// departure time (two in number because of modiifed DFS)
 	int pred[2]; //predecessor node (two in number because of modiifed DFS)
	int no_of_visits; // the number of times this node has been visited
	
	
	//constructors implementation
	Node(){
		adjacent = new List<int>();
		pred[0] = pred[1] = -1;
		arr[0] = arr[1] = -1;
		dep[0] = dep[1] = -1;
		no_of_visits = 0;
	}
	
	Node(int n){
		value = n;
		adjacent = new List<int>();
		pred[0] = pred[1] = -1;
		arr[0] = arr[1] = -1;
		dep[0] = dep[1] = -1;
		no_of_visits = 0;
	}
	
	//for iserting Edges 
	bool insertEdge(int index){
		if(adjacent->find(index)) return false;
		adjacent->insert(index);
		return true;
	}
	
	~Node(){
		delete adjacent;
	}
// insert other fields and methods as appropriate
};



//Graph class declared here
class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int times; // for storing the value of time
  Node *nodes;
  int count; // the variable which counts the difference of cyclic nodes and the nodes traversed twice
  List<BST*> *a; // containing the list of BSTs
  BST *b; // the BST which is the working BST 
  int ones, twice, connected_components; // the details like the number of nodes traversed once, traversed twice and the number of connected components
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
	a = new List<BST*>();
	numNodes = nNodes;
    numEdges = nEdges;
    if(numEdges > (numNodes*(numNodes-1))/2){
    	cout << "Impossible number of edges given" << endl;
    	exit(-1);
    }
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
      nodes[i].index = i;
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
      
      if(nodes[n1].insertEdge(n2) == false){
		continue;
      }else{
		  nodes[n2].insertEdge(n1);
		  graphFile << n1+1 << " " << n2+1 << endl;
		  countEdges++;
		}
		
    }
	times = 0;
	count = 0;
	ones = 0;
	twice = 0;
	connected_components = 0;
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
  void modifiedDFS();
  void modifiedDFS_visit(int n, int m);
  void printResults();
};

#endif
