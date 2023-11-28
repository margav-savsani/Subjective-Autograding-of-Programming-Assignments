#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


struct TreeNode{
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;

  TreeNode(int val){
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    value = val;
  }

  void printInfo(){
    cout << value;
  }
};

void printBinaryTree(TreeNode *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->printInfo();
    cout << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  
}

class BST {
  TreeNode* root = nullptr;

public:
  void print(){
    printBinaryTree(root, "", false);
  }

  void insert(int val){
      
  TreeNode *temp = new TreeNode(val);

  if (root == nullptr)
  {
    root = temp;
    return;
  }

  TreeNode *next_ptr;
  TreeNode *parent_to_add = root;

  if (temp->value <= parent_to_add->value)
  {
    next_ptr = root->left;
  }

  else
    next_ptr = root->right;

  while (next_ptr != nullptr)
  {
    parent_to_add = next_ptr;

    if (temp->value <= parent_to_add->value)
    {
      next_ptr = parent_to_add->left;
    }

    else
      next_ptr = parent_to_add->right;
  }

  if (temp->value <= parent_to_add->value)
  {
    parent_to_add->left = temp;
    temp->parent = parent_to_add;
  }

  else
  {
    parent_to_add->right = temp;
    temp->parent = parent_to_add;
  }

  }
};

struct LinkedListNode{
  int value;
  LinkedListNode* prev = nullptr;
  LinkedListNode* next = nullptr;
};

class LinkedList{
  LinkedListNode* head = nullptr;

public:

  void insert(int value){
    if(head == nullptr){
      head = new LinkedListNode;
      head->value = value;
      return;
    }

    LinkedListNode* temp = head;
    while(temp->next != nullptr){
      temp = temp->next;
    }

    temp->next = new LinkedListNode;
    temp->next->prev = temp;
    temp->next->value = value;
    return;
  }

  bool isPresent(int value){
    LinkedListNode* temp = head;
    while(temp != nullptr){
      if(temp->value == value){
        return true;
      }

      temp = temp->next;
    }

    return false;
  }

  LinkedListNode* getHead(){
    return head;
  }
};


class Node {
 public:
  int value;
  bool isInCycle = false;
  int parent = -1;
  int parent1  = -1, parent2 = -1;
  LinkedList AdjacenyList;
  int arrivalTime;
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

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

      if(nodes[n1].AdjacenyList.isPresent(n2 + 1)){
        continue;
      }

      nodes[n1].AdjacenyList.insert(n2 + 1);
      nodes[n2].AdjacenyList.insert(n1 + 1);

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

  void myDFS(int nodeNum, int* visited, BST* tree);
  void actualDFS(int nodeNum, bool* visited, int &time);
};



#endif
