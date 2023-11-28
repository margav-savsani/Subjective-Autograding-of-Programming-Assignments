#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class point{             //node of list to store edges
	public:
		int a,b;
		point* next;
		point(int x, int y){
			a=x;b=y;
			next=NULL;
		}
};

class node2{			//node of list of indices
	public:
	int index;
	node2* next;
	node2* prev;
	node2(int i){
		index=i;
		next=NULL;
		prev=NULL;
	}
};

class node3{         //bst node
  	public:
  		int val;
  		node3* left;
  		node3* right;
  		node3(){
  		  	left=NULL;
  		  	right=NULL;
  		}
};

class BST {
  	// Add your own field and members here
  	public:
  		node3* root;
  		BST(){
  		  	root=NULL;
  		}
  		// Feel free to use the printBST function used earlier
  		void insert(int k){            //inserting node
  		  	if(root==NULL){
  		    	root=new node3;			//root case
			  	root->val=k;
  		  	}
  		  	else{
  		    	node3* t;
  		    	t=new node3;
				  	t->val=k;
  		    	node3* tra;
  		    	tra=root;
  		    	node3* par;
  		    	while(tra!=NULL){
  		    	  	par=tra;
  		    	  	if(k<tra->val){
  		    	  	  	tra=tra->left;
  		    	  	}
  		    	  	else{
  		    	  	  	tra=tra->right;
  		    	  	}
				  	}
  		    	  	if(k < par->val){   //insert
  		    	  	  	par->left=t;
  		    	  	}
  		    	  	else{
  		    	  	  	par->right=t;
  		    	  	}
  		  	}	
  		}
  		void printBST(const string& prefix, bool isLeft=false){
  		  	if( root != nullptr ){
  		      	cout << prefix;
  		      	cout << (isLeft ? "|--" : "|__" );
  		      	cout << root->val << endl;
  		      	node3 *curr = root;
  		      	root = root->left;
  		      	printBST( prefix + (isLeft ? "│   " : "    "), true);
  		      	root = curr->right;
  		      	printBST( prefix + (isLeft ? "│   " : "    "), false);
  		      	root = curr;
  		  	}
  		}
};	

class Node {
 	public:
  		int value;
  		int visited;			//visiting status
  		node2* adja;			//adjacent list
  		bool cycle;
  		Node(){
  		  	visited=0; 		//can take 0,1,2
			adja=NULL;
			cycle=false;
  		}

  // insert other fields and methods as appropriate
};

class Graph {
  	int numNodes;
  	int numEdges;
  	fstream graphFile;
	int conncomp;
  	Node *nodes;
 	public:
  		Graph(int nNodes, int nEdges, string gFileName) {
    	numNodes = nNodes;
    	numEdges = nEdges;
    	graphFile.open(gFileName, ios::out);
    	if (!graphFile.is_open()) {
    	  	cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
    	  	exit(-1);
    	}

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;
	conncomp=0;
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
      bool t=false;
		node2* x=nodes[n1].adja;
		while(x!=NULL){
			if(x->index==n2){			//if same pair of numbers are generated
				t=true;
				break;
			}
			x=x->next;
		}
      if(t){continue;}
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;       

	node2* k=nodes[n1].adja;
	if(nodes[n1].adja==NULL){
		nodes[n1].adja=new node2(n2);        //adding into adjacent list
	}
	else{
		while(k->next!=NULL){
			k=k->next;
		}
		k->next=new node2(n2);
	}

	node2* k1=nodes[n2].adja;
	if(nodes[n2].adja==NULL){
		nodes[n2].adja=new node2(n1);       
	}
	else{
		while(k1->next!=NULL){
			k1=k1->next;
		}
		k1->next=new node2(n1);
	}
    }
  }

    // Add appropriate code as necessary for your implementation
  
      
  ~Graph() {
    if(graphFile.is_open()) {
      	graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void modDFS(BST* b, int i, int par, node2* traversal, point* edg);
  void modifiedDFS();
  void printResults();
};

#endif
