#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class arr {
  public:
    T* list;
    int max_size;
    int index;

    arr() {
        max_size = 2;
        list = new T[max_size];
        index = 0;
    }

    int len() {
      return index; 
    }

    void append(T data) {
      if (index == max_size) {
        // In first lecture, we read the growing array is better than increase size everytime
        T* newarr = new T[max_size * 2];
        for (int i = 0; i < max_size; i++) {
          newarr[i] = list[i];
        }
        max_size *= 2;

        // Saves space
        delete[] list;
        list = newarr;

        list[index] = data;
        index++;
    
      } else {
        list[index] = data;
        index++;
      }
    }

    T& operator[](int ind) {
      return list[ind]; 
    } 
};

// Node stores a node with value, adjancency and reverse adjancency list
// Adjanency list is a list of nodes coming from this node
// Reverse Adjanency list is a list of nodes going to this node
class Node {
 public:

  // Value of node
  int value;

  // adjacency list of Node
  arr<Node*> adjancency;
  arr<Node*> revadjancency;

  Node() {
    value = 0;
  }
  
  bool operator == (Node n2) {
    if (value == n2.value) {
      return true;
    }
  }

};

class Graph {

  int numNodes;
  Node *nodes;
  arr<Node*> source;
  arr<Node*> similar;
  arr<arr<Node*>> collapsed;
  arr<int> topcollapsed;
  arr<int> Edgescollapsed;
  int* visited;
  
 public:

  Graph(int n) {
      numNodes = n;
      nodes = new Node[numNodes];
      visited = new int[numNodes];

      for (int i = 0; i < numNodes; i++) {
        nodes[i].value = i+1;
      }    

      for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
      }        
    }
      
  ~Graph() {
    delete[] nodes;
  }

  // Adds edges to the graph
  void insertEdge(int n1, int n2) {
    nodes[n1-1].adjancency.append(&nodes[n2-1]);
    nodes[n2-1].revadjancency.append(&nodes[n1-1]);
  }

  // User defined similar nodes
  void insertSimilar(int n1, int n2) {
    similar.append(&nodes[n1-1]);
    similar.append(&nodes[n2-1]);
  }

  bool existsEdge(Node* n1, Node* n2);
  bool existsSource(Node* n);
  bool existsSimilar(Node* n1, Node* n2);
  void pushFinalSimilar(Node* n1, Node* n2);

  int recursiveDFS(Node* source, arr<Node*>* stack, int top);
  void rebuildGraph(Graph* graph);

  void sourceNodes();
  void similarNodes();
  void collapsedNodes(Graph* graph);
  void printResults(Graph* graph);
};

#endif
