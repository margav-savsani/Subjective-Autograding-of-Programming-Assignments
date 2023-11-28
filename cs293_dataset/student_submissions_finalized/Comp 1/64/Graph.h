#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class BSTNode
{
  public:
    int value;
    BSTNode *left;  // Left Child of this Node (NULL, if None)
    BSTNode *right; // Right Child of this Node (NULL, if None)
    BSTNode *parent; //parent of node

    BSTNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
    BSTNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    BSTNode(BSTNode *leftchild, BSTNode *rightchild, BSTNode *parentt, int val) : value(val), left(leftchild), right(rightchild), parent(parentt) {}
};

class BST
{
  // Add your own field and members here
  // Feel free to use the printBST function used earlier
  public:
    BSTNode *root;
    BST()
    {
      root = nullptr;
    }

    BST(BSTNode *root1)
    {
      root = root1;
    }
//insert the node in BST
    void insert(int value)
    {
      BSTNode *y = nullptr;
      BSTNode *x = root;
      while (x != nullptr)
      {
        y = x;
        if (value < x->value)
        {
          x = x->left;
        }
        else
        {
          x = x->right;
        }
      }
      BSTNode *z = new BSTNode(value);
      z->parent = y;
      if (y == nullptr)
      {
        root = z;
      }
      else if (value < y->value)
      {
        y->left = z;
      }
      else
      {
        y->right = z;
      }
      return;
    }

    void printBST(const string& prefix, bool isLeft=false)
    {
        if( root != nullptr )
        {
            cout << prefix;
            cout << (isLeft ? "|--" : "|__" );
            // print the value of the node
            cout << root->value << endl;
            BSTNode *curr = root;
            root = root->left;
            // enter the next tree level - left and right branch
            printBST( prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;
            printBST( prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }


};

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

class Node
{
public:
  int value;
  Node* parent1;
  Node* parent2;
  listOfObjects<Node*> *adjacency;
  bool visited1;
  bool visited2;
  int start;
  int end;
  bool isInCycle;

  Node(int val){
    value = val;
    adjacency = nullptr;
    parent1=nullptr;
    parent2=nullptr;
    start=-1;
    end=-1;
    isInCycle=true;
  }

  Node(){
    value = 0;
    adjacency = nullptr;
    parent1=nullptr;
    parent2=nullptr;
    start=-1;
    end=-1;
    isInCycle=true;
  }

//function to detect if a node is a leaf of a graph i.e. if a node has only one element in its
//adjacency list
  bool isEndNode(){
    int count = 0;
    listOfObjects<Node*>* x = adjacency;
    while(x!=nullptr){
      count++;
      x=x->next;
    }
    if(count>=2){
      return false;
    }else{
      return true;
    }
  }
//are the nodes adjacent
  bool isNodeInAdj(Node* a){
    listOfObjects<Node*>* temp = adjacency;
    if(temp!=nullptr){
      if(temp->object->value == a->value){
        return true;
      }
      temp=temp->next;
    }
    return false;
  }
  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  int numConnected;
  fstream graphFile;
  int numCycles;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    numConnected = 0;
    numCycles=0;
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
      bool found1 = false;
      bool found2 = false;
      if(nodes[n1].adjacency==nullptr){
        Node* node1 = &nodes[n2];
        nodes[n1].adjacency = new listOfObjects<Node*>(node1);
      }else{
        listOfObjects<Node*>* temp = nodes[n1].adjacency;
        while(temp!=nullptr){
          if(temp->object->value == n2+1){
            found1 = true;
            break;
          }
          temp = temp->next;
        }
        if(!found1){
          Node* node2 = &nodes[n2];
          temp = nodes[n1].adjacency;
          while(temp->next!=nullptr){
            temp=temp->next;
          }
          temp->next = new listOfObjects<Node*>(node2);
        }
      }

      if(nodes[n2].adjacency==nullptr){
        Node* node3 = &nodes[n1];
        nodes[n2].adjacency = new listOfObjects<Node*>(node3);
      }else{
        listOfObjects<Node*>* temp = nodes[n2].adjacency;
        while(temp!=nullptr){
          if(temp->object->value == n1+1){
            found2 = true;
            break;
          }
          temp = temp->next;
        }
        if(!found2){
          Node* node4 = &nodes[n1];
          temp=nodes[n2].adjacency;
          while(temp->next!=nullptr){
            temp=temp->next;
          }
          temp->next = new listOfObjects<Node*>(node4);
        }
      }

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      if(!found1 && !found2){
        countEdges++;
      }
    }
    cout<<"ADJACENCY LIST OF GRAPH"<<endl;
    for(int i=0; i<numNodes; i++){
      listOfObjects<Node*> *p = nodes[i].adjacency;
      cout<<i+1<<"===";
      while(p!=nullptr){
        cout<<p->object->value;
        if(p->next!=nullptr){
          cout<<"<--";
        }
        p=p->next;
      }cout<<endl;
    }
  }

  BST * myDFS(int index, int index_parent, bool visited_once[], bool visited_twice[]);
  void DFS(int index);
  void modifiedDFS();
  void print1(bool visited_once[]);
  void print2(bool visited_twice[]);

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
  void printResults();
  
};

#endif
