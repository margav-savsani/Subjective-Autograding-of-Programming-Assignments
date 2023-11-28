#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <unistd.h>
class TreeNode{
  public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  TreeNode(int val){
    value = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

};
class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  TreeNode *root;
  public:
  BST(){
    root = NULL;
  };
	BST(TreeNode *root){
    this->root = root;
  }
  void printBST(const string& prefix, bool isLeft){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  }
  bool insert(int value){                  //insertion in bst
    TreeNode * z;
    z  = new TreeNode(value);
    if(root == nullptr){
      this->root = new TreeNode(value);
      return true;
    }
    
    TreeNode *y = NULL;
    TreeNode *x = root;

    while(x != NULL){
      //cout << "a";
      y = x;
      if(x->value > z->value){
        x = x->left;
      }
      else 
        x = x->right;
    }

    z->parent = y;
    
    if(y->value > z->value){
      y->left= z;
    }
    else
      y->right = z;
    return true;

  }
};

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  listOfObjects(){

  }
  // Destructor
  ~listOfObjects() {;}
};

class Node {
 public:
  int value;
  int visit;
  int par1;
  int par2;
  
  Node(int val ){
    value = val;
  }
  Node(){}
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  listOfObjects<Node*>**adjacent;           //ajacency list
  listOfObjects<BST*>* bstheads;             //list of bst roots
  int nodes_visited_once;                    //number of nodes visited once
  int nodes_visited_twice;                    //number of nodes visited twice
  int cc;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    adjacent = new listOfObjects<Node*>*[numNodes];
    nodes_visited_once = 0;
    nodes_visited_twice = 0;
    cc = 0;
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
      nodes[i].visit = 0;
      nodes[i].par1 = -1;
      nodes[i].par2 = -1;
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
      bool not_n2 = true;
      listOfObjects<Node*>* n1_adj = adjacent[n1];
      while(n1_adj != nullptr){
        if(n1_adj->object->value == n2+1){          //if n2 is already present in adjacency list of n1 do not add edge
          not_n2 = false;
        }
        n1_adj = n1_adj->next;
      }
      if(not_n2 == false){
        continue;
      }
      listOfObjects<Node*>* n1_last = adjacent[n1];   //find last position in adjacency list of n1 and at tht position add n2
      if(n1_last == nullptr){
        Node* n = &nodes[n2];
        listOfObjects<Node*>* first_node = new listOfObjects<Node*> (n);
        adjacent[n1] = first_node;
      }
      else{
        while(n1_last->next != nullptr){
          n1_last = n1_last->next;
        }
        Node* n = &nodes[n2];
        listOfObjects<Node*>* first_node = new listOfObjects<Node*> (n);
        n1_last->next = first_node;
        
      }                                              // do the same thing for n2 as above  ie to add n1 in adjacency of n2
      listOfObjects<Node*>* n2_last = adjacent[n2];
      if(n2_last == nullptr){
        Node* n = &nodes[n1];
        listOfObjects<Node*>* first_node = new listOfObjects<Node*> (n);
        adjacent[n2] = first_node;
      }
      else{
        while(n2_last->next != nullptr){
          n2_last = n2_last->next;
        }
        Node* n = &nodes[n1];
        listOfObjects<Node*>* first_node = new listOfObjects<Node*> (n);
        n2_last->next = first_node;
        
      }
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
  void dfs(int i , int par){
    nodes[i].visit++;
    if(nodes[i].visit == 1){                //if visit of this node is 1 ..increment number of nodes visited once
      nodes_visited_once++;
    }
    if(nodes[i].visit == 2){                // else increment nodes visited twice by  and decrease number of nodes visited once
      nodes_visited_once--;
      nodes_visited_twice++;
    }
   
    bstheads->object->insert(nodes[i].value);            //insert node's value in BST
    listOfObjects<Node *> *adj = adjacent[i];      
    while(adj != nullptr){                               //iterate through all adjacent 
      if(adj->object->visit < 2 && (adj->object->value != par)){   //if adjacent is not parent of curr node
        if(adj->object->par1-1 != i && adj->object->par2-1 != i){   //and we haven't traverse this path before do DFS and update parents accordingly
          if(adj->object->par1 == -1){
          adj->object->par1 = nodes[i].value;
          }
          else{
            adj->object->par2 = nodes[i].value;
          }
          dfs(adj->object->value - 1,i+1);
        }
        
      }
      adj = adj->next;
    }
  }
  void modifiedDFS();
  void printResults();
};

#endif
