#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

// Using Stack for keeping track of the elements in DFS it is useful in detecting cycles.
class Stack
{

public:
    int top = -1;
    int size;

    int *arr;
    Stack(int size)
    {
        this->size = size;
        arr = new int[size];
    }
    void print()
    {
        for (int i = 0; i <= top; i++)
        {
            cout << arr[i] + 1 << " ";
        }
        cout << endl;
    }
    void insert(int k)
    {
        top++;
        arr[top] = k;
    }
    void remove()
    {
        arr[top] = -1;
        top--;
    }
    int top_element()
    {
        return arr[top];
    }
    int find_from_first(int n)
    {
        for (int i = 0; i <= top; i++)
        {
            if (arr[i] == n)
            {
                return i;
            }
        }
        return -1;
    }
    int find_from_last(int n)
    {
        for (int i = top; i >= 0; i--)
        {
            if (arr[i] == n)
            {
                return i;
            }
        }
        return -1;
    }
};

// TreeNode for BST
struct TreeNode
{
    int node_number;  // Node Number
    TreeNode *left;   // Left Child of this Node (NULL, if None)
    TreeNode *right;  // Right Child of this Node (NULL, if None)
    TreeNode *parent; // The Parent Node, NULL in case of Root

    // Constructors

    TreeNode() : node_number(0), left(nullptr), right(nullptr) {}
    TreeNode(int number) : node_number(number), left(nullptr), right(nullptr) {}
    TreeNode(int number, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : node_number(number), left(leftChild), right(rightChild), parent(parent) {}
};

// The BST Class with insert and printBST function only as they are only needed
class BST
{
    TreeNode *root;

public:
    BST()
    {
        root = new TreeNode;
        root = NULL;
    }
    BST(TreeNode *root)
    {
        this->root = new struct TreeNode;
        this->root = root;
    }

    TreeNode *minforsuccessor(TreeNode *N);
    void printBST(const string &prefix = "", bool isLeft = false)
    {
        if (root != nullptr)
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__");

            cout << root->node_number << endl;
            TreeNode *curr = root;
            root = root->left;

            printBST(prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;

            printBST(prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }


    bool insert(int nodeNumber)
    {
        if (root == nullptr)
        {
            root = new struct TreeNode(nodeNumber);
            root->parent = NULL;
            return true;
        }
        TreeNode *k = root;
        TreeNode *naya = new struct TreeNode(nodeNumber);
        while (true)
        {
            if ((naya->node_number) >= (k->node_number))
            {
                if (k->right == NULL)
                {
                    k->right = naya;
                    naya->parent = k;
                    return true;
                }
                else
                {
                    k = k->right;
                }
            }
            if ((naya->node_number) < (k->node_number))
            {
                if (k->left == NULL)
                {
                    k->left = naya;
                    naya->parent = k;
                    return true;
                }
                else
                {
                    k = k->left;
                }
            }
        }
    }
};

// Class which contains info on node of the graph
class Node
{
public:
    int value;
    int visited = 0;// Tracking the number of times a node has been visited
    bool in_a_cycle = false;// Whether this node is present in a cycle
};


// linked list for the adjacency list
template <typename T>
class listOfObjects
{
public:
    T object;
    listOfObjects<T> *next;
    // Constructor
    listOfObjects(T initValue)
    {
        object = initValue;
        next = nullptr;
    }
    listOfObjects() { next = nullptr; }
    // Destructor
    ~listOfObjects() { ; }
};

// adds a value to an ll
template <typename T>
void add_ll(listOfObjects<T> *&L, T val)
{
    if (L == nullptr)
    {
        L = new listOfObjects<T>(val);
        return;
    }
    else
    {
        listOfObjects<T> *curr = L;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = new listOfObjects<T>(val);
        return;
    }
}

// only adds a value to a ll if it is not already there else returns false
template <typename T>
bool add_ll_unique(listOfObjects<T> *&L, T val)
{
    if (L == nullptr)
    {
        L = new listOfObjects<T>(val);
        return true;
    }
    else
    {
        listOfObjects<T> *curr = L;
        while (curr->next != nullptr)
        {
            if (curr->object == val)
            {
                return false;
            }
            curr = curr->next;
        }
        if (curr->object == val)
            return false;
        curr->next = new listOfObjects<T>(val);
        return true;
    }
}


// main graph class
class Graph
{
    
    int numNodes;
    int numEdges;
    fstream graphFile;
    // The stack stores at each time which element are present in the recursion stack
    Stack *S;
    Node *nodes;
    // the number of connected components in the graph
    int connected_components;
    // The number of nodes which are visited only ones
    int singly_visited;
    // The number of present in a cycles
    int Nodes_in_cycles;
    // The adjacency list array
    listOfObjects<int> **adjacency;
public:
    Graph(int nNodes, int nEdges, string gFileName)
    {
        // max size of stack would be 2*number of nodes
        S = new Stack(2 * nNodes);
        singly_visited = 0;
        connected_components = 0;
        Nodes_in_cycles = 0;
        adjacency = new listOfObjects<int> *[nNodes];
        numNodes = nNodes;
        numEdges = nEdges;
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

        while (countEdges < numEdges)
        {
            do
            {
                n1 = rand() % numNodes;
                n2 = rand() % numNodes;
            } while (n1 == n2);
            // If we can add n2 to adjacency of n1 it means the edge is not present
            // If we can't add the implementation of add_ll_unique doesnt add n2 to adjacency of n1
            if (add_ll_unique(adjacency[n1], n2))
            {
                add_ll_unique(adjacency[n2], n1);
            }
            else
            {   
                //continuing so that we do not increment countEdges
                continue;
            }
            graphFile << n1 + 1 << " " << n2 + 1 << endl;
            countEdges++;
        }
    }

    ~Graph()
    {
        if (graphFile.is_open())
        {
            //   myGraph->printResults();
            graphFile.close();
        }
        delete[] nodes;
        // Add appropriate code as necessary for your implementation
    }

    // Add appropriate method declarations as necessary for your implementation
    // A Helper function for DFS i is the source node and NodesTree is just the BST we need to add the nodes to
    void DFSHelper(int i, BST &NodesTree);
    void modifiedDFS();
    void printResults();
};

#endif
