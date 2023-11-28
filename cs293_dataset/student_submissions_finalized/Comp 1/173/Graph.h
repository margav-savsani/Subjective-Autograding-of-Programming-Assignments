#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TNode {   // https://github.com/AWorldOfChaos/CS293-2022-Solutions/blob/main/Lab%203/BST.cpp
	int value;
	TNode* left, *right, *parent;
	TNode(): value(-1), left(nullptr), right(nullptr), parent(nullptr) {}
	TNode(int v): value(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
	TNode* root;
	public:
		BST() {root=NULL;}
		BST(TNode* root) {this->root=root;}
		bool insert(int v) {
			if(root==NULL) {
				root= new TNode(v);
				return true;
			}

			TNode *curr=root;
			while (true) {
				if(v >= curr->value) {
					if (curr->right != nullptr) curr=curr->right;
					else {
						curr->right = new TNode(v);
						break;
					}
				}
				else {
					if (curr->left != nullptr) {
						curr = curr->left;
					}
					else {
						curr->left = new TNode(v);
					}
				}
			}
			return true;
		}

		void printBST(const string& prefix, bool isLeft=false)
		{
    	if( root != nullptr )
    	{
      	  cout << prefix;

  	      cout << (isLeft ? "|--" : "|__" );

  	      // print the value of the node
    	    cout << root->value << endl;
      	  TNode *curr = root;
        	root = root->left;
        	// enter the next tree level - left and right branch
        	printBST( prefix + (isLeft ? "│   " : "    "), true);
        	root = curr->right;
        	printBST( prefix + (isLeft ? "│   " : "    "), false);
        	root = curr;
    	}
		}
			
};

struct list {
  int value;
  list* next;
  list () {value=-1;next=nullptr;}
  list (int value) {this->value =value; next=nullptr;}
};

void del(list **x , int v){
  list *r=*x;
  list *prev=nullptr;
  if(r!=nullptr && r->value==v){
    *x=r->next;
    delete r;
    return;
  }
  else{
    while(r!=nullptr && r->value!=v){
      prev=r;
      r=r->next;
    }
    if(r==nullptr)
			return;
    prev->next=r->next;
    delete r;
    return;
  }

}


class Node {
 public:
  int value;
  list* adj;
  Node () {adj=new list(-1);}
  // insert other fields and methods as appropriate
};


class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
	int *visited;
  int numComp;
  Node *nodes;
	BST* t;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visited = new int[numNodes] (); // all are initialized to zeros
    numComp = 1;
		t = new BST[numNodes];
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

      list* currNode1=nodes[n1].adj;

      list* currNext1=currNode1->next;
      bool flag=false; // used to check if the edge already exists
      while (currNext1 != nullptr) {
        if (currNode1->value == n2+1) {flag=true; break;}
        currNext1=currNext1->next;
        currNode1 = currNode1->next;
				if (currNode1->value == n2+1) {flag=true; break;}   // don't erase this
      }
      if (flag) continue;


      currNode1->next = new list(n2+1);
      list* currNode2=nodes[n2].adj;
      list* currNext2=currNode2->next;
      while (currNext2 != nullptr) {
        currNext2=currNext2->next;
        currNode2 = currNode2->next;
      }
      currNode2->next = new list(n1+1);

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

  void modifiedDFS();
  void printResults();
};

#endif
