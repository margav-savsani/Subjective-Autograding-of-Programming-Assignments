#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>
using namespace std;
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = nullptr;}
};
class Node {
 public:
  Node(){;};
  int value;
  listOfObjects<Node*> *to;
  listOfObjects<Node*> *from;
};
class Graph {
  int numNodes;
  Node *nodes;
  bool **similaritymatrix;
  bool **checked;
  public:
  // Add appropriate fields as necessary for your implementation
  Graph(int nNodes) {
    nodes = new Node[nNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    numNodes=nNodes;
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
    // Add appropriate code as necessary for your implementation
    similaritymatrix=new bool*[nNodes];
    checked=new bool*[nNodes];
    for(int i=0;i<nNodes;i++){
      similaritymatrix[i]=new bool[nNodes];
      checked[i]=new bool[nNodes];
      for(int j=0;j<nNodes;j++){
        similaritymatrix[i][j]=false;
        checked[i][j]=false;
      }
    }
  }
  ~Graph() {
    delete[] nodes;
    }
  void printResults();
  void addedge(int a ,int b );
  void addsimilarpair(int a , int b);
  void similarity2();
  void similarity13();
  bool check(int i, int j,listOfObjects<Node*> *a,listOfObjects<Node*> *b);
};