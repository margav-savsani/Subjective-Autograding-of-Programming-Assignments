#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

//listOfObjects class from previous labs
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

//stack implementation using listOfObjects
template <typename T> class my_stack{
  public:
    listOfObjects<T>* list;
    listOfObjects<T>* tail;
    my_stack(){
      list = nullptr;
      tail = nullptr;
    }
    void insert(T obj){
      if(list == nullptr){
        list = new listOfObjects<T>(obj);
        tail = list;
      }
      else{
        tail->next = new listOfObjects<T>(obj);
        tail->next->prev = tail;
        tail = tail->next;
      }
    }
    T pop(){
      T res;
      if(list != nullptr){
        if(tail->prev != nullptr){
          auto temp = tail;
          res = tail->object;
          tail->prev->next = nullptr;
          tail = tail->prev;
          delete temp;
          //tail = temp->prev;
        }
        else{
          res = tail->object;
          list = nullptr;
          delete tail;
          tail = nullptr;
        }
      }
      return res;
    }
    bool isEmpty(){
      return (list == nullptr);
    }
    void print(){
      cout << "Stack contains: ";
      if(list != nullptr){
        auto trav = list;
        
        while(trav != nullptr){
          cout << trav->object << " ";
          trav = trav->next;
        }
        cout << endl;
      }
    }
};

// tree node class
template <typename T> class TreeNode{
  public:
  TreeNode* left;
  TreeNode* right;
  //TreeNode* parent;
  T obj;
  TreeNode(T obj){
    left = nullptr;
    right = nullptr;
    this->obj = obj;
  }


};

//BST with insert
template <typename T> class BST
{
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  public:
  TreeNode<T>* root;
  BST(T obj){
    root = new TreeNode<T>(obj);
  }
  BST(){
    root = nullptr;
  }
  void insert(T newobj){
    if(root == nullptr){
      root = new TreeNode<T>(newobj);
    }
    else if(root != nullptr){
      auto trav = root;
      while(true){
        if(newobj >= trav->obj){
          if(trav->right == nullptr){
            trav->right = new TreeNode<T>(newobj);
            break;
          }
          else{
            trav = trav->right;
          }
        }
        else if(newobj < trav->obj){
          if(trav->left == nullptr){
            trav->left = new TreeNode<T>(newobj);
            break;
          }
          else{
            trav = trav->left;
          }
        }
      }
    }
  }

};

class Node
{
public:
  int value;
  listOfObjects<int>* adj;  //adjancency list(stores node index)
  listOfObjects<int>* tail;   
  my_stack<int>* parents;  //stores the parents' indices(note that a node can have atmost 2 parents )
  bool incycle;  //stores if it is a cycle node
  int stacknum;   //stores the number of occurences in the stack
  // insert other fields and methods as appropriate
  Node(int value){
    this->value = value;
    adj = nullptr;
    tail = nullptr;
    parents = new my_stack<int>;
    incycle = false;
    stacknum = 0;
  }
  Node(){
    adj = nullptr;
    tail = nullptr;
    parents = new my_stack<int>;
    incycle = false;
    stacknum = 0;
  }
  void insert_adj(int node_ind){   //helper function to create adjacency ist
    if(adj == nullptr){
      adj = new listOfObjects<int>(node_ind);
      tail = adj;
    }
    else{   
      tail->next = new listOfObjects<int>(node_ind);
      tail->next->prev = tail;
      tail = tail->next;
    }
  }
  bool isParent(int nod){    //checks if nod is a parent of the current node
    auto trav = parents->list;
    while(trav != nullptr){
      if(nod == trav->object){
        return true;
      }
      trav = trav->next;
    }
    return false;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  int cyclenodes;
  Node *nodes;
  my_stack<BST<int>*>* trees_gr;   //stores the list of trees
  int* vis;   //stores the visited array
  int comps;   //stores the number of connected components

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    comps = 0;
    
    cyclenodes = 0;
    trees_gr = new my_stack<BST<int>*>;
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

    nodes = new Node[numNodes];
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
      auto adj1 = nodes[n1].adj;
      bool ispres = false;
      while(adj1 != nullptr){  
        if(adj1->object == n2){
          ispres = true;
          break;
        }
        adj1 = adj1->next;
      }
      if(ispres){continue;}   //n1 and n2 are already adjacent, continue the loop

      nodes[n1].insert_adj(n2);  //n1 is adjacent to n2 and vice versa since undirected graph
      nodes[n2].insert_adj(n1);

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
  void printResults();
  int checkCycles(int node, bool* visited_new, int*, int*, bool*, int*);
  void DFS(int, int*, my_stack<int>*, BST<int>*);
};

#endif
