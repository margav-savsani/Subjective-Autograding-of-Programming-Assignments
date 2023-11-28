#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


// Node for doubly linked list
template <typename T>
struct DLLNode{
  T value;
  DLLNode *prev;
  DLLNode *next; 
  DLLNode(T v): value(v){
    // value = v;
    prev = nullptr;
    next = nullptr;
  }
};

//doubly linked list implementation, trivial
template <typename T>
class DLL{
  public:
  int len;
  DLLNode<T> *head;
  DLLNode<T> *tail;
  DLLNode<T> *sortedhead;
  
    DLL(){
      len=0;
      head = nullptr;
      tail = nullptr;
    }

    //inserting a new element
    void insert(T x){
      if (head == nullptr){
        head = new DLLNode<T>(x);
        tail = head;
        len++;
        return;
      }
      DLLNode<T> *tailtemp=tail;
      tail = new DLLNode<T>(x);
      tailtemp->next = tail;
      tail->prev = tailtemp;
      len++;
    }

    //printing size of list
    int size(){
      return len;
    }

    //deleting element from the list
    void pop(){
      if (tail == nullptr){
        return;
      }
      if (tail->prev != nullptr){
        DLLNode<T> *d=tail;
        tail = tail->prev;
        tail->next=nullptr;
      }
      else{
        tail=nullptr;
        head=nullptr;
      }
    }

    int top(){
      if (tail == nullptr){
        return -1;
      }
      return tail->value;
    }

    // checking if an element exists in the linked list or not
    bool isin(T x){
      DLLNode<T> *d = head;
      while (d != nullptr){
        if (d->value == x){
          return true;
        }
        d = d->next;
      }
      return false;
    }

    // to get the pointer to a particular node of list
    DLLNode<T> * getptr(T x){
      DLLNode<T> *d = tail;
      while (d != nullptr){
        if (d->value == x){
          return d;
        }
        d = d->prev;
      }
      return nullptr;
    }

    //sorting the list by using insertion sort
    void insertionSort()
    {
        sortedhead = NULL;
        DLLNode<T> *current = head;
        while (current != NULL) {
            DLLNode<T> *next = current->next;
            sortedInsert(current);
            current = next;
        }
        head = sortedhead;
    }

    //helper function for above insertion sort
    void sortedInsert(DLLNode<T> *newnode)
    {
        if (sortedhead == NULL || !(sortedhead->value < newnode->value)) {
            newnode->next = sortedhead;
            sortedhead = newnode;
        }
        else {
            DLLNode<T>* current = sortedhead;
            while (current->next != NULL
                   && current->next->value < newnode->value) {
                current = current->next;
            }
            newnode->next = current->next;
            current->next = newnode;
        }
    }

};

// node class for directed graph
class Node {
 public:
  int value;  // value on node
  int outgoingSize;  // size of outgoing edge node list
  int incomingSize;  // size of incoming edge node list
  DLL<int> incoming;  // list of incoming edge nodes
  DLL<int> outgoing;  // list of outgoing edge nodes
  DLL<int> similar;   // list of elements 'e' such that (value similar to e) using the similarity relation given 
  Node(){
    value = -1;
  }
  Node(int x){
    value = x;
    outgoingSize=0;
    incomingSize=0;
  }

  // adding an edge to the node based on bool source which says whether it is incoming or outgoing
  void addEdge(int x, bool source){
    if (source){
      if (outgoing.isin(x)){
        return;
      }
      outgoing.insert(x);
      outgoingSize++;
    }
    else{
      if (incoming.isin(x)){
        return;
      }
      incoming.insert(x);
      incomingSize++;
    }
  }

  // equal operator defined on this class objects
  bool operator==(Node n){
    if (value == n.value){
      return true;
    }
    return false;
  }
};

//struct for a pair of integers which may be the similar vertices or may storing the edges
struct Pair{
  int n1;
  int n2;
  Pair(){
    n1 = -1;
    n2 = -1;
  }
  Pair(int n1, int n2){
    this->n1 = n1;
    this->n2 = n2;
  }

  // equal operator for these type of objects
  bool operator==(Pair s){
    if (n1 == s.n1 && n2 == s.n2){
      return true;
    }
    return false;
  }

  // less than operator needed for sorting these objects
  bool operator<(Pair s){
    if (n1 < s.n1){
      return true;
    }
    else if (n1 == s.n1 && n2 < s.n2){
      return true;
    }
    else{
      return false;
    }
  }
};


// Class for directed Graph
class Graph {
  int numNodes;
  int numEdges;
  ofstream out; // file to write
  int numConnComp;  // number of connected components based on the similarity relation

  Node *nodes;  // list of all nodes
  DLL<Pair> similarList; // list of all similar pair of vertices
  int *connectedCompNumber; // lists out the index of connected component the particular node is present into  
  bool *sourceNode; // true if the indexed node is source node
  short int *similar; // integer matrix for storing whether two nodes are settled similar or not yet settled or settled as not similar
  // Add appropriate fields as necessary for your implementation
  
 public:
  // constructor when no files are to be used, instead manual adding of edges
  Graph(int nNodes){
    numNodes = nNodes;
    numEdges = 0;
    numConnComp = 0;
    sourceNode = new bool[numNodes];
    connectedCompNumber = new int[numNodes];
    nodes = new Node[numNodes];
    similar = new short int[numNodes*numNodes];

    for (int i = 0; i < numNodes; i++) {
      sourceNode[i] = false;
      nodes[i].value = i+1;
      connectedCompNumber[i] = 0;
      for (int j=0; j<numNodes; j++){
        similar[i*numNodes+j] = 0;
      }
    }
  }

  //constructor when file input considered
  Graph() {
    numNodes = 0;
    numEdges = 0;
    numConnComp = 0;

    cin >> numNodes;

    sourceNode = new bool[numNodes];
    connectedCompNumber = new int[numNodes];
    nodes = new Node[numNodes];
    similar = new short int[numNodes*numNodes];

    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      sourceNode[i] = false;
      nodes[i].value = i+1;
      connectedCompNumber[i] = 0;
      for (int j=0; j<numNodes; j++){
        similar[i*numNodes+j] = 0;
      }
    }

    //following is the addition of edges to the graph
    int n1, n2;
    
    while (true) {
      cin >> n1;
      cin >> n2;
      if (n1 == -1 || n2 == -1){
        break;
      }
      addEdgeToGraph(n1,n2);
      numEdges++;
    }
  }
      
  ~Graph() {
    delete[] nodes;
    out.close();
  }

  // updating the value of connected components
  void updateConn(int *x,int y){
    for (int i=0; i<numNodes; i++){
      *(connectedCompNumber+i) = *(x+i);
    }
    numConnComp = y;
  }

  // updating the value of nodes
  void updateNode(int x, int y){
    nodes[x-1].value = y;
  }

  // adding an edge to the graph
  void addEdgeToGraph(int s, int e){
    nodes[s-1].addEdge(nodes[e-1].value,true);
    nodes[e-1].addEdge(nodes[s-1].value,false);
    return;
  }

  void printGraph();  // printing the graph
  void printSources();  // printing the source nodes
  void printCollapsed();  // printing the collapsed graph
  void printSimilar();  // printing the similar pairs
  bool isSimilar(int m, int n);   // to check whether the two nodes are similar or not
};


// node class for undirected graph
class NodeUndirected {
 public:
  int value;
  DLL<int> adjacent;  // adjacency list
  NodeUndirected(){
    value = -1;
  }
  NodeUndirected(int x){
    value = x;
  }

  // adding an edge to the graph
  bool addEdge(int x){
    if (adjacent.isin(x)){
      return false;
    }
    adjacent.insert(x);
    return true;
  }
};

// graph class for undirected graphs
class GraphUndirected {
  int numNodes; 
  int *visited; // whether the node visited or not used for DFS
  NodeUndirected *nodes;
  
 public:
  
  int *connectedCompNumber;   // list of index of the component number in which the element belongs to
  int compNum;  // total number of components present
  int numEdges;

  // constructor with given number of nodes and no file inputs
  GraphUndirected(int nNodes) {
    numNodes = nNodes;
    compNum = 0;
    numEdges = 0;
    visited = new int[numNodes];
    connectedCompNumber = new int[numNodes];
    nodes = new NodeUndirected[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      visited[i] = 0;
      connectedCompNumber[i] = 0;
      nodes[i].value = i+1;
    }
  }
      
  ~GraphUndirected() {
    delete[] nodes;
    delete[] visited;
    delete[] connectedCompNumber;
  }

  // adding an edge to the graph
  void addEdgeToGraph(int s, int e){
    if (nodes[s-1].addEdge(nodes[e-1].value)){
      nodes[e-1].addEdge(nodes[s-1].value);
      numEdges++;
    }
    return;
  }
  void DoDFS(int x); //doing DFS on  particular node
  void findComponents();  // finding/labelling all the connected components
};

#endif
