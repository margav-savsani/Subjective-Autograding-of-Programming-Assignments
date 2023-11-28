#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; prev=next = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class Node {
 public:
 int value;
 int childs=0;
 int parents=0;
 bool source=true;
 listOfObjects<int>*child;
 listOfObjects<int>*parent;
 listOfObjects<int>*group;
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges=0;
  fstream graphFile;
  listOfObjects<int> *dest;
  listOfObjects<int> *src;
  listOfObjects<int> *si;
  listOfObjects<int> *so;
  listOfObjects<int> *f1;
  listOfObjects<int> *f2;
  Node *nodes;
  ofstream graphfinal;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph() {
    graphfinal.open("outgraph.txt");
  cin >> numNodes;
  nodes=new Node[numNodes];
  for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
  }
  int n1,n2;
  while(cin>>n1>>n2){
    if(n1<0 && n2<0) break;
    listOfObjects<int> *copy=nodes[n1-1].child;
    listOfObjects<int> *copy1=nodes[n2-1].parent;
    listOfObjects<int> *dest1=dest;
    listOfObjects<int> *src1=src;
    if(dest1==NULL){
      dest1 = new listOfObjects<int> (n2);
      dest=dest1;
      src1 = new listOfObjects<int> (n1);
      src=src1;
    }
    else{
      while(dest1->next!=NULL){
      dest1=dest1->next;
    }
    dest1->next=new listOfObjects<int> (n2);
    while(src1->next!=NULL){
      src1=src1->next;
    }
    src1->next=new listOfObjects<int> (n1);
    }
    if(copy==NULL){ 
      copy = new listOfObjects<int> (n2);
      nodes[n1-1].child=copy;
      nodes[n1-1].childs++;
    }
    else{
    while(copy->next!=NULL){
      copy=copy->next;
    }
    copy->next=new listOfObjects<int> (n2);
    nodes[n1-1].childs++;
    }
    if(copy1==NULL){ 
      copy1 = new listOfObjects<int> (n1);
      nodes[n2-1].parent=copy1;
      nodes[n2-1].parents++;
    }
    else{
    while(copy1->next!=NULL){
      copy1=copy1->next;
    }
    copy1->next=new listOfObjects<int> (n1);
    nodes[n2-1].parents++;
    }
  }
  listOfObjects<int> *d=dest;
  while(d!=NULL){ 
    nodes[d->object-1].source=false;
    d=d->next;
    }


  

      // Create an undirected edge from n1 to n2 and store in appropriate
      // child list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile


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

  bool similarnodes(int a,int b);
  void printResults();
  void intersection(int i,int j);
  void newedge(int w,int m);
  bool check(int x,int y);

};

#endif
