#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T>
class LinkedListNode{

public:
  T data;
  bool consider;
  LinkedListNode<T> *next;

  LinkedListNode(T dat){
    this->data = dat;
    this->next = nullptr;
    consider = true;
  }
  ~LinkedListNode(){
    this->next = nullptr;
  }
};
template <typename T>
class LinkedList{
  LinkedListNode<T> *head;

public:
  LinkedList(){
    this->head = nullptr;
  }

  template <typename G>
  LinkedListNode<T> *findOne(G&& matcher){
    LinkedListNode<T> *cur = head;
    while (cur != nullptr){
      if (matcher(cur)) return cur;
      cur = cur->next;
    }
    return cur;
  }

  void insert(T data){
    LinkedListNode<T> *new_node = new LinkedListNode(data);
    new_node->next = this->head;
    this->head = new_node;
  }

  template <typename G>
  bool remove(G&& matcher){
    LinkedListNode<T> *cur = head, *prev = nullptr;
    while (cur != nullptr){
      if (matcher(cur)) break;
      prev = cur;
      cur = cur->next;
    }

    if(cur == nullptr) return false;
  
    if(prev != nullptr) prev->next = cur->next;
    delete cur;
    cur = nullptr;

    return true;
  }

  void clear(){
    LinkedListNode<T>* cur = this->head, *cur_p = nullptr;

    while(cur != nullptr){
      cur_p = cur;
      cur = cur->next;

      delete cur_p;
    }

    this->head = nullptr;
  }
  LinkedListNode<T>* getHead(){return this->head;}
};

template <typename T>
class BSTNode{
public:
  T data;
  BSTNode *left, *right, *parent;

  BSTNode(T dat){
    this->data = dat;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
  }
  BSTNode(T dat, BSTNode* par, bool left_child){
    this->data = dat;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = par;

    if(par != nullptr){
      if(left_child) par->left = this;
      else par->right = this;
    }
  }

  void printInfo(){
    cout<<this->data;
  }
};
template <typename T>
class BST
{
  // Add your own field and members here
  BSTNode<T>* root;

  void clearSubTree(BSTNode<T>* sub_root){
    if(sub_root == nullptr) return;

    this->clearSubTree(sub_root->left);
    this->clearSubTree(sub_root->right);

    if(sub_root != this->root){
      if(sub_root->parent->left == sub_root) sub_root->parent->left = nullptr;
      else sub_root->parent->right = nullptr;
    }else{
      this->root = nullptr;
    }

    delete sub_root;
    sub_root = nullptr;
  }

  void printBST_(BSTNode<T>* troot, const string& prefix, bool isLeft){
    if( troot != nullptr )   {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__" );

      // print the value of the node
      troot->printInfo();
      cout << endl;
      BSTNode<T> *curr = troot;
      bool pref_decider = (isLeft && this->root != troot);
      // string spacing = (this->root==troot) ? "" : "   ";
      troot = curr->left;
      // enter the next tree level - left and right branch
      this->printBST_(troot, prefix + (pref_decider ? "│   " : "    "), true);
      troot = curr->right;
      this->printBST_(troot, prefix + (pref_decider ? "│   ": "    "), false);
      troot = curr;
    }
    else {
      // cout << "NULL tree" << endl;
    }
  }
public:
  BST(){
    this->root = nullptr;
  }

  template <typename G>
  void insert(T dat, G&& lesser){
    if(this->root == nullptr){
      this->root = new BSTNode<int>(dat, nullptr, false);
      return;
    }
    BSTNode<T> *cur=this->root, *cur_p=nullptr;
    while(cur != nullptr){
      cur_p = cur;
      cur = lesser(dat, cur->data) ? cur->left : cur->right;
    }

    cur = new BSTNode(dat, cur_p, lesser(dat, cur_p->data));
  }

  void clear(){
    this->clearSubTree(this->root);
  }

  void printBST(){
    this->printBST_(this->root, "", true);
  }
  // Feel free to use the printBST function used earlier
};

class Node
{
public:
  int value;
  LinkedList<Node*> *adj;

  Node(){
    this->value = 0;
    this->adj = new LinkedList<Node*>();
  }
  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  LinkedList<BST<int>*> *dfs_bsts;
  bool *visited_once, *visited_twice;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    this->dfs_bsts = new LinkedList<BST<int>*>();

    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    // for(int i=1; i <= numNodes; i++) graphFile << i << endl;

    nodes = new Node[numNodes];
    this->visited_once = new bool[numNodes];
    this->visited_twice = new bool[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }

    srand(time(0));
    // srand(0);
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
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
      if(nodes[n1].adj->findOne([val = n2+1](LinkedListNode<Node*> *to_check){return to_check->data->value==val;}) != nullptr)
        continue;

      nodes[n1].adj->insert(&nodes[n2]);
      nodes[n2].adj->insert(&nodes[n1]);

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }
    // Add appropriate code as necessary for your implementation
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void modifiedDFS_perComponent(Node *cur, Node* prev, bool* visited, bool* revisited, BST<int>* dfs_bst);
  void printResults();
};

#endif
