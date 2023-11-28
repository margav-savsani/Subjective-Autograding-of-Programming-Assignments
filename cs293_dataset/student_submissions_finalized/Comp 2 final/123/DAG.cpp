#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class Node
{
public:
    int value;
    // insert other fields and methods as appropriate
    // Adjacency list storing neighbours
    int *inneighbours;
    int *outneighbours;
    int *simNodes;
    bool amSource;
    // Constructor
    Node()
    {
        value = -1;
        amSource = true;
    }
    void setSize(int size)
    {
        inneighbours = new int[size];
        outneighbours = new int[size];
        simNodes = new int[size];
        for (int i = 0; i < size; i++)
        {
            inneighbours[i] = 0;
            outneighbours[i] = 0;
            simNodes[i] = 0;
        }
    }
    bool addinNeighbours(int node)
    {
        if (inneighbours[node] == 1)
        {
            return false;
        }
        else
        {
            inneighbours[node] = 1;
            amSource = false;
            // tp = true;
            return true;
        }
    }
    bool addoutNeighbours(int node)
    {
        if (outneighbours[node] == 1)
        {
            return false;
        }
        else
        {
            outneighbours[node] = 1;
            return true;
        }
    }
    bool addsimNodes(int node, Node *nodes)
    {
        if (simNodes[node] == 1)
        {
            return false;
        }
        else
        {
            simNodes[node] = 1;
            return true;
        }
    }
};


bool checkSim(int *node1, int *node2, int size, Node *nodes)
{
    // We get 2 list of nodes. we will check each node is related and all will be covered

    // STAGE 1:
    //  Check node1 to node2 i.e., check if each node in node1 is covered

    // Check each node of node1 is related to each node of node2
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (node1[i] == 1)
        {
            // node in node1 is 'i'
            bool found = false;
            for (int j = 0; j < size; j++)
            {
                if (node2[j] == 1)
                {
                    // Node in node2 is 'j'
                    if (nodes[i].simNodes[j] == 1)
                    {
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
            {
                return false;
            }
            count++;
        }
    }
    if (count == 0)
    {
        return false;
    }

    // STAGE 2:
    // Check each node of node2 is related to each node of node1
    count = 0;
    for (int i = 0; i < size; i++)
    {
        if (node2[i] == 1)
        {
            // node in node2 is 'i'
            bool found = false;
            for (int j = 0; j < size; j++)
            {
                if (node1[j] == 1)
                {
                    // Node in node1 is 'j'
                    if (nodes[i].simNodes[j] == 1)
                    {
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
            {
                return false;
            }
            count++;
        }
    }
    if (count == 0)
    {
        return false;
    }

    return true;
}

bool updateSimNodes(Node *nodes, int size)
{
    for (int j = 0; j < size; j++)
    {
        // Each node n1
        int *n1_neighbours = new int[size];
        // Counting all neighbours
        for (int i = 0; i < size; i++)
        {
            n1_neighbours[i] = nodes[j].inneighbours[i];
        }

        // Check Similarity by passing both n1_neighbours and n2_neighbours
        for (int i = 0; i < size; i++)
        {
            // Other nodes
            if (i != j && n1_neighbours[i] != 1)
            {
                int *n2_neighbours = new int[size];
                // Counting all neighbours
                for (int k = 0; k < size; k++)
                {
                    n2_neighbours[k] = nodes[i].inneighbours[k];
                }
                bool found = checkSim(n1_neighbours, n2_neighbours, size, nodes);
                if (found)
                {
                    nodes[j].simNodes[i] = 1;
                }
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        int lol = -1;
        for (int j = 0; j < size; j++)
        {
            if (nodes[i].inneighbours[j] == 1)
            {
                count++;
                lol = j;
            }
        }
        if (count == 1)
        {
            nodes[i].simNodes[lol] = 1;
        }
    }
    return true;
}

void makeSymm(Node *nodes, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (nodes[i].simNodes[j] == 1)
            {
                nodes[j].simNodes[i] = 1;
            }
        }
    }
}

void makeTrans(Node *nodes, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (nodes[i].simNodes[j] == 1)
            {
                for (int k = 0; k < size; k++)
                {
                    if (nodes[j].simNodes[k] == 1)
                    {
                        nodes[i].simNodes[k] = 1;
                    }
                }
            }
        }
    }
}

class DAG
{
public:
    int numNodes;
    int numEdges;
    Node *nodes;
    int *arr;
    ofstream file;

    DAG()
    {
        cin >> numNodes;
        int n1(0), n2(0);
        nodes = new Node[numNodes];
        arr = new int[numNodes];
        file = ofstream("outGraph.txt");
        if (nodes == nullptr)
        {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
        }
        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].setSize(numNodes);
        }
        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].value = i + 1;
        }
        while (n1 != -1 && n2 != -1 && n1 <= numNodes && n2 <= numNodes)
        {
            cin >> n1 >> n2;
            if (n1 == -1 || n2 == -1)
            {
                break;
            }
            nodes[n1 - 1].addoutNeighbours(n2 - 1);
            nodes[n2 - 1].addinNeighbours(n1 - 1);
        }
        n1 = n2 = 0;
        while (n1 != -1 && n2 != -1 && n1 <= numNodes && n2 <= numNodes)
        {
            cin >> n1 >> n2;
            if (n1 == -1 || n2 == -1)
            {
                break;
            }
            nodes[n1 - 1].addsimNodes(n2 - 1, nodes);
        }
    }

    ~DAG()
    {
        delete[] nodes;
        file.close();
    }
    void getSources()
    {
        file << "Source Nodes : ";
        for (int i = 0; i < numNodes; i++)
        {
            // if(nodes[i].tp){
            if (nodes[i].amSource)
            {
                file << i + 1 << " ";
            }
            // }
        }
        file << endl;
    }
    void getSimilarNodePairs()
    {
        updateSimNodes(nodes, numNodes);
        updateSimNodes(nodes, numNodes);
        file << "Similar Nodes: ";
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (nodes[i].simNodes[j] == 1)
                {
                    file << "(" << i + 1 << "," << j + 1 << ") ";
                }
            }
        }
        file << endl;
    }

    void caller()
    {
        makeSymm(nodes, numNodes);
        makeTrans(nodes, numNodes);
        collapsedGraph();
    }

    int *collapse()
    {
        int size = numNodes;
        static int count = 1;
        if (count == 1)
        {
            for (int i = 0; i < size; i++)
            {
                arr[i] = 0;
            }
        }
        bool found = false;
        for (int i = 0; i < size; i++)
        {
            found = (arr[i] == 0);
            if (found)
            {
                arr[i] = count;
                break;
            }
        }
        if (found)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (i != j && arr[j] == 0)
                    {
                        if (nodes[i].simNodes[j] == 1)
                        {
                            arr[j] = arr[i];
                        }
                    }
                }
            }
            count++;
            collapse();
        }
        else
        {
            return arr;
        }
        return arr;
    }

    void collapsedGraph()
    {
        int *arr = collapse();
        int N = 0;
        for (int i = 0; i < numNodes; i++)
        {
            if (arr[i] > N)
            {
                N = arr[i];
            }
        }
        if (N <= 0)
        {
            file << "N = 0" << endl;
            abort();
        }
        int collapsed[N];
        Node nods[N];
        for (int i = 0; i < N; i++)
        {
            nods[i].setSize(N);
            collapsed[i] = 0;
        }
        for (int i = 0; i < numNodes; i++)
        {
            if (collapsed[arr[i] - 1] < i)
            {
                collapsed[arr[i] - 1] = i;
            }
        }
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (arr[i] != arr[j] && (nodes[i].inneighbours[j] == 1))
                {
                    nods[arr[i]-1].addinNeighbours(arr[j] - 1);
                    nods[arr[j]-1].addoutNeighbours(arr[i] - 1);
                }
                if (arr[i] != arr[j] && (nodes[i].outneighbours[j] == 1))
                {
                    nods[arr[i]-1].addoutNeighbours(arr[j] - 1);
                    nods[arr[j]-1].addinNeighbours(arr[i] - 1);
                }
            }
        }
        file << N << ": ";
        for (int i = 0; i < N; i++)
        {
            file << collapsed[i] + 1 << " ";
        }
        file << endl;
        // for (int i = 0; i < numNodes; i++)
        // {
        //     file << arr[i] << " ";
        // }
        
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (nods[i].inneighbours[j] == 1 )
                {
                    file << collapsed[j] + 1<< " " << collapsed[i] + 1<< endl;
                }
            }    
        } 
    }

};

#endif
