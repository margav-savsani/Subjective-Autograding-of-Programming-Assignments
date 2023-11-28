#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define NEG_INF -1000

#include <time.h>
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

template <typename T> class myList{
  public:
  listOfObjects<T> * journeys;// HEAD of the linked list
  listOfObjects<T> * tail; // TAIL of the linked list
  int size;

  myList(){
    journeys = nullptr; tail = nullptr; size = 0;
  }
  void add(T num){
    listOfObjects<T>* toAdd = new listOfObjects<T>(num);
    if(tail!=nullptr){// non-empty queue
      tail->next = toAdd;
      toAdd->prev = tail;
      tail = tail->next;
    }
    else{// empty queue
      journeys = toAdd;
      tail = toAdd;
    }
    // increase the size of vector by 1
    size++;
  }
  T remove(){
    T last;
    if(size==0){
      return nullptr; // cannot remove anymore
    }
    else if (size==1){
      last = journeys->object;
      journeys = nullptr;
      tail = nullptr;
    }
    else{
      last = tail->object;
      tail = tail->prev;
    }
    size--; // reduce the size of the queue
    return last;
  }
  bool find(T num){ // do not use find for other than T = int 
    listOfObjects<T> * iterator = journeys;
    bool found = false;
    while(iterator!=nullptr){
      if (iterator->object == num){
        found = true;
        break;
      }
      iterator = iterator->next;
    }

    return found;
  }
  void print(){
    listOfObjects<T> * iterator = journeys;
    int i = 0;
    while(iterator!=nullptr){
      cout<<"Connected Component: "<<(i+1)<<endl;
      iterator->object->printBST("", false);
      cout<<"-------------------------------------------------------------------------"<<endl;
      iterator = iterator->next; 
      i++;
    }
  }
};
struct TreeNode{
  int value;
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  
  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  
  TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
  
  TreeNode(int value, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(value), left(leftChild), right(rightChild), parent(parent) {}
};
class BST{
  TreeNode *root;
  
public:
  // ************************************************************
  // Methods for Part I
  
  // Constructors!
  BST() {root = nullptr; }
  BST(TreeNode *curr_root) {root = curr_root;}

  // Implement your own destructor
  ~BST() {};
  
  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(int value)
      {
      // To check whether the current pivot is already present in the BST
      // if (find(value)){
      //   return false;
      // }
      // initializes a node with the given parameters
        TreeNode *toInsert = new TreeNode;
        if (toInsert != NULL)
        {
            toInsert->value = value;
        }
        if (root == NULL)
        {
            root = toInsert;
            return true;
        }
        TreeNode *y = new TreeNode;
        TreeNode *x = root;

        while (x != NULL)
        {
            y = x;
            if (value < (x->value))
            {
                x = (x->left);
            }
            else
            {
                x = (x->right);
            }
        }
        toInsert->parent = y;
        if (y == NULL)
        {
            root = toInsert;
            return true;
        }
        else if (toInsert->value < y->value)
        {
            y->left = toInsert;
            return true;
        }
        else
        {
            y->right = toInsert;
            return true;
        }
    }

// Return True, if the ticket with given attributes is found, false otherwise
bool find(int value)
{
      TreeNode *x = root;
      while (x != NULL && (value != (x->value)))
      {

          if (value < (x->value))
          {
              x = (x->left);
          }
          else
          {
              x = (x->right);
          }
      }
      if (x == NULL)
      {
          return false;
      }
      if ((value == (x->value)))
      {
          return true; // both the prices and journey code matches
      }
      else
      {
          return false; // node not found
      }
}
void printBST(const string& prefix, bool isLeft)
  {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = curr->left;
        // enter the next tree level - left and right branch
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
  Node* next;
  Node* list;
  myList<int> backtrack;

  Node(int i){
    value = i;
    next = nullptr;
    list = nullptr;
  }
  Node(){
    value = 0;
    next = nullptr;
    list = nullptr;
  }

  // insert other fields and methods as appropriate
};

class Graph {
  public:
  int numNodes;
  int numEdges;
  fstream graphFile;
  int* visited;
  bool* inCycle;
  Node *parentArray;
  Node *nodes;
  int* arr;
  

  myList<BST *> forest;
  void printGraph(){
    for (int i = 0; i<numNodes;i++){
      cout<<nodes[i].value<<" -----> ";

      Node* currNode = nodes[i].list;
      while(currNode!=nullptr){
        cout<<currNode->value<<" | ";
        currNode = currNode->next;
      }
      cout<<endl;
    }
  }
  int deleteParent(Node* node1, Node* node2){ // deletes node 2 from the adjacency list of node 1
        bool found = false;
        if(nodes[node1->value -1].list == nullptr){
          return -1;
        }
        Node* inList = nodes[node1->value -1].list;

        while(inList->next!=nullptr){
          if(inList->value == node2->value){
            found = true;
            break;
          }
          inList = inList->next;
          }
          if(inList->value == node2->value){
              found = true;
          }
        if(!found){return -1;}
        else{ // sets the value of node to negative - which is equivalent to removing the node
          inList->value = NEG_INF;
          return 1;
        }
      
  }
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visited = new int[numNodes];
    inCycle = new bool[numNodes];
    parentArray = new Node[numNodes];
    arr = new int[numNodes];
    for (int i = 0 ;  i< numNodes; i++){
      arr[i] = 10000;
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
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

      bool insert1 = false;
      bool insert2 = false;
      // Add n2 to the list of n1
      Node* toAdd = new Node(n2+1);
      Node* currNode = nodes[n1].list;

      if (currNode==nullptr){
        nodes[n1].list = toAdd;
        insert1 = true;
      }
      else{
        bool found = false;
        while(currNode->next!=nullptr){
          if(currNode->value == n2+1){
            found = true;
            break;
          }
          currNode = currNode->next;
        }
        if(currNode->value == n2+1){
            found = true;
        }

        if (!found){
          currNode->next = toAdd;
          insert1 = true;
        }
      }
      // Add n1 to the list of n2
      toAdd = new Node(n1+1);
      currNode = nodes[n2].list;

      if (currNode==nullptr){
        nodes[n2].list = toAdd;
        insert2 = true;
      }
      else{
        bool found = false;
        while(currNode->next!=nullptr){
          if(currNode->value == n1+1){
            found = true;
            break;
          }
          currNode = currNode->next;
        }
        if(currNode->value == n1+1){
            found = true;
        }

        if (!found){
          currNode->next = toAdd;
          insert2 = true;
        }
      }
      if(insert1 && insert2){
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  void myDFS(int v, int prev);
};

#endif
