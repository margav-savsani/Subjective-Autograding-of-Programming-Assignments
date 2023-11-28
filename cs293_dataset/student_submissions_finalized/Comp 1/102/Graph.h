#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
#include<map>
#include <vector>
#include <algorithm>
class Node
{
public:
  int value;    // value
  Node *left;   // Left Child of this Node (NULL, if None)
  Node *right;  // Right Child of this Node (NULL, if None)
  Node *parent; // The Parent Node, NULL in case of Root
  bool visited_Once = false;
  bool visited_Twice = false;

  // Node() : value(0), JourneyCode(0), left(nullptr), right(nullptr) {}
  Node() {
    left = nullptr;
    right = nullptr;
    parent=nullptr;
  };
  Node(int v)
  {
    value = v;
    left = nullptr;
    right = nullptr;
    parent=nullptr;
  }

  Node(int v, Node *leftChild, Node *rightChild, Node *parent)
  {
    value = v;
    left = leftChild;
    right = rightChild;
    this->parent = parent;
  }
};

class BST
{
  // Add your own field and members here
  // Feel free to add more private/public variables and/or functions
  // But do not modify the pre-existing function signatures

 


public:
  // ************************************************************
  // Methods for Part I
  Node *root;
  // Constructors!
  // BST() { root = nullptr; }
  BST(){root = nullptr;}
  // BST(Node *curr_root) { root = curr_root; }

  // Implement your own destructor
  

  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(int value)
  { 
    if(root==nullptr){
      root=new Node(value, nullptr, nullptr, (nullptr));
      return true;
    }
    // cout<<root<<" this \n";
    Node *currentNode=root;
    Node *currentParent = nullptr;
    // cout<<"HELP69\n";
    bool isL=false;
    while (currentNode != nullptr)
    { 
      // if ((currentNode)->value > value && (currentNode)->value != 0)
      if ((currentNode)->value > value )
      { 
        currentParent=currentNode;
        currentNode=currentNode->left;
        isL=true;
        // cout<<"Going left in insert \n";
        // return actualInsert(JourneyCode, value, ((*currentNode)->left), &(*currentNode));
      }
      else if ((currentNode)->value <= value )
      {
        // cout<<"Going right in insert \n";
        isL=false;
        // return actualInsert(JourneyCode, value, &((currentNode)->right), &(*currentNode));
        currentParent=currentNode;
        currentNode=currentNode->right;        
      }
    }
    if (currentNode == nullptr && currentParent!=nullptr)
    { 
      // cout<<"HELP420\n";
      currentNode = new Node(value, nullptr, nullptr, (currentParent));
      // if(currentParent->value==currentNode->value){
      //   return false;
      // }
      if(isL){
        currentParent->left=currentNode;
      }
      else{
        currentParent->right=currentNode;
      }
      // cout<<currentNode<<" "<<currentParent<<endl;
      return true;
    }
  }

  // Feel free to use the printBST function used earlier

  void printBST(const string &prefix, bool isLeft)
  { 
    // cout<<"HEHE\n";
    if (root != nullptr)
    { 
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->value << endl;
      Node *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }

  ~BST(){};
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  int components=0;
  map<int, vector<int> > path;
  int node_visited_once=0;
  int node_visited_twice=0;
  Graph(int nNodes, int nEdges, string gFileName)
  {
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

      if(find((path[n1]).begin(), (path[n1]).end(), n2)!=(path[n1]).end()){
        // !MEANS FOUND
        //if pair n1 and n2 exist no need to check for n2 & n1; they for sure exist...
        continue;
      }
      else{
        path.insert(pair<int, vector<int> >(n1,vector<int>()));
        (path[n1]).push_back(n2);
        path.insert(pair<int, vector<int> >(n2, vector<int>()));
        (path[n2]).push_back(n1);
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
      }

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

  void DFS(int v,BST*B);
  void modifiedDFS();
  void printResults();
};

#endif
