#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class treeNode {
  public:
    int val;
    treeNode *left;
    treeNode *right;
    treeNode(){
      left = nullptr;
      right = nullptr;
      val = 0;
    }
};

class BST {
  // Add your own field and members here
  public:
  treeNode *root ;
  BST *next;

  BST(){
    root = nullptr;
    next = nullptr;
  }

  bool insert(int value) { 
    treeNode* x = root; //for checking
    treeNode* y = NULL; //for pointing to the parent
    treeNode* node = new treeNode();
    node->val = value;

    if(root == NULL){
        root = node;
        return true;
    }

    while(x != NULL){
        // cout<<"x not null";
        y = x;

        if(x->val >= value){ //equal values go to left
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    // node->parent = y;

    if(y->val >= value){
        y->left = node;
    }
    else{
        y->right = node;
    }
    
    return true;
    }

    void printBST(const string& prefix, bool isLeft)
    {
        if( root != nullptr )
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__" );

            // print the value of the node
            cout << root->val << endl;
            treeNode *curr = root;
            root = root->left;
            // enter the next tree level - left and right branch
            printBST( prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;
            printBST( prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }

  // Feel free to use the printBST function used earlier
};

class adjacencyList {
  public:
  int nodeIndex;
  int direction = 0;//means calling object to nodeIndex
  adjacencyList *next;

};

class Node {
 public:
  int value;
   adjacencyList *adjStart;
   adjacencyList *last;

   Node(){
    this->value = 0;
    this->adjStart = nullptr;
    this->last = nullptr;
   }

  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int *visited;
  bool *cycle;
  // bool *backtraced;
  Node *currNode;
  BST *trees;
  int numTrees;
  // Add appropriate fields as necessary for your implementation
  
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

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    cycle = new bool[numNodes];
    // backtraced = new bool[numNodes];
    visited = new int[numNodes];
    for(int i=0; i<numNodes; i++){
      visited[i] = 0;
      cycle[i] = false;
      // backtraced[i] = false;
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
    currNode = &nodes[0];

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
        n1 = 1 + rand() % numNodes;
        n2 = 1 + rand() % numNodes;
      } while (n1 == n2);

      nodes[n1-1].value = n1;
      nodes[n2-1].value = n2;

      if(nodes[n1-1].adjStart == nullptr){

        nodes[n1-1].adjStart = new adjacencyList();
        nodes[n1-1].adjStart->nodeIndex = n2-1;
        nodes[n1-1].adjStart->next = nullptr;
        nodes[n1-1].last = nodes[n1-1].adjStart;

      }
      else{
        adjacencyList *temp1 = nodes[n1-1].adjStart;
        bool alreadyP = false;
        while(temp1 != nullptr){
          if(temp1->nodeIndex == n2-1)
            alreadyP = true;
          temp1 = temp1->next;
        }
        if(alreadyP) continue;
        // if( !alreadyP ){
          // cout<< nodes[n1-1].value << "seg fault here not" <<endl;
          if(nodes[n1-1].last !=nullptr){
            // cout<<"not null"<<endl;
            nodes[n1-1].last->next = new adjacencyList();
            nodes[n1-1].last->next->nodeIndex = n2-1;
            nodes[n1-1].last->next->next = nullptr;
            nodes[n1-1].last = nodes[n1-1].last->next;
          }
          // cout<<" seg fault here not"<<endl;
        // }
      }

      if(nodes[n2-1].adjStart == nullptr){
        nodes[n2-1].adjStart = new adjacencyList();
        nodes[n2-1].adjStart->nodeIndex = n1-1;
        nodes[n2-1].adjStart->next = nullptr;
        nodes[n2-1].last = nodes[n2-1].adjStart;
      }
      else{
        adjacencyList *temp1 = nodes[n2-1].adjStart;
        // bool alreadyP = false;
        // while(temp1 != nullptr){
        //   if(temp1->node == &nodes[n1-1])
        //     alreadyP = true;
        //   temp1 = temp1->next;
        // }
        if( nodes[n2-1].last ){
          nodes[n2-1].last->next = new adjacencyList();
          nodes[n2-1].last->next->nodeIndex = n1-1;
          nodes[n2-1].last->next->next = nullptr;
          nodes[n2-1].last = nodes[n2-1].last->next;
        }
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      // cout<< "seg---"<<endl;
      graphFile << n1 << " " << n2 << endl;
      countEdges++;
    }
    // cout<<"came out"<<endl;
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
  // void DFS();
  void modifiedDFS();
  void printResults();
};

#endif
