#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

// TreeNode class
class TreeNode {
   public:
    int value;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value, TreeNode* parent = nullptr, TreeNode* left = nullptr, TreeNode* right = nullptr) {
        this->value = value;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }
};

// BST class
class BST {
    TreeNode* root;

    void insertInTree(int v, TreeNode* r) {
        if (r->value < v) {
            if (r->right == nullptr) r->right = new TreeNode(v, r);
            else insertInTree(v, r->right);
        } else {
            if (r->left == nullptr) r->left = new TreeNode(v, r);
            else insertInTree(v, r->left);
        }
    }

   public:
    BST() { root = nullptr; }

    BST(TreeNode* root) { this->root = root; }

    void insert(int v) {
        if (root == nullptr) root = new TreeNode(v);
        else insertInTree(v, root);
    }

    void UpdateParentChild(TreeNode* child, TreeNode* parent, bool isLeft) {
        if (parent != nullptr) {
            if (isLeft) parent->left = child;
            else parent->right = child;
        }
        if (child != nullptr) child->parent = parent;
    }

    // delete all TreeNode recursively
    void deleteAll(TreeNode* T) {
        if (T == nullptr) return;
        deleteAll(T->left);
        deleteAll(T->right);
        delete T;
    }

    
    void printBST(const string& prefix, bool isLeft = false) {
        if (root != nullptr) {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__");

            // print the value of the node
            cout << root->value << endl;
            TreeNode* curr = root;
            root = root->left;
            // enter the next tree level - left and right branch
            printBST(prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;
            printBST(prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }
    ~BST() { deleteAll(root); }
};

template <typename T>
class Linklist {
   public:
    T object;
    Linklist* next;
    Linklist* prev;

    Linklist() {
        next = nullptr;
        prev = nullptr;
    }
};

class Node {
   public:
    int value;
    bool isInCycle;
    int visit;
    int out;
    Linklist<int>* adjacency;

    Node(int value) {
        this->value = value;
        isInCycle = false;
        visit = 0;
        out = -1;
    }

    Node() { 
        isInCycle = false; 
        visit = 0;
        out = -1;
    }

    void addAdjacent(int N) {
        if (adjacency == nullptr) {
            adjacency = new Linklist<int>();
            adjacency->object = N;
            return;
        }
        adjacency->prev = new Linklist<int>();
        adjacency->prev->object = N;
        adjacency->prev->next = adjacency;
        adjacency = adjacency->prev;
    }

    bool isadjacent(int v) {
        if (adjacency == nullptr) return false;
        Linklist<int>* curr = adjacency;
        while (curr != nullptr) {
            if (curr->object == v) return true;
            curr = curr->next;
        }
        return false;
    }
};

class Graph {
    int numNodes;
    int numEdges;
    fstream graphFile;
    int visitedOne = 0, visitedTwice = 0, inloop = 0, currectedComponent = 0;
    Node* nodes;
    Linklist<BST*>* B;
    // Add appropriate fields as necessary for your implementation

   public:
    Graph(int nNodes, int nEdges, string gFileName) {
        visitedOne = 0;
        visitedTwice = 0;
        inloop = 0;
        currectedComponent = 0;
        numNodes = nNodes;
        numEdges = nEdges;
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
            nodes[i].value = i + 1;
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
            if (nodes[n1].isadjacent(n2)) continue;
            nodes[n1].addAdjacent(n2);
            nodes[n2].addAdjacent(n1);
            // adjacency list(s).  If an undirected edge from n1 to n2 (or
            // equivalently from n2 to n1) already exists, you shouldn't add
            // an edge.  Only if such an undirected edge didn't exist earlier,
            // should you add the edge and increment countEdges; otherwise,
            // do not increment countEdges;
            // Every time an edge is created, we also add that information to
            // graphFile

            graphFile << n1 + 1 << " " << n2 + 1 << endl;
            countEdges++;
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
    void visitDFS(int N, BST* B,Linklist<int>*, int parent = -1);
};

#endif
