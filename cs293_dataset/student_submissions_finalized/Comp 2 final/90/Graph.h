#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <cassert>
using namespace std;


// Creating a list to store literally
// any set of nodes we see later in the graph class
// Implemented using concept of dynamic
// programming using growth arrays
template<typename T> 
class list{

    T* link;
    int cap, strength;
public:
    // Initialising an initial capacity of 1 element
    // and dynamically allocating storage
    list(){
      link = new T[1];
      cap = 1;
      strength = 0;
    } 

    // Adds an element at the end of the list
    void push(T value){
      if(strength == cap){
         //Then grow the link
          T* tmp = new T[2*cap];

          // copying old elements to the new link
          for(int i = 0; i < cap; i++) {
            tmp[i] = link[i];
          }
          // deleting previous link
          delete[] link;
          cap *= 2;
          link = tmp;
      }
      // Inserting the value
      link[strength++] = value;
    }

    // Returns the element at the given index
    T get(int index){
      // Ensuring index within bound
      assert(index < strength);
      return link[index];        
    }

    //Returns size of link
    int size(){ 
      return strength;
    }

    // For debugging purposes
    void print(){
      for(int i=0; i<size();i++){
        cout << get(i) << " ";
      }
      cout << endl;
    }
};

// Building blocks of a graph
class Node {
public:
  int value;  //value stored at that node
  list<Node*> adjacencyto; // The list of nodes incident from this node
  list<Node*> adjacencyfrom; // The list of nodes incident to this node
  list<int> similarnodes; // List of nodes similar to this node
  list<int> newsimilarnodes; // New list of nodes, an extension to similar nodes, we shall see it being used later on
  bool visited; // marks if the node is visited, used while doing DFS
  bool sourceNode; // marks true for a source node

  Node(){
    // Constructor
    visited = false;
    sourceNode = false;
  }
};


// The Graph Class containing nodes
class Graph {
  int numNodes; // Number of nodes
  Node *nodes; // Array of Nodes in the graph
  ofstream myfile;  // Output file stream
  int* newValues; // Array of new values corresponding to each node in graph, used during construction of collapsed graph
  bool* newlyvisit; // Array of boolean new values, to be used to indetify elements of a component
  int* leader; // Array of values which it is collapsed to(the largest value in a collapsed component)

 public: 
  Graph(int nNodes) {
    newlyvisit = new bool[nNodes]; 
    reset_newly_visit(); //sets newlyvisit to all false
    leader = new int[nNodes]; 
    myfile.open ("outgraph.txt"); //opening output file
    numNodes = nNodes;
    nodes = new Node[numNodes];
    newValues = new int[numNodes];
    for(int i=0; i< numNodes; i++) newValues[i] = i+1;
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    int n1, n2;
    // Taking input of directed edges
    while(true){
      cin >> n1 >> n2;
      if(n1 == -1 && n2 == -1) break; //when user wants to end giving input of directed edges
      //Here n1 is incident to n2
      nodes[n2-1].adjacencyfrom.push(&nodes[n1-1]);
      nodes[n1-1].adjacencyto.push(&nodes[n2-1]);
    }

    // Taking input of similar nodes among the source nodes
    while(true){
      cin >> n1 >> n2;
      if(n1 == -1 && n2 == -1) break;//when user wants to end giving input of similar nodes
      // Here n1 is similar to n2, according to condition 1
      // Caution: the vice versa may not be true
      nodes[n1-1].similarnodes.push(n2);
    }
  }

  // Resets newlyvisit boolean array to all false
  // To be used for next round of DFS on another component
  // divided by similarity
  void reset_newly_visit(){
    for(int i=0; i<numNodes; i++){
      newlyvisit[i] = false;
    }
  }
  
  //Destructor
  ~Graph() {
    delete[] nodes;
    delete[] newValues;
    delete[] newlyvisit;
    delete[] leader;
    myfile.close();
  }

  // Does DFS on a new graph
  // This new graph is an undirected graph with 
  // Edges defined by the similar relation
  // i.e., there is an edge between n1 and n2
  // iff n1 is similar to n2 in the original graph
  // the user had input
  int DFS(int n);

  // Our newly created graph may not be connected
  // Hence we shall do DFS to cover all points and 
  // count all connected components and 
  //collapses them to the maximum value in the component
  //and prints the vertices of this collapsed graph
  void doDFS();

  //Prints the source Nodes
  //Done in O(n), linear time, where n is numNodes
  void printSourceNodes();

  //Prints similar nodes and number of components
  //for the new graph ideated as earlier and 
  //collapses them to the maximum value in the component
  //and prints the vertices of this collapsed graph
  void printSimilarNodes();

  //Prints the edges of the collapsed graph
  void printCollapsedGraph();

  
  //Recursively checks if two nodes are similar according to point 2
  //We do recursion because we may miss out some similar 
  //nodes if we dont do recursion, and instead check similarity
  //via point 2 directly, then the parents may not be similar by then
  //but may become later, which can cause an issue
  bool check_similarity_recursively(Node* n1, Node* n2){
    for(int i=0; i<n1->similarnodes.size();i++){
      if(n2->value == n1->similarnodes.get(i)){
        //If they are already similar then just return true, 
        //no need of recursion.
        //This is a very good applciation of memoization
        return true;
      }
    }
    if(n1->adjacencyfrom.size() == 0) return false;
    for(int i=0; i<n1->adjacencyfrom.size();i++){
      bool exists = false; //Checking whether a corresponding m2, predecessor of n2 
                            //exists which is similar to m1, predecessor of n1
      for(int j=0; j<n2->adjacencyfrom.size();j++){
        if(check_similarity_recursively(n1->adjacencyfrom.get(i),n2->adjacencyfrom.get(j))){
          exists = true;
          break;
        }
      } 
      if(!exists) return false; //return false if no such exists, even for one value of m1
    }
    return true;
  }

};

#endif
