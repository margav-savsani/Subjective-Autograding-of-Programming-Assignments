/*
The set class is used purely for ease of ordering
No absurdly powerful properties of set class have been used
And this class can easily be mimicked by the BST class designed by us earlier
Only insert, find and delete functions have been utilized.

So I hope its fine using this from the STL library, as its purpose is mainly for ordering property !!
*/


#include <set>
#include <fstream>


// the node for the vertices of graph
struct Node {
    int value;              // value stored in node
    int collapsed_value;    // the value corresponding to collapsed graph
    set<Node *> from;       // the from edges
    set<Node *> to;         // the to edges
    set<Node *> adj;        // adjacent nodes (for similar graph only)
    set<Node *> similar;    // all similar nodes for this node

    Node(int v) : value(v) {}
    ~Node() {}
};


// mimicking a tuple
struct Tuple {
    Node *a;
    Node *b;

    Tuple() : a(nullptr), b(nullptr) {}
    Tuple(Node *a, Node* b) : a(a), b(b) {}

    // operator required for the find operation of sets
    bool operator < (const Tuple &other) const {
        if(a < other.a) return true;
        if(other.a < a) return false;
        return b < other.b;
    }
};


class Graph {
    int numOfVertices;      // the number of vertices in graph
    Node **vertices;        // the array of vertices in graph
    Node **sim_vertices;    // the graph of similar vertices
    set<Node *> sources;    // the source nodes in the graph

    int num_collapsed;      // number of nodes in collapsed graph
    Node **collapsed;       // the collapsed graph

    ofstream out;           // the output file stream

    public:
    void read_and_sources();
    void find_similar();
    void collapse();
    int DFS(int i, bool visited[]);

    // default constructor and calling all necessary functions
    Graph() {
        out.open("outgraph.txt");
        read_and_sources();
        find_similar();
        collapse();
    }

    // destructor
    ~Graph() {
        delete[] vertices;
        delete[] sim_vertices;
        delete[] collapsed;
        out.close();
    }
};