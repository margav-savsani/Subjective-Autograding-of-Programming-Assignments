#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#endif

template<typename T> class list {
 public:
  T object;
  list<T> *next;
  list<T> *prev;
  
  // Constructor
  list(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~list() {;}
};

class Node {
    public:
        int val;
        bool is_source=true;

        Node(int x){val = x;}
        Node(){}
};

class Graph {
    public:
    int numOfNodes;
    int **adj_mat,**sim_mat,**new_sim;
    Node *nodes;

        Graph(int num, int **adj_mat, int **sim_mat,int **new_sim, bool *arr);
        
        // add a directed adge b/w two edges
        void add_edge(int a, int b); 

        // function to print source nodes
        void source();

        // function to print similar node pairs
        void similar();

        // function of collapse the equivalence classes
        void collapse();

        // graph
        bool DFS(int i,int *max, int *arr);
};

