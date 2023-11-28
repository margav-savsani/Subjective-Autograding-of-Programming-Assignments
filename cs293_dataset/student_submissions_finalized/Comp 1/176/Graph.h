#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


// linked list implementation
template <typename T> class listOfObjects {
    public:
    T object;
    listOfObjects<T> *next;
    listOfObjects<T> *prev;
    
    // Constructor
    listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
    
    // Destructor
    ~listOfObjects() {;}
};

// finds the element in the given list
template<typename T>
bool find(T x, listOfObjects<T *> *list){
    while(list != nullptr){
        if(*(list->object) == x)
            return true;
        list = list->next;
    }
    return false;
}


// nodes for the binary search tree
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    
    TreeNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNode(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNode(int v, TreeNode* l, TreeNode* r, TreeNode* p) : value(v), left(l), right(r), parent(p) {}
};


class BST {
    TreeNode *root;

    public:
    BST() {root = NULL;}
    BST(TreeNode *root) {this->root = root;}

    void insert(int v) {
        TreeNode *new_node = new TreeNode(v);
        if(root == NULL){
            root = new_node;
            return;
        }

        TreeNode* parent = nullptr;
        TreeNode* null_node = root;
        while(null_node != nullptr){
            parent = null_node;
            if(v < null_node->value)
                null_node = null_node->left;
            else
                null_node = null_node->right;
        }
        if(v < parent->value)
            parent->left = new_node;
        else
            parent->right = new_node;

        new_node->parent = parent;
    }

    void printBST(const string& prefix, bool isLeft=false){
        if( root != nullptr )
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__" );

            // print the value of the node
            cout << root->value << endl;
            TreeNode *curr = root;
            root = root->left;
            // enter the next tree level - left and right branch
            printBST( prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;
            printBST( prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }
};


// node for the graph
class Node {
    public:
    int value;
    int visited;
    int parent;
    int parent2;
    
    Node() : value(0), visited(0), parent(-1), parent2(-1) {}
    
    bool operator==(Node const another){
        return value == another.value;
    }
};


// node for the stack used to mimick recursion stack
struct stackNode {
    Node* node;
    listOfObjects<Node *> *progress;

    stackNode() : node(nullptr), progress(nullptr) {}
    stackNode(Node* n, listOfObjects<Node *> *p) : node(n), progress(p) {}
};




class Graph {
    int numNodes;
    int numEdges;
    fstream graphFile;

    Node *nodes;
    listOfObjects<Node *> **adjacency;
    
    int connected;      // no. of connected components
    int once_visited;   // nodes visited once
    int twice_visited;  // nodes visited twice
    int nodes_cycle;    // nodes part of cycle

    listOfObjects<BST *> *trees;    // binary search trees

    public:
    Graph(int nNodes, int nEdges, string gFileName) {
        numNodes = nNodes;
        numEdges = nEdges;
        connected = 0;
        once_visited = numNodes;
        twice_visited = 0;
        trees = nullptr;

        graphFile.open(gFileName, ios::out);
        if (!graphFile.is_open()) {
            cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
            exit(-1);
        }

        graphFile << numNodes << endl;
        graphFile << numEdges << endl;

        nodes = new Node[numNodes];
        adjacency = new listOfObjects<Node *>*[numNodes];
        if (nodes == nullptr || adjacency == nullptr) {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
        }

        for (int i = 0; i < numNodes; i++) {
            nodes[i].value = i+1;
        }

        srand(time(0));
        int n1, n2;
        int countEdges = 0;
        
        while (countEdges < numEdges) {
            do {
                n1 = rand() % numNodes;
                n2 = rand() % numNodes;
            } while (n1 == n2);

            // edge already present
            if(find(nodes[n1], adjacency[n2]))
                continue;

            // add n1 to adjacency list of n2
            listOfObjects<Node *> *new_ele1 = new listOfObjects<Node *> (&(nodes[n1]));
            if(adjacency[n2] == nullptr)      // list not yet initiaized
                adjacency[n2] = new_ele1;
            else {                      // append new element at beginning of list
                new_ele1->next = adjacency[n2];
                adjacency[n2]->prev = new_ele1;
                adjacency[n2] = new_ele1;
            }

            // add n2 to adjacency of n1
            listOfObjects<Node *> *new_ele2 = new listOfObjects<Node *> (&(nodes[n2]));
            if(adjacency[n1] == nullptr)      // list not yet initiaized
                adjacency[n1] = new_ele2;
            else {                      // append new element at beginning of list
                new_ele2->next = adjacency[n1];
                adjacency[n1]->prev = new_ele2;
                adjacency[n1] = new_ele2;
            }
            // Create an undirected edge from n1 to n2 and store in appropriate
            // adjacency list(s).  If an undirected edge from n1 to n2 (or
            // equivalently from n2 to n1) already exists, you shouldn't add
            // an edge.  Only if such an undirected edge didn't exist earlier,
            // should you add the edge and increment countEdges; otherwise,
            // do not increment countEdges;
            // Every time an edge is created, we also add that information to
            // graphFile

            graphFile << n1+1 << " " << n2+1 << endl;
            countEdges++;
        }

        graphFile.close();
    }
        
    ~Graph() {
        if (graphFile.is_open()) {
            graphFile.close();
        }
        delete[] nodes;
        for(int i=0; i<numNodes; i++){
            while(adjacency[i] != nullptr) {
                listOfObjects<Node *> *temp = adjacency[i]->next;
                delete adjacency[i];
                adjacency[i] = temp;
            }
        }
        delete[] adjacency;
        // Add appropriate code as necessary for your implementation
    }

    // Add appropriate method declarations as necessary for your implementation

    void modifiedDFS();
    void printResults();
};

#endif
