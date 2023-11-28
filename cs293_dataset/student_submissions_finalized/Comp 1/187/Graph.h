#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif
// Self implementation of
// the Vector Class in C++
template <typename T> class vectorClass {
 
    // arr is the integer pointer
    // which stores the address of our vector
    T* arr;
    // capacity is the total storage
    // capacity of the vector
    int capacity;
    // current is the number of elements
    // currently present in the vector
    int current;
 
public:
    // Default constructor to initialise
    // an initial capacity of 1 element and
    // allocating storage using dynamic allocation
    vectorClass()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }
       //destructor to deallocate storage allocated by dynamic allocation
       //to prevent memory leak
    //   ~ vectorClass()
    // {
    //       delete [] arr;
    // }
 
    // Function to add an element at the last
    void push_back(T data)
    {
 
        // if the number of elements is equal to the
        // capacity, that means we don't have space to
        // accommodate more elements. We need to double the
        // capacity
        if (current == capacity) {
            T* temp = new T[2 * capacity];
 
            // copying old array elements to new array
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
 
            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
 
        // Inserting data
        arr[current] = data;
        current++;
    }
    void remove(int index){
        for(int i = index;i<current;i++){
            arr[i] = arr[i+1];
        }
        current--;
    }
    // function to add element at any index
    void push(T data, int index)
    {
 
        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
            push(data);
        else
            arr[index] = data;
    }
 
    // function to extract element at any index
    T get(int index)
    {
 
        // if index is within the range
        if (index < current)
            return arr[index];
    }
 
    // function to delete last element
    void pop() { current--; }
 
    // function to get size of the vector
    int size() { return current; }
 
    // function to get capacity of the vector
    int getcapacity() { return capacity; }
 
    // function to print array elements
    void print()
    {
        for (int i = 0; i < current; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

class BSTNode{// Each Node of Tree.
  public:
  int value;// value stored in Node.
  BSTNode *left;// left child pointer of Node.
  BSTNode *right;// right child pointer of Node.
  BSTNode *parent;//  parent pointer of Node.
  BSTNode(){// Constructor of BSTNode.
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  BSTNode(int a){// Another constructor of BSTNode.
    value = a;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};
class BST {// Binary Search Tree class.
  public:
  BSTNode *root;// root of Tree.
  BST(){
    root = nullptr;// root is null pointer.
  }
  BST(BSTNode *root){
    this->root = root;
  }
  bool insert(int value){ // inserts the value in to BST by checking with node and sending it to left or right corresponding to its value.
    if(root == nullptr){
        root = new BSTNode(value);
        return true;
    }
    BSTNode *curr = root;
    BSTNode *y = new BSTNode(value);
    while(true){            
        if(value > curr->value){
            if(curr->right != nullptr){
                curr = curr->right;
            }
            else{
                curr->right = y;
                break;    
            }
        }
        else{
            if(curr->left!=nullptr){
                curr = curr->left;
            }
            else{
                curr->left = y;
                break;
            }
        }
    }
    return true;
}

void printBST(const string& prefix, bool isLeft=false)
{// This function prints the Binary Search Tree with given values stored in BSTNode.
    if(root != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );
        cout << root->value << endl;
        BSTNode *curr = root;
        root = root->left;
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
};

class Node {// Node of Graph
 public:
  int value;// Value stored in Graph
  vectorClass<int> list;
  vectorClass<int> adj;// adjacnecy list
  Node *prev;
  bool incycle;
//insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  int *count;
  int connected;
  bool *visit;
  vectorClass<BST *> trees;
//  Add appropriate fields as necessary for your implementation
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    count = new int[nNodes];
    visit = new bool[nNodes];
    connected = 0;
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
    for(int i=0;i<numNodes;i++){// assigns visit array to false.
        visit[i] = false;
    }
    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
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
      if(!visited(n1, n2)){// checks if not visited then proceeds further.
        nodes[n1].list.push_back(n2);// appends value n2 to adjlist of n1.
        nodes[n1].adj.push_back(n2);// appends value n1 to adjlist of n2.
        nodes[n2].list.push_back(n1);// appends value n2 to adjlist of n1.
        nodes[n2].adj.push_back(n1);// appends value n1 to adjlist of n2.
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
    }
}
  }
  bool visited(int a, int b){// This function gives us whether edge betwene two nodes or not by adjacency list
  Node s = nodes[a];
  for(int i=0;i<s.adj.size();i++){
    if(s.adj.get(i) == b){
        return true;
    }
  }  
  return false;
}
    // Add appropriate code as necessary for your implementation 
 ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }
  // Add appropriate method declarations as necessary for your implementation
  void DFS(int a, BST* tree);// Does DFS upon given node value.
  bool Cycle(int a, int val);// checks if node is present cycle or not.
  void modifiedDFS();// Does modified DFS upon given graph.
  void printResults();// Prints the results corresponding to graph.
};

#endif
