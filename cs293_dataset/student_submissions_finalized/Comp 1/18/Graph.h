#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>


using namespace std;

struct TreeNode{
  int value;
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  TreeNode(){
    value = 0;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
  }
  TreeNode(int val){
    value = val;
    left=nullptr;
    right=nullptr;
    parent=nullptr; 
  }
};

class BST
{
  // Add your own field and members here
  public:
  TreeNode *root;
  BST(){
    root = nullptr;
  }
  BST(int val){
    root = new TreeNode(val);
  }

  void insert(int val){
    TreeNode *z = new TreeNode(val);
    TreeNode *x,*y;
    y = NULL;
    x = root;
    while(x!=NULL){
        y=x;
        if(x->value>z->value) x=x->left;
        else x=x->right;
    }
    z->parent=y;
    if(y==NULL) root=z;
    else if(z->value<y->value) {
      y->left = z;
    }
    else {
      y->right = z;
    }
  }
  // Feel free to use the printBST function used earlier

  void printBST(const string& prefix, bool isLeft=false)
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


template <typename T> class List{
  public:
  T value; //value of node
  List *next;

  List(T node){
    value = node;
    next = nullptr;
  }
};

class Node
{
public:
  int value;
  List<Node> *adj; //adjacency list
  List<Node> *parents; //list of nodes from which it has been visited in dfs

  bool visited_once;
  bool visited_twice;
  bool visited; //for checking if present in cycle
  int degree;

  // insert other fields and methods as appropriate
};


class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  int numConnComp;
  int num_ones;
  int num_twos;
  int num_in_cycle;
  int *arr; //stores dfs
  int n; //stores elements in arr

  List<BST> *bst;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    arr = new int[10000000];
    n=0;
    BST *null_bst = new BST();
    bst = new List<BST>(*null_bst);
    numConnComp=0;
    num_ones=0;
    num_twos=0;
    num_in_cycle=0;
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
      nodes[i].adj = nullptr;
      nodes[i].parents = nullptr;
      nodes[i].visited_once = false;
      nodes[i].visited_twice = false;
      nodes[i].visited = false;
      nodes[i].degree=0;
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

      List<Node> *adj1 = nodes[n1].adj;
      List<Node> *adj2 = nodes[n2].adj;
      List<Node> *rec = adj2;

      while(rec!=nullptr){
        if(rec->value.value==(n1+1)) break; //check whether edge between n1 and n2 already exist
        rec = rec->next;
      }

      if(rec!=nullptr) continue; //if edge already exists, go to next iteration of while loop

      //now we have made sure that no edge exists between n1 and n2, so we add n1 to n2's adj list and vice versa
      //since the edge is undirected
      if(nodes[n1].adj == nullptr){
        nodes[n1].adj = new List<Node>(nodes[n2]);
      }
      else{
        while(adj1->next!=nullptr){
          adj1=adj1->next;
        }   
        adj1->next = new List<Node>(nodes[n2]);
      }
      if(nodes[n2].adj == nullptr){
        nodes[n2].adj = new List<Node>(nodes[n1]);
      }
      else{
        while(adj2->next!=nullptr){
          adj2=adj2->next;
        }   
        adj2->next = new List<Node>(nodes[n1]);
      }
      nodes[n1].degree++;
      nodes[n2].degree++;

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

  void DFS(Node *n, BST *bst); //dfs with backtracks when node is visited twice, and enter into BST
  int in_cycle();

  void modifiedDFS();
  void printResults();
};

#endif
