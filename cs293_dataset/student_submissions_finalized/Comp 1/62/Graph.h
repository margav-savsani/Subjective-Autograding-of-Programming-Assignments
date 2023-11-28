#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

template<typename T>
class LLNode{ // node of a linked list - doubly
	public:
	LLNode<T>* prev;
	LLNode<T>* next;
	T value;
	LLNode(T val){ 
		value=val;
		next = prev = nullptr;
	}
	//*
	~LLNode(){
		if (next) delete next;
	}	///*/
};
template<typename T>//wrapper for the linked list
class LinkedList{
	LLNode<T>* head;
	LLNode<T>* tail;
	public:
	unsigned int size;
	LinkedList(){
		head=tail=nullptr;
		size=0;
	}
	bool insert(T val){ // insert value into the linkedlist
		if (size==0){ //empty
			head=tail=new LLNode<T>(val);
			size=1;
			return true;
		}//nonempty
		size++; 
		tail->next = new LLNode<T>(val);
		tail->next->prev=tail;
		tail=tail->next;
		return true;
	}
	LLNode<T>* Head(){return head;}//*
	~LinkedList(){
		if (head) delete head;
	}///*/
};

// BST storing integers
class BST { // uses revursive definition of binary tree
public:	
	BST* left; // left subtree
	BST* right; // right subtree
	BST* parent;//unnecessary
	int value;

	BST(int val){
		value = val;
		left=right=parent=nullptr;
	}
	BST(int val, BST* par){
		left=right=nullptr;
		value=val;
		parent = par;
	}//*
	~BST(){
		if (left) delete left;
		if (right) delete right;
	}///*/
///*
// a slight variation in the return parameter of BST find
//in case a match is found, the pointer to that node is returned, otherwise
// return the node whose direct hild would have been where this value existed
	BST* find(int val){ //recursive find
		if (value==val) return this;
		if (value<val) return (right==nullptr?this:right->find(val));
		return (left==nullptr?this:left->find(val));
	}
///*/
//only important convention - equal values go to the left
//regular insert like
	bool insert(int val){// recursive insert
		if (value<val){
			if (right==nullptr) {
				right = new BST(val,this);
				return true;
			}
			return right->insert(val);
		}
		if (left==nullptr){
			left= new BST(val,this);
			return true;
		}
		return left->insert(val);
	}
// convert the inorder traversal of the binary tree to a linked list, because why not use BST sort for the edges
	void addtolist(LinkedList<int>* addto){
		if (left) left->addtolist(addto);
		addto->insert(this->value);
		if (right) right->addtolist(addto);
	}
// print BST op, modification of the standard 
	void printBST(const string& prefix ="",bool isLeft = true){
		cout << prefix << (isLeft ? "|--" : "|__" ) << value << endl;// print the value of the node
        
        // recursively call
        if (left) left->printBST( prefix + (isLeft ? "│   " : "    "), true);
        if (right) right->printBST( prefix + (isLeft ? "│   " : "    "), false);
	}	
};
// Wrapper class for BST , again ints
class BSTWrapper{
	BST* root;// root of tree
	public:
		BSTWrapper(){
			root=nullptr;
		}
		bool insert(int val){//wrapper
			return root->insert(val);
		}

		BST* Root(){return root;}
		void clear(){root=nullptr;}
		~BSTWrapper(){
			delete root;
		}
		LinkedList<int>* tolist(){//helper to call BST::addtolist
			if (root==nullptr) return nullptr;
			LinkedList<int>* sorted = new LinkedList<int>();
			root->addtolist(sorted);
			return sorted;
		}
		//insert uniquely into the BST
		bool addUnique(int val){
			if (root==nullptr){// empty tree
				root = new BST(val);
				return true;
			}
			BST* lastrec = root->find(val);
			if (lastrec->value==val) return false;//value already exists
			return lastrec->insert(val);// otherwise insert at that point
		}
		//insert in a way that allows only one copy
		bool add(int val){
			if (root==nullptr){
				root = new BST(val);
				return true;
			} 
			BST* interm = root->find(val); // interim/possible first occurence of value
			if (interm->value!=val||interm->left==nullptr) return interm->insert(val);//go ahead insert right there
			//equal values are inserted on the leftin insert
			BST* final =  interm->left->find(val);// traverse below to check for other copies
			if (final->value==val) return false;// found and not inserted
			return final->insert(val);
		}
};
// Graph node class
class Node {
	
	public:
	int value;
	LinkedList<int>* adjacency;

	Node(){
		value = -1;
		adjacency = nullptr;
	}
	Node(int val){
		value = val;
		adjacency = nullptr;
	}
	~Node(){
		delete adjacency;
	}
};
// a convenient way to bunch things up
struct GraphInfo{
	LinkedList<BST*>* forest;// collection of trees of each connected component
	int numconnected;// no of those components
	int nodesonce;// nodes visited once
	int nodestwice;// nodes visited twice
	int incycle;// nodes in cycles
	GraphInfo(LinkedList<BST*>* forest_,int nodesonce_,int nodestwice_,int incycle_){
		forest=forest_;
		numconnected = forest_->size;
		nodesonce=nodesonce_;
		nodestwice=nodestwice_;
		incycle=incycle_;
	}
	~GraphInfo(){
		delete forest;
	}
};

class Graph {
	int numNodes;
	int numEdges;
	fstream graphFile;

	Node *nodes;

	int* parent; // parent node index - index of parent
	bool* incycle; //  if node identified as being incycle
	int* visited; // nodes visited
	int* arrival;//first arrival of the node

	GraphInfo* Gi; //to b used by print
  // Add appropriate fields as necessary for your implementation
  
	public:
	Graph(int nNodes, int nEdges, string gFileName) {
		numNodes = nNodes;
		numEdges = nEdges;

		Gi = nullptr;
		parent = new int[numNodes];
		incycle = new bool[numNodes];
		visited = new int[numNodes];
		arrival = new int[numNodes];

		
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
		BSTWrapper* adjacentbst = new BSTWrapper[numNodes];
		//srand(time(0));
		srand(0); // for debugging
		int n1, n2; // indices in the array, not node vals
		int countEdges = 0;
		
		while (countEdges < numEdges) {
			do {
				n1 = rand() % numNodes;
				n2 = rand() % numNodes;
			} while (n1 == n2);
			if (adjacentbst[n2].addUnique(n1)&&adjacentbst[n1].addUnique(n2)){// assume both must hold or be violated simulatenously, which is true - when redundant have to only do one
				graphFile << n1+1 << " " << n2+1 << endl;
				countEdges++;
			}			
		}
		for(int i=0;i<numNodes;i++){
			nodes[i].adjacency = adjacentbst[i].tolist();
		}
		delete[] adjacentbst;
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
	delete Gi;
	delete[] parent;
	delete[] incycle;
	delete[] visited;
	delete[] arrival;
  }


  void modifiedDFS();
  void modifiedDFSrecursive(int root, BSTWrapper& tree, int& time);
  void printResults();
};


#endif
