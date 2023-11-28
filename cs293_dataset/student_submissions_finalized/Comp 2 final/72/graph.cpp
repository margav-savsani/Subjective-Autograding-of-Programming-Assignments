#include "std_headers.h"
#include "graph.h"

// Checking whether an edge is present already in the graph
bool Graph::edgePresent(int n1, int n2)
{
    int i = n1 * numNodes + n2;
    return (adj[i] == 1);
    listOfObjects<Node> *poin = nodes[n1].adjout;
    while (poin != nullptr)
    {
        if (poin->object.value == nodes[n2].value)
            return true;
        poin = poin->next;
    }
    return false;
}

// Adding a directed edge in the graph
void Graph::addEdge(int n1, int n2)
{
    source[n2] = false;
    int i = n1 * numNodes + n2;
    adj[i] = 1;
    if (nodes[n1].adjout == nullptr)
    {
        nodes[n1].adjout = new listOfObjects<Node>(nodes[n2]);
        nodes[n1].tailout = nodes[n1].adjout;
    }
    else
    {
        nodes[n1].tailout->next = new listOfObjects<Node>(nodes[n2]);
        nodes[n1].tailout = nodes[n1].tailout->next;
    }
    if (nodes[n2].adjin == nullptr)
    {
        nodes[n2].adjin = new listOfObjects<Node>(nodes[n1]);
        nodes[n2].tailin = nodes[n2].adjin;
    }
    else
    {
        nodes[n2].tailin->next = new listOfObjects<Node>(nodes[n1]);
        nodes[n2].tailin = nodes[n2].tailin->next;
    }
    return;
}

// Whether a pair is similar or not
bool Graph::SimPresent(int n1, int n2)
{
    int i = n1 * numNodes + n2;
    return (simarray[i] == 1);
}

// Adding a similar pair
void Graph::addSim(int n1, int n2)
{
    int i = n1 * numNodes + n2;
    simarray[i] = 1;
    return;
}

void Graph::collapse()
{
    for (int i = 0; i < numNodes * numNodes; i++)
    {
        if (simarray[i] == 1)
        {
            int s1 = i / numNodes;
            int s2 = i % numNodes;
            if (s1 == s2)
                continue;
            if (s1 <= s2)
            {
                int t = s2;
                s2 = s1;
                s1 = t;
            }
            for (int j = 0; j < numNodes; j++)
            {
                if (adj[s2 * numNodes + j])
                {
                    adj[s1 * numNodes + j] = 1;
                    adj[s2 * numNodes + j] = 0;
                }
                if (simarray[s2 * numNodes + j])
                {
                    simarray[s1 * numNodes + j] = 1;
                    simarray[s2 * numNodes + j] = 0;
                }

                if (adj[s2 + numNodes * j])
                {
                    adj[s1 + numNodes * j] = 1;
                    adj[s2 + numNodes * j] = 0;
                }
                if (simarray[s2 + numNodes * j])
                {
                    simarray[s1 + numNodes * j] = 1;
                    simarray[s2 + numNodes * j] = 0;
                }
                connected[s2] = 1;
            }
        }
    }
}