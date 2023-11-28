#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef QUEUE
#include "queue.cpp"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
//=======================================================================================================//

class Node
{
public:
    int value;
    DynamicQueue<int> adjacencyList;
    DynamicQueue<int> similarNodes;
    int inCount, outCount, head;
    bool cond3done;

    Node()
    {
        value = inCount = outCount = 0;
        cond3done=false;
        head=-1;
    }

    Node(int val)
    {
        value = val;
        inCount = outCount = 0;
        cond3done=false;
        head=-1;
    }
    // insert other fields and methods as appropriate
};

struct Pair
{
    int a, b;

    Pair() { a = b = -1; }
    Pair(int v1, int v2)
    {
        a = v1;
        b = v2;
    }

    bool operator ==(Pair p)
    {
        if ((this->a == p.a && this->b == p.b))
            return true;
        else
            return false;
    }

    void operator =(Pair p)
    {
        this->a = p.a;
        this->b = p.b;
        return;
    }

    void printPair()
    {
        cout<<"("<<a+1<<", "<<b+1<<")";
    }
};

class Graph
{
    int numNodes;
    fstream graphFile;

    Node *nodes;
    DynamicQueue<int> sourceNodes;
    DynamicQueue<Pair> similars, condensedGraphEdges;
    // DynamicQueue<DynamicQueue<int>*> sets;
    bool *visited;

    DynamicQueue<int> condensedGraph;

public:
    Graph()
    {
        cin >> numNodes;

        nodes = new Node[numNodes];
        visited = new bool[numNodes];
        if (nodes == nullptr)
        {
            std::cerr << "Memory allocation failure." << std::endl;
            exit(-1);
        }
        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].value = i + 1;
            visited[i] = false;
        }

        int sourceIndex, targetIndex;

        cin >> sourceIndex >> targetIndex;
        // sourceIndex-=1;
        // targetIndex-=1;
        while (targetIndex != -1)
        {
            sourceIndex -= 1;
            targetIndex -= 1;
            if (sourceIndex == targetIndex)
                continue;

            if (nodes[sourceIndex].adjacencyList.QInsert(targetIndex))
            {
                nodes[sourceIndex].outCount++;
                nodes[targetIndex].inCount++;
            }
            
            cin >> sourceIndex >> targetIndex;
        }

        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].inCount == 0)
                sourceNodes.QInsert(i);
        }

        int node1, node2;
        
        cin >> node1 >> node2;
        while (node2 != -1)
        {
            node1 -= 1;
            node2 -= 1;
            if (nodes[node1].inCount != 0 || nodes[node2].inCount != 0)
                continue;
            Pair p(node1, node2);
            similars.QInsert(p);
            nodes[node1].similarNodes.QInsert(node2);
            nodes[node2].similarNodes.QInsert(node1);
            
            cin >> node1 >> node2;
        }
    }

    ~Graph()
    {
        if (graphFile.is_open())
        {
            graphFile.close();
        }
        // delete[] nodes;
        // Add appropriate code as necessary for your implementation
    }

    void connectedComps(int index, DynamicQueue<int> *set);
    void similarNodes();
    void compressGraph();
    void printResults();
};

#endif