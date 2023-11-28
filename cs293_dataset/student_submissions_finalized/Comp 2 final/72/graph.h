#include "std_headers.h"
using namespace std;

template <typename T>
class listOfObjects
{
public:
    T object;
    listOfObjects<T> *next;
    listOfObjects<T> *prev;
    listOfObjects(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }
    ~listOfObjects() { ; }
};

class Node
{
public:
    int value;
    int idx;
    // index of its parent in the traversal
    int pindx;
    // Adjacency list of a node
    listOfObjects<Node> *adjout;
    listOfObjects<Node> *tailout;
    listOfObjects<Node> *adjin;
    listOfObjects<Node> *tailin;
    // insert other fields and methods as appropriate
    Node()
    {
        adjout = nullptr;
        tailout = nullptr;
        adjin = nullptr;
        tailin = nullptr;
    }
};

class Graph
{
public:
    int numNodes;
    Node *nodes;
    int *simarray;// Similar Node pairs
    int *adj;
    int *connected;
    // To keep track of number of times a node is visited
    bool *visited;
    bool *source;
    fstream file;

    Graph(int nnodes)
    {
        numNodes = nnodes;
        nodes = new Node[numNodes];
        visited = new bool[numNodes];
        source = new bool[numNodes];
        connected = new int[numNodes];
        simarray = new int[numNodes * numNodes];
        adj = new int[numNodes * numNodes];
        file.open("outgraph.txt",ios::out);


        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].value = i + 1;
            nodes[i].idx = i;
            nodes[i].pindx = -1;
            source[i] = true;
            visited[i] = false;
            connected[i] = 0;
        }
        for (int i = 0; i < numNodes * numNodes; i++)
        {
            adj[i] = 0;
            simarray[i] = 0;
        }
    }

    bool edgePresent(int n1, int n2);
    void removeEdge(int n1, int n2);
    void addEdge(int n1, int n2);
    void addSim(int n1, int n2);
    bool SimPresent(int n1, int n2);
    void collapse();// Collapse graph function
};