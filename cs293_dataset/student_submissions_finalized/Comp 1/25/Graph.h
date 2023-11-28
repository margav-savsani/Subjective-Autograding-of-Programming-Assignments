#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <cmath>
using namespace std;

struct TreeNode
{
    int value;
    TreeNode *left;   // Left Child of this Node (NULL, if None)
    TreeNode *right;  // Right Child of this Node (NULL, if None)
    TreeNode *parent; // The Parent Node, NULL in case of Root

    // Constructors

    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
    TreeNode(int value, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(value), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
public:
    TreeNode *root;
    BST()
    {
        root = nullptr;
    }
    BST(TreeNode *root) : root(root) {}
    void insert(int val)
    {
        TreeNode *next = root;
        TreeNode *node = nullptr;
        while (next != nullptr)
        {
            node = next;
            if (next->value > val)
            {
                next = next->left;
            }
            else
            {
                next = next->right;
            }
        }
        // Now node is where we have to insert the new ticket.
        // If node is nullptr, we need to create a node and make it root.
        if (node==nullptr){
            root = new TreeNode(val, nullptr, nullptr, nullptr);
        }
        else if (node->value>val){
            node->left = new TreeNode(val, nullptr, nullptr, node);
        }
        else {
            node->right = new TreeNode(val, nullptr, nullptr, node);
        }
    }

    // Feel free to use the printBST function used earlier
    void printBST(const string& prefix, bool isLeft=false)
    {
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


class Edge
{
public:
    int node1;
    int node2;
    Edge()
    {
        node1 = -1;
        node2 = -1;
    }
    Edge(int n1, int n2) : node1(n1), node2(n2) {}
    bool operator==(Edge b)
    {
        return (node1 == b.node1 && node2 == b.node2 || node1 == b.node2 && node2 == b.node1);
    }
};

enum shade {White, Grey, Black};

class Node
{
public:
    int value;
    int neighbours;
    int *adjacent;
    int visited;
    int parent1;
    int parent2;
    bool cycle;
    shade color;
    Node()
    {
        value = 0;
        neighbours = 0;
        adjacent = nullptr;
        visited = 0;
        parent1 = -1; parent2=-1;
        cycle = false;
        color = White;
    }

    // insert other fields and methods as appropriate
};

bool edgeExists(Edge *edges, Edge e, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (edges[i] == e)
        {
            return true;
        }
    }
    return false;
}

class Graph
{
    int numNodes;
    int numEdges;
    fstream graphFile;

    Node *nodes;

    Edge *edges;
    int connectedComponents;
    BST* trees;
    int treeCount;

public:
    Graph(int nNodes, int nEdges, string gFileName)
    {
        numNodes = nNodes;
        numEdges = nEdges;
        connectedComponents = 0;
        edges = new Edge[numEdges];
        treeCount = 0;
        trees = new BST[(int)(numNodes+1 - sqrt(2*numEdges))];
        graphFile.open(gFileName, ios::out);
        if (!graphFile.is_open())
        {
            cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
            exit(-1);
        }

        graphFile << numNodes << endl;
        graphFile << numEdges << endl;

        nodes = new Node[numNodes];
        if (nodes == nullptr)
        {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
        }

        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].value = i + 1;
        }

        srand(time(0));
        int n1, n2;
        int countEdges = 0;

        while (countEdges < numEdges) {
            do {
                n1 = rand() % numNodes;
                n2 = rand() % numNodes;
            } while (n1 == n2 || edgeExists(edges, Edge(n1, n2), countEdges));

            // Create an undirected edge from n1 to n2 and store in appropriate
            // adjacency list(s).  If an undirected edge from n1 to n2 (or
            // equivalently from n2 to n1) already exists, you shouldn't add
            // an edge.  Only if such an undirected edge didn't exist earlier,
            // should you add the edge and increment countEdges; otherwise,
            // do not increment countEdges;
            // Every time an edge is created, we also add that information to
            // graphFile
            edges[countEdges] = Edge(n1, n2);
            nodes[n1].neighbours++;
            nodes[n2].neighbours++;

            // cout << n1 + 1<<" "<< n2 + 1<<endl;
            graphFile << n1 + 1 << " " << n2 + 1 << endl;
            countEdges++;
        }

        // Allocate space for adjacency lists
        int adjcount[numNodes];
        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].adjacent = new int[nodes[i].neighbours];
            adjcount[i] = 0;
        }
        // Now go over the edges and create adjacency lists
        for (int i = 0; i < numEdges; i++)
        {
            n1 = edges[i].node1;
            n2 = edges[i].node2;
            nodes[n1].adjacent[adjcount[n1]] = n2;
            nodes[n2].adjacent[adjcount[n2]] = n1;
            adjcount[n1]++;
            adjcount[n2]++;
        }
        graphFile.close();
    }

    ~Graph()
    {
        if (graphFile.is_open())
        {
            graphFile.close();
        }
        delete[] nodes;
        delete[] edges;
    }


    void modifiedDFS();
    void DFS_visit(int x);
    void printResults();
};

#endif
