#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef BST_H
#define BST_H
#endif



struct TreeNode{
    // int JourneyCode;	// Train Number
    int price;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    
    // Constructors
  
    TreeNode() : price(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice) : price(jrnyPrice), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), left(leftChild), right(rightChild), parent(parent) {}
    

};



class BST{
	TreeNode *root;


public:

	BST(){
    root = nullptr;
  }
	
	void printBST(const string& prefix, bool isLeft){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->price << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }  }
	

	bool insert(int price){
    TreeNode *parent_node = nullptr;
    TreeNode *child_node = root;
    TreeNode *node_to_insert = new TreeNode(price);

    while(child_node != nullptr){
        parent_node = child_node;
        if (price >= child_node->price){
            child_node = child_node->right;
        }
        else{
            child_node = child_node->left;
        }
    }
    
    node_to_insert->parent = parent_node;
    if (parent_node == nullptr){
        root = node_to_insert;
    }
    else if(price>=parent_node->price){
        parent_node->right = node_to_insert;
    }
    else{
        parent_node->left = node_to_insert;
    }
    return true;
  }

};






class linked_list{
  public:
  int node_number;
  linked_list* next;
  linked_list* prev;
  linked_list(){
    next=nullptr;
    prev = nullptr;
  }
};





class Node {
 public:
  int value;
  linked_list* start;
  linked_list* end;
  linked_list* gone_and_backtracked_s;
  linked_list* gone_and_backtracked_e;

  
  Node(){
    start=nullptr;
    end=nullptr;
    gone_and_backtracked_s=nullptr;
    gone_and_backtracked_e=nullptr;
  }

  bool has_connection(int connecting_val){
    if(start==nullptr){
      return false;
    }
    linked_list* marker = start;
    while (marker!=nullptr){
      if(marker->node_number==connecting_val){
        return true;
      }
      marker = marker->next;
    }
    return false;
  }

  void add_to_backtracking_list(int num){
    if(gone_and_backtracked_s==nullptr){
      gone_and_backtracked_s = new linked_list;
      gone_and_backtracked_s->node_number=num;
      gone_and_backtracked_e=gone_and_backtracked_s;
    }
    else{
      gone_and_backtracked_e->next = new linked_list;
      gone_and_backtracked_e->next->node_number = num;
      gone_and_backtracked_e->next->prev = gone_and_backtracked_e;
      gone_and_backtracked_e = gone_and_backtracked_e->next;
    }
  }

  bool exists_in_to_backtracking_list(int num){
    linked_list* marker = gone_and_backtracked_s;
    while(marker!=nullptr){
      if(marker->node_number==num){
        return true;
      }
      marker = marker->next;
    }
    return false;
  }
  // insert other fields and methods as appropriate
};


class BST_linked_list{
  public:
  BST* object;
  BST_linked_list* next;
  BST_linked_list(){
    object = nullptr;
    next = nullptr;
  }
};


class Graph {
  int num_components;
  int num_ones;
  int num_twos;
  int num_cycles;


  int numNodes;
  int numEdges;
  fstream graphFile;

  BST_linked_list* my_bst_list;
  BST_linked_list* bst_list_marker;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    num_components = 0; num_ones=0; num_twos =0; num_cycles = 0;
    my_bst_list = nullptr;
    bst_list_marker = nullptr;
    numNodes = nNodes;
    numEdges = nEdges;
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
      } 
      while (n1 == n2);

      if(nodes[n1].has_connection(n2)){
        continue;
      }
      
      linked_list *edge = new linked_list;
      edge->node_number = n2;
      
      if(nodes[n1].start==nullptr){
        nodes[n1].start = edge;
        nodes[n1].end = edge;
      }
      else{
        nodes[n1].end->next = edge;
        edge->prev=nodes[n1].end;
        nodes[n1].end = nodes[n1].end->next;
      }

      linked_list *edge2 = new linked_list;
      edge2->node_number = n1;

      if(nodes[n2].start==nullptr){
        nodes[n2].start = edge2;
        nodes[n2].end = edge2;
      }
      else{
        nodes[n2].end->next = edge2;
        edge2->prev=nodes[n2].end;
        nodes[n2].end = nodes[n2].end->next;
      }
      
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;


      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

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
