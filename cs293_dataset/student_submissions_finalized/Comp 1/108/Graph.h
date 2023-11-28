#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

constexpr int MAX_EDGES_FROM_NODE = 1e5;

// Same as in lab 4
struct TreeNode{
    int JourneyCode;	// Journey code
    int price;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    
    TreeNode(int jrnyCode, int jrnyPrice) : 
        price(jrnyPrice), 
        JourneyCode(jrnyCode), 
        left(nullptr), 
        right(nullptr), 
        parent(nullptr) 
        {}
};

// Same as the one in lab 4
class BST {
    // Add your own field and members here
    TreeNode *root;

    // Feel free to use the printBST function used earlier
public:
    bool insert(int JourneyCode, int price);
    void printBST(const string& prefix, bool isLeft=false);
};

class Node {
public:
    int value;
    int num_edges {0};  // Number of edges from this node
    int visited {0};  // Number of times this is visited
    int edges[MAX_EDGES_FROM_NODE];  // Array of nodes with edges from this node
    bool cycle;  // Is this node in a cycle

    // insert other fields and methods as appropriate
};

class Graph {
    int numNodes;
    int numEdges;
    int cc;
    int once, twice;
    BST* bsts;
    fstream graphFile;
    Node* nodes;

    // Add appropriate fields as necessary for your implementation
    void modifiedDFS_on_cc(int cur, int prev, bool** edges_used);
    
public:
    Graph(int nNodes, int nEdges, string gFileName) {
        numNodes = nNodes;
        numEdges = nEdges;
        cc = 0;
        once = 0;
        twice = 0;
        bsts = new BST[numNodes];
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

        // srand(time(0));
        int n1, n2;
        int countEdges = 0;
        
        while (countEdges < numEdges) {
            do {
                n1 = rand() % numNodes;
                n2 = rand() % numNodes;
            } while (n1 == n2);

            // Create an undirected edge from n1 to n2 and store in appropriate
            // adjacency list(s). If an undirected edge from n1 to n2 (or
            // equivalently from n2 to n1) already exists, you shouldn't add
            // an edge. Only if such an undirected edge didn't exist earlier,
            // should you add the edge and increment countEdges; otherwise,
            // do not increment countEdges;
            // Every time an edge is created, we also add that information to
            // graphFile
            bool present { false };
            for (auto &e: nodes[n1].edges) {
                if (e == n2) present = true;
            }
            if (present) continue;

            nodes[n1].edges[nodes[n1].num_edges++] = n2;
            nodes[n2].edges[nodes[n2].num_edges++] = n1;

            graphFile << n1+1 << " " << n2+1 << endl;
            countEdges++;
            if (countEdges == (numNodes*(numNodes-1))/2) return;
        }

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
    void modifiedDFS();
    void printResults();
};

#endif