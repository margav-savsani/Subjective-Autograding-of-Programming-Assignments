#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T>
class list
{
public:
    T object;
    list<T> *next = nullptr;
    list<T> *prev = nullptr;

    // Constructor
    list(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }

    // Destructor
    ~list() { ; }
};

class BST
{
    // Add your own field and members here
    int value;
    BST *left = nullptr, *right = nullptr, *parent = nullptr;

public:
    BST(int val) { value = val; }

    void insert(int val)
    {
        if (val <= value)
        {
            if (left == nullptr)
            {
                left = new BST(val);
                left->parent = this;
            }
            else
                left->insert(val);
        }
        else
        {
            if (right == nullptr)
            {
                right = new BST(val);
                right->parent = this;
            }
            else
                right->insert(val);
        }
    }

    void printBST(const string &prefix = "", bool isLeft = false)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << value << endl;
        if (left != nullptr)
            left->printBST(prefix + (isLeft ? "|   " : "    "), true);
        if (right != nullptr)
            right->printBST(prefix + (isLeft ? "|   " : "    "), false);
    }

    // Feel free to use the printBST function used earlier
};

class Node
{
public:
    int value;

    list<Node *> *adjacency = nullptr;
    // insert other fields and methods as appropriate

    Node() {}
    Node(int v) { value = v; }

    Node *isAdjacent(Node x)
    {
        list<Node *> *temp = adjacency;
        while (temp != nullptr)
        {
            if (temp->object->value == x.value)
                return temp->object;
            temp = temp->next;
        }
        return nullptr;
    }

    void addAdjacent(Node *x)
    {
        if (adjacency == nullptr)
        {
            adjacency = new list<Node *>(x);
            return;
        }
        else
        {
            list<Node *> *temp = adjacency, *p = nullptr;
            while (temp != nullptr && temp->object->value < x->value)
            {
                p = temp;
                temp = temp->next;
            }
            if (p == nullptr)
            {
                list<Node *> *t = new list<Node *>(x);
                t->next = adjacency;
                adjacency->prev = t;
                adjacency = t;
            }
            else if (temp == nullptr)
            {
                p->next = new list<Node *>(x);
                p->next->prev = p;
            }
            else
            {
                list<Node *> *t = new list<Node *>(x);
                p->next = t;
                temp->prev = t;
                t->next = temp;
                t->prev = p;
            }
        }
    }

    void removeAdjacency(int val)
    {
        list<Node *> *temp = adjacency;
        while (temp != nullptr && temp->object->value != val)
            temp = temp->next;
        if (temp == nullptr)
            return;
        if (temp->prev == nullptr && temp->next == nullptr)
            adjacency = nullptr;
        else if (temp->prev == nullptr)
        {
            adjacency = temp->next;
            adjacency->prev = nullptr;
        }
        else if (temp->next == nullptr)
        {
            temp->prev->next = nullptr;
        }
        else
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
    }
};

class Graph
{
    int numNodes;
    int numEdges;
    fstream graphFile;

    Node *nodes;
    list<BST *> *trees = nullptr;
    int numConnectedComponents = 0;
    int numNodesVisitOnce = 0;
    int numNodesVisitTwice = 0;

    // Add appropriate fields as necessary for your implementation

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

        // Handling Exception for not possible graphs
        if (numNodes * (numNodes - 1) < 2 * numEdges)
        {
            cerr << "Graph Not Possible, too many edges for given number of nodes." << endl;
            exit(-1);
        }

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
        // srand(0);
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
            if (nodes[n1].isAdjacent(nodes[n2]) == nullptr)
            {
                nodes[n1].addAdjacent(&(nodes[n2]));
                nodes[n2].addAdjacent(&(nodes[n1]));
                graphFile << n1 + 1 << " " << n2 + 1 << endl;
                countEdges++;
            };
        }

        // Add appropriate code as necessary for your implementation
        // graphFile << "\nAdjacency List:" << endl;
        // for (int i = 0; i < numNodes; i++)
        // {
        //     graphFile << "Node : " << i + 1 << endl;
        //     list<Node *> *a = nodes[i].adjacency;
        //     if (a == nullptr)
        //         graphFile << "\tNo adjacent Nodes" << endl;
        //     while (a != nullptr)
        //     {
        //         graphFile << "\t" << i + 1 << "--------" << a->object->value << endl;
        //         a = a->next;
        //     }
        // }
    }

    ~Graph()
    {
        if (graphFile.is_open())
        {
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
