#include <iostream>
#include <fstream>
using namespace std;

class Node {
public:
    int value;
    int out_neighbours; // The out degree of this node
    int in_neighbours; // The in degree of this node
    int * out_adjacent; // Out adjacency list
    int *in_adjacent; // In adjacency list
    int equivalence_class_no; // Which equivalence class it belongs to
    Node(){
        value = 0;
        out_neighbours = 0;
        in_neighbours = 0;
        out_adjacent = nullptr;
        in_adjacent = nullptr;
        equivalence_class_no = -1;
    }
};

struct Edge {
    // An edge from node1 to node2
    int node1;
    int node2;
    Edge(int n1, int n2) : node1(n1), node2(n2) {}
};

struct EdgeList {
    // Linked List for edges
    EdgeList* next;
    EdgeList* prev;
    Edge* object;
    EdgeList(){
        next = nullptr;
        prev = nullptr;
        object = nullptr;
    }
    EdgeList(EdgeList* next, Edge*obj) : next(next), object(obj), prev(nullptr) {}
};


class DAG {
    public:
    int numNodes;
    int numEdges;
    EdgeList* edges; // linked list for edges in the graph
    Node* nodes; // array of nodes in the graph
    bool** similar; // Similarity matrix, similar to an adjacency matrix
    int no_of_equivalence_classes; // No. of equivalence classes in the graph
    int* class_representative; // The maximum value node in an equivalence class
    int** equivalence_class_list; // The list of equivalence classes in the graph
    int* class_length; // Array containing lengths of equivalence classes
    DAG(int n); // Constructor
    void create_adjacency();
    void printSource();
    void similarPairs();
    bool isSimilar(int a, int b);
    bool isSource(int n){return nodes[n-1].in_neighbours==0;}
    void equivalance_class();
    void compute_closure_matrix();
};
