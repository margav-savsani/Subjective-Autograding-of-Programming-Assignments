#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class listOfObjects {
  public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  listOfObjects(){
    next = prev = nullptr;
  }

  listOfObjects(T val){
    object = val;
    next = prev = nullptr;
  }

  ~listOfObjects(){;}
};

class Node{
  public:
  int value;

  Node(){
    value = 0;
  }

  Node(int val){
    value = val;
  }

  // insert other fields and methods as appropriate
};



class TreeNode {   
public:

  TreeNode* left;
  TreeNode* parent;
  TreeNode* right;
  int value;


  TreeNode(){
    this->value = -1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  TreeNode(int val){
    this->value = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  ~TreeNode() {;}
  
};


class adjacencyList{
  public:
  Node n;
  listOfObjects<Node> *list;

};


class BST {
  // Add your own field and members here
  public:
    TreeNode *root;

    BST(){
      this->root = nullptr;
    }
    BST(TreeNode *root){
      this->root = new TreeNode();
      this->root = root;
    }

    void insert(int val){
      TreeNode *currNode = root;
      TreeNode *parentNode = nullptr;

      int i = -1;
      while(currNode != nullptr){
        if(currNode->value <= val){
          //currNode->parent = parentNode;
          parentNode = currNode;
          currNode = currNode->right;
          i = 0;
        }
        else if(currNode->value > val){
          //currNode->parent = parentNode;
          parentNode = currNode;
          currNode = currNode->left;
          i = 1;
        }
        //else return false;
      }

      if(i == 1){
        parentNode->left = new TreeNode(val);
        parentNode->left->parent = parentNode;
        i = -1;
      }
      else if(i == 0){
        parentNode->right = new TreeNode(val);
        parentNode->right->parent = parentNode;
        i = -1;
      }
      else{
        root = new TreeNode(val);
      }
    }

    bool find(int val){
      TreeNode *currNode = root;
      TreeNode *parentNode = nullptr;

      while(currNode != nullptr){
        if(currNode->value == val){
          return true;
        }
        else if(val < currNode->value){
          parentNode = currNode;
          currNode = currNode->left;
        }
        else if(val > currNode->value){
          parentNode = currNode;
          currNode = currNode->right;
        }
      }

      return false;
    }

    void printBST(TreeNode *root, const string& prefix, bool isLeft){
      if( root != nullptr )   {
        cout << prefix;
        
        cout << (isLeft ? "|--" : "|__" );
        
        // print the value of the node
        //root->printInfo();
        cout << root->value << endl;
        cout << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(root, prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(root, prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
      }
      else {
        cout << "NULL tree" << endl;
      }
    }    
  // Feel free to use the printBST function used earlier
};







class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  adjacencyList *adjList;

  int *num_visited; // number of times the node is visited
  BST *b;
  //int *num_nodes_cycle;
  //b = new BST[num_connected_com];

  int num_connected_com;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    num_visited = new int[numNodes];
    
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    for(int i = 0; i < numNodes; i++){
      num_visited[i] = 0;
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    adjList = new adjacencyList[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      adjList[i].n = nodes[i];
      adjList[i].list = nullptr;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    int i = 0;
    bool edge_exists = false;
    listOfObjects<Node> *l;
    listOfObjects<Node> *l1;
    

    while (countEdges < numEdges) {
      //cout << "I am here" << endl;
      do {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);

      if(adjList[n1].list == nullptr){
        //cout << "lol" << endl;
        adjList[n1].list = new listOfObjects<Node>(nodes[n2]);
        if(adjList[n2].list == nullptr){
          adjList[n2].list = new listOfObjects<Node>(nodes[n1]);
        }
        else{
          l = adjList[n2].list;
          while(l != nullptr){
            l1 = nullptr;
            l1 = l;
            l = l->next;
          }
          l1->next = new listOfObjects<Node>(nodes[n1]);
          l1->next->prev = l1;
        }
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
      else{
        l = adjList[n1].list;
      
        while(l != nullptr){
          if(l->object.value == nodes[n2].value){
            //cout << "Hi" << endl;
            edge_exists = true;
            break;
          }
          //cout << l->object.value << endl;
          l1 = nullptr;
          l1 = l;
          l = l->next;
        }
        //edge_exists = false;
        if(!edge_exists){
          //cout << "yes" << endl;
          l1->next = new listOfObjects<Node>(nodes[n2]);
          l1->next->prev = l1;
          edge_exists = false;
          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;  // check this part

          if(adjList[n2].list == nullptr){
            adjList[n2].list = new listOfObjects<Node>(nodes[n1]);
          }
          else{
            l = adjList[n2].list;
            while(l != nullptr){
              l1 = nullptr;
              l1 = l;
              l = l->next;
            }
            l1->next = new listOfObjects<Node>(nodes[n1]);
            l1->next->prev = l1;
          }

          /*
          l = adjList[n2].list;
          while(l != nullptr){
            if(l->object.value == nodes[n1].value){
              edge_exists = true;
              break;
            }
            else{
              l1 = l;
              l = l->next;
            }
          }
          if(!edge_exists){
            l1->next = new listOfObjects<Node>(nodes[n2]);
            l1->next->prev = l1;
            //countEdges++;
            edge_exists = false;
          }
          */
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
