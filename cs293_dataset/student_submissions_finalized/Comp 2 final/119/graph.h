#include "stdHeaders.h"

// -------------------------- linkedListNode and linkedList --------------------------

template <typename T>
class linkedListNode
{
public:
    T value;
    linkedListNode<T> *prev = NULL, *next = NULL;
};

template <typename T>
class linkedList
{
public:
    linkedListNode<T> *head = NULL, *tail = NULL;

    void insert(linkedListNode<T> *v)
    {
        if (head == NULL)
            head = tail = v;
        else
        {
            tail->next = v;
            v->prev = tail;

            tail = v;
        }
    }
};

// -------------------------- BST, GRAPH, and NODE --------------------------

void Error(string m)
{
    cerr << m << endl;
    exit(-1);
}

struct Node
{
    int value;
    linkedList<int> adjNodeIndexes;
};

class Graph
{
    int numNodes = 0;
    int numEdges = 0;
    bool *sources;
    int *sourcesIndex;
    int numSources;
    int numSourcesIndex;
    bool **edgeMatrix;
    bool **relatedMatrix;

    Node *nodes;
    ofstream output;

public:
    Graph(string filename)
    {
        output = ofstream(filename);

        cin >> numNodes;
        nodes = new Node[numNodes];
        sources = new bool[numNodes];
        numSourcesIndex = numSources = numNodes;
        sourcesIndex = new int[numNodes];

        relatedMatrix = new bool *[numNodes];
        edgeMatrix = new bool *[numNodes];
        for (int i = 0; i < numNodes; i++)
        {
            relatedMatrix[i] = new bool[numNodes]();
            edgeMatrix[i] = new bool[numNodes]();
        }

        sources = new bool[numNodes];
        for (int i = 0; i < numNodes; i++)
            sources[i] = 1;

        int n1, n2;
        int stage = 1;
        while (true)
        {
            cin >> n1 >> n2;
            if (n1 == -1 && n2 == -1)
            {
                if (stage == 1)
                    stage = 2;
                else if (stage == 2)
                    break;
            }

            if (stage == 1)
            {
                edgeMatrix[n1 - 1][n2 - 1] = 1;
                numEdges++;

                if (sources[n2 - 1])
                {
                    sources[n2 - 1] = 0;
                    numSources--;
                }
            }
            else if (stage == 2)
                if (sources[n1 - 1] && sources[n2 - 1])
                    relatedMatrix[n1 - 1][n2 - 1] = 1;
        }

        // numNodes = nNodes;
        // numEdges = nEdges;

        // graphFile.open(gFileName, ios::out);

        // if (!graphFile.is_open())
        //     Error("Couldn't open graph file. Aborting ...");

        // graphFile << numNodes << endl;
        // graphFile << numEdges << endl;

        // nodes = new Node[numNodes];
        // if (nodes == nullptr)
        //     Error("Memory allocation failure.");

        // for (int i = 0; i < numNodes; i++)
        //     nodes[i].value = i + 1;

        // srand(time(0));
        // int n1, n2;
        // int countEdges = 0;

        // while (countEdges < numEdges)
        // {
        //     linkedListNode<int> *one = new linkedListNode<int>;
        //     linkedListNode<int> *two = new linkedListNode<int>;
        //     while (true)
        //     {
        //         do
        //         {
        //             n1 = rand() % numNodes;
        //             n2 = rand() % numNodes;
        //         } while (n1 == n2);

        //         if (linkedListUniqueInsertCheck(nodes[n1].adjNodeIndexes, n2) &&
        //             linkedListUniqueInsertCheck(nodes[n2].adjNodeIndexes, n1))
        //         {
        //             one->value = n1;
        //             two->value = n2;
        //             break;
        //         }
        //     }

        //     nodes[n1].adjNodeIndexes.insert(two);
        //     nodes[n2].adjNodeIndexes.insert(one);

        //     graphFile << n1 + 1 << " " << n2 + 1 << endl;
        //     countEdges++;
        // }
    }

    ~Graph()
    {
        output.close();
        delete[] nodes;
    }

    void similarityB();
    void similarityC();
    void printSources();
    void printRelated();
    void collapse();
    void printCollapse();
};