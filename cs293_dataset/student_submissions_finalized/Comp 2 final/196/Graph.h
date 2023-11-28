//Graph header File
#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

//Singly Linked List Object of Typename T
template <typename T> class listOfObjects {
 public:
  T object; //object
  listOfObjects<T> *next; //pointer to next element
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = nullptr;}
  // Destructor
  ~listOfObjects() {;}
};

//Ordered Pair Struct
struct OrderedPair{
  int value1; //first argument
  int value2; //second argument
  //Constructor 1
  OrderedPair(){
    value1=-1;
    value2=-1;
  }
  //Constructor 2
  OrderedPair(int val1, int val2){
    value1=val1;
    value2=val2;
  }
};

//Graph Node Class
class Node {
 public:
  int value;  //Value of the node
  listOfObjects<Node*> *inadjnodes; //Inadjacency List of neighbours
  listOfObjects<Node*> *outadjnodes;  //Outadjacency List of neighbours
  listOfObjects<Node*> *similar;  //List of Nodes similar to the given node
  //Value of the node that this node has collapsed to
  //By default it is same as the node's value
  int collapsedTo;
  //Is the node a source or not
  bool isSource;
  //Constructor 1
  Node(){
    value=0;
    inadjnodes=nullptr;
    outadjnodes=nullptr;
    similar=nullptr;
    isSource=false;
    collapsedTo=0;
  }
  //Constructor 2
  Node(int val){
    value=val;
    inadjnodes=nullptr;
    outadjnodes=nullptr;
    similar=nullptr;
    isSource=false;
    collapsedTo=val;
  }

  //Adds the neighbour to inadjacency list of the current node
  void addinNeighbour(Node* n){
    //Adding the first in-neighbour
    if(inadjnodes==nullptr){
      inadjnodes= new listOfObjects<Node*>(n);
      return; 
    }
    //Adding subsequent neighbours
    listOfObjects<Node*> *curr;
    curr=inadjnodes;
    while (curr->next!=nullptr)
    {
      curr=curr->next;
    }
    curr->next= new listOfObjects<Node*>(n);
    return;
  }

  //Adds the neighbour to outadjacency list of the current node
  void addoutNeighbour(Node* n){
    //Adding first out-neighbour 
    if(outadjnodes==nullptr){
      outadjnodes= new listOfObjects<Node*>(n);
      return; 
    }
    //Adding subsequent out-neighbours
    listOfObjects<Node*> *curr;
    curr=outadjnodes;
    while (curr->next!=nullptr)
    {
      curr=curr->next;
    }
    curr->next= new listOfObjects<Node*>(n);
    return;
  }

  //Checks whether n is an in-neighbour of current node or not
  //Returns true if it is and false otherwise
  bool isinNeighbour(Node n){
    //If there are no in-neighbours
    if (inadjnodes==nullptr) return false;
    listOfObjects<Node*> *curr;
    curr=inadjnodes;
    while(curr!=nullptr){
      //Returning true if it is found
      if(curr->object->value==n.value){
        return true;
      }
      curr=curr->next;
    }
    //Otherwise returning false
    return false;
  }
  //Checks whether n is an out-neighbour of current node or not
  //Returns true if it is and false otherwise
  bool isoutNeighbour(Node n){
    //If there are no out-neighbours
    if (outadjnodes==nullptr) return false;
    listOfObjects<Node*> *curr;
    curr=outadjnodes;
    while(curr!=nullptr){
      //Returning true if it is found
      if(curr->object->value==n.value){
        return true;
      }
      curr=curr->next;
    }
    //Otherwise returning false
    return false;
  }

  //Adds the node to the similar list of current node
  void addsimilar(Node* n){
    //Adding the first simiklar node
    if(similar==nullptr){
      similar= new listOfObjects<Node*>(n);
      return; 
    }
    //Adding subsequent similar nodes
    listOfObjects<Node*> *curr;
    curr=similar;
    while (curr->next!=nullptr)
    {
      curr=curr->next;
    }
    curr->next= new listOfObjects<Node*>(n);
    return;
  }

  //Checks whether the node is in similar list of current node or not
  //Returns true if it is and false otherwise
  bool isSimilar(Node n){
    //If there are no similar nodes
    if (similar==nullptr) return false;
    listOfObjects<Node*> *curr;
    curr=similar;
    while(curr!=nullptr){
      //Returning true if it is found
      if(curr->object->value==n.value){
        return true;
      }
      curr=curr->next;
    }
    //Otherwise returning false
    return false;
  }
};

//Graph Object
class Graph {
 public:
  int numNodes; //Number of Nodes
  Node *nodes;  //Array of Nodes of Graph
  listOfObjects<OrderedPair*> *listofSimilars;  //List of pairs of all similar node values
  listOfObjects<int> *collapsedNodes; //List of values of all nodes left after collapsing
  int nUnCollapsedNodes;  //Number of all uncollapsed nodes
  fstream graphFile;  //Graphfile to stream output in outgraph.txt
  //Constructor
  Graph(int nNodes){
    numNodes=nNodes;
    nodes = new Node[numNodes];
    listofSimilars=nullptr;
    collapsedNodes=nullptr;
    nUnCollapsedNodes=0;
    graphFile.open("outgraph.txt",ios::out);
    //Assigning values to each node
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      nodes[i].collapsedTo=i+1;
    }
  }

  //Destructor
  ~Graph(){
    delete[] nodes;
  }
  //Adds a directed edge from node valued n1 to node valued n2
  void addDirectedEdge(int n1, int n2);
  //Adds (n1,n2) pair to listofSimilars and also the node valued n2 in the similar list of node valued n1
  void addSimilar(int n1, int n2);
  //Constructs all the similar nodes possible
  void constructSimilar();
  //Checks and updates if n1 is similar to n2
  //Returns true if it is and false otherwise
  bool checkSimilar(int n1, int n2);
  //Prints all the Source Nodes
  void printSourceNodes();
  //Prints all the Similar Node Pairs
  void printSimilarNodes();
  //Collapses the Graph and prints the collapsed graphs numNodes, NodeList and Edges
  void CollapseGraph();
  //Finds the node value that the node valued n will finally collapse to
  int findFinalCollapse(int n);
};

#endif