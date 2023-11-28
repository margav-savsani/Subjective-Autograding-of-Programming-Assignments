#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


//class of BST node

class BST_node{
  public:
  int value;
  BST_node * left;
  BST_node * right;
  BST_node * parent;

  BST_node(int value){
    this->value = value;
    left = NULL;
    right = NULL;
    parent = NULL;
  }

  BST_node(){
    left = NULL;
    right = NULL;
    parent = NULL;
  }

};

class BST {
  public:
  // Add your own field and members here
  BST_node * root;
  BST * next;
  // Feel free to use the printBST function used earlier

    // constructor
    BST(){
      next = NULL;
      root = NULL;
    }

    //printBST from prev lab
    void printBST(const string& prefix, bool isLeft){
      if( root != nullptr )
      {
          cout << prefix;

          cout << (isLeft ? "|--" : "|__" );

          // print the value of the node
          cout << root->value << endl;
          BST_node *curr = root;
          root = root->left;
          // enter the next tree level - left and right branch
          printBST( prefix + (isLeft ? "│   " : "    "), true);
          root = curr->right;
          printBST( prefix + (isLeft ? "│   " : "    "), false);
          root = curr;
      }
    }

    // tooj from previous lab
    bool insert(int value){
    BST_node* to= new BST_node(value);//this is the node to be searched
    BST_node * parent_ptr;
    BST_node * child_ptr;
    child_ptr=root;
    parent_ptr=NULL;
    //loops continues till node is found
    while(child_ptr!=NULL){
        //traverse the tree to find the node
        parent_ptr=child_ptr;
        if(value<=child_ptr->value){
            //if the value is left move to left
            child_ptr=child_ptr->left;
        }
        else{
            //if the value is more, move to right
            child_ptr=child_ptr->right;
        }

    }
    //attatching the node to the tree
    //comparing its value with the value of the parent node and accordingly joining it in the BST
    //if the value is equal, I have added it to the left
    to->parent=parent_ptr;
    if(parent_ptr==NULL){
        root=to;
        return true;
    }
    else{
        if(to->value<=parent_ptr->value){
            parent_ptr->left=to;
            return true;
        }
        else{
            parent_ptr->right=to;
            return true;
        }
    }

    return false;
    }
};

// nodal class
class Node {
 public:
  int value;

  int instack;
  bool incycle;
  int count;
  bool connected;
  Node *next;
  int p1;
  int p2;
  Node *ref;

  //constructors
  Node(int value, int instack, bool incycle, int count, bool connected, Node *next){
    this->value = value;
    this->instack = instack;
    this->incycle = incycle;
    this->count = count;
    this->connected = connected;
    this->next = next;
  }

  //constructor
  Node(int value){
    this->value = value;
    this->instack = 0;
    this->incycle = 0;
    this->count = 0;
    this->connected = 0;
    this->next = NULL;
  }

  Node(){

  }

  // insert other fields and methods as appropriate
};

// storing the path to the node
class node_l{
  public:
    int value;
    node_l * prev;
    node_l * next;
  node_l(int value){
    this->value = value;
    prev = NULL;
    next = NULL;
  }
};

// main graph class
class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  BST * arr;
  int num_connected;

  // string str;
  node_l * start;

  Node *nodes;


  // Add appropriate fields as necessary for your implementation

 public:
 //constructor
  Graph(int nNodes, int nEdges, string gFileName) {
    start = NULL;
    // str = "";
    arr = NULL;
    num_connected = 0;
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
      //constructor
      // nodes[i].value = i+1;
      nodes[i].value = i + 1;
      nodes[i].instack = 0;
      nodes[i].incycle = 0;
      nodes[i].count = 0;
      nodes[i].connected = 0;
      nodes[i].next = NULL;
      nodes[i].p1 = 0;
      nodes[i].p2 = 0;
      nodes[i].ref = &nodes[i];
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges) {
      // cout<<countEdges<<endl;
      // cout<<numEdges<<endl<<endl;
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
      Node * traverse = & nodes[n1];
      // cout<<"tt"<<&nodes[n1]<<endl;
      // cout<<traverse<<endl;
      // cout<<traverse->next<<endl;

      bool already = false;
      while(traverse->next!=NULL){
        if(traverse->next->ref->value == n2 + 1){
          already = true;
          break;
        }
        traverse = traverse->next;
      }

      // if already inserted
      if (!already){
        Node *nex = new Node;
        nex->ref = &nodes[n2];
        traverse->next = nex;
      }

      else{
        continue;
        }

      // adjacency list addition of next element
      traverse = & nodes[n2];
      while(traverse->next!=NULL){
        traverse = traverse->next;
      }


      Node *nex = new Node;
      nex->ref = &nodes[n1];
      traverse->next = nex;

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
  void mod_DFS(Node* parent, Node* child, BST* bst);
};

#endif
