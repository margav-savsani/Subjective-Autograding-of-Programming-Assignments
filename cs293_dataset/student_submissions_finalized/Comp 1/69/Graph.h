#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <list>
#include <string>
using namespace std;

struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyvalue) : value(jrnyvalue), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyvalue, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(jrnyvalue), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
    TreeNode *root;

public:
    BST(){root = NULL; }
    BST(TreeNode *root){this->root = root; }
    void printBST(const string &prefix, bool isLeft = false)
    {
        if (root != nullptr)
        {
            cout << prefix;
            cout << (isLeft ? "|--" : "|__");
            cout << '(' << root->value << ')' << endl;
            TreeNode *curr = root;
            root = root->left;
            printBST(prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;
            printBST(prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }
    void insert(int value)
    {
        if (root == NULL)
        {
            root = new TreeNode(value, NULL, NULL, NULL);
        }
        TreeNode *curr = root;
        while (true)
        {
            if (value > curr->value)
            {
                if (curr->right != NULL)
                {
                    curr = curr->right;
                }
                else
                {
                    curr->right = new TreeNode(value, NULL, NULL, curr);
                    break;
                }
            }
            else
            {
                if (curr->left != NULL)
                {
                    curr = curr->left;
                }
                else
                {
                    curr->left = new TreeNode(value, NULL, NULL, curr);
                    break;
                }
            }
        }
    }
};

// template <typename T>
// class listOfObjects
// {
// public:
//     T object;
//     listOfObjects<T> *next;
//     listOfObjects<T> *prev;
//     listOfObjects(T initValue)
//     {
//         object = initValue;
//         next = prev = nullptr;
//     }
//     ~listOfObjects() { ; }
// };

class Node
{
public:
    int value;

    // insert other fields and methods as appropriate
    int visit;
    list<Node *> adj;
    Node(){visit = 0;}
    // Node(int val, int vis, listOfObjects<Node *> *p){
    //     value = val;
    //     vis = visit;
    //     A = p;
    // }
    ~Node(){;}
    // listOfObjects<Node*> *A;
};

class Graph
{
    int numNodes;
    int numEdges;
    fstream graphFile;

    Node *nodes;

    // Add appropriate fields as necessary for your implementation
    BST *trees = new BST();
    int comp = 0;
    // int *V = new int[numNodes];

public:
    Graph(int nNodes, int nEdges, string gFileName)
    {
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

            // Create an undirected edge from n1 to n2 and store in appropriate
            // adjacency list(s).  If an undirected edge from n1 to n2 (or
            // equivalently from n2 to n1) already exists, you shouldn't add
            // an edge.  Only if such an undirected edge didn't exist earlier,
            // should you add the edge and increment countEdges; otherwise,
            // do not increment countEdges;
            // Every time an edge is created, we also add that information to
            // graphFile
            // bool k = false;
            // listOfObjects<Node *> *p = nodes[n1].A;
            // while(p->object != nullptr){
            //     if(p->object->value == nodes[n2].value){
            //         k = true;
            //         break;
            //     }
            //     p = p->next;
            // }
            
                // add adjacents
                // Node *a = &nodes[n1];
                // Node *b = &nodes[n2];
                // nodes[n1].A->next->object = b;
                // nodes[n2].A->next->object = a;
                // nodes[n1].A = nodes[n1].A->next;
                // nodes[n2].A = nodes[n2].A->next;
            bool k = false;
            list<Node *> p = nodes[n1].adj;
            while(p.front() != nullptr){
                if(p.front()->value == nodes[n2].value){
                    k = true;
                    break;
                }
                p.pop_front();
            }
            if(!k){


                nodes[n1].adj.push_back(&nodes[n2]);
                nodes[n2].adj.push_back(&nodes[n1]);
                graphFile << n1 + 1 << " " << n2 + 1 << endl;
                countEdges++;
            }
        }

        // Add appropriate code as necessary for your implementation
    }

    ~Graph()
    {
        if (graphFile.is_open())
        {
            graphFile.close();
        }
        delete[] nodes;
        // delete []V;
        // Add appropriate code as necessary for your implementation
    }

    // Add appropriate method declarations as necessary for your implementation

    void modifiedDFS();
    void printResults();
    void DFS(Node *node);
    string numSingle();
    string numDouble();
    int numComp();
    int numCycle();
    void printTrees();
};

#endif