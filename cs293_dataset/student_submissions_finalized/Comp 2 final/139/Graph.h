#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <list>
#include <vector>
#include <algorithm>

class Node
{
public:
    int value;
    vector<Node *> incoming, outgoing, adjacent;
    bool isvisit;
    Node() { isvisit = false; }
    Node(int value)
    {
        this->value = value;
        isvisit = false;
    }
};

class DirectedEdge
{
public:
    Node *source, *sink;
    DirectedEdge(Node *source, Node *sink)
    {
        this->source = source;
        this->sink = sink;
    }
};

class Graph
{
    Node *Nodes;
    list<Node *> SourceNodes;
    list<DirectedEdge *> SimilarNodes;

public:
    vector<vector<int>> edges;
    int numNodes;
    Graph(int nodes, string gFileName)
    {
        numNodes = nodes;
        Nodes = new Node[numNodes];
        for (int i = 0; i < numNodes; i++)
        {
            Nodes[i].value = i + 1;
            SourceNodes.push_back(&Nodes[i]);
        }
        while (true)
        {
            int from, to;
            cin >> from;
            cin >> to;
            if (from == -1 && to == -1)
                break;
            vector<int> edge;
            edge.push_back(from);
            edge.push_back(to);
            edges.push_back(edge);
            Nodes[from - 1].outgoing.push_back(&Nodes[to - 1]);
            Nodes[from - 1].adjacent.push_back(&Nodes[to - 1]);
            Nodes[to - 1].incoming.push_back(&Nodes[from - 1]);
            Nodes[to - 1].adjacent.push_back(&Nodes[from - 1]);

            for (auto const &i : SourceNodes)
            {
                if (i->value == Nodes[to - 1].value)
                {
                    SourceNodes.remove(i);
                    break;
                }
            }
        }
        while (true)
        {
            int sim1, sim2;
            cin >> sim1;
            cin >> sim2;
            if (sim1 == -1 && sim2 == -1)
                break;
            if (std::count(SourceNodes.begin(), SourceNodes.end(), &Nodes[sim1 - 1]) && std::count(SourceNodes.begin(), SourceNodes.end(), &Nodes[sim2 - 1]))
            {
                DirectedEdge *DirEdge1 = new DirectedEdge(&Nodes[sim1 - 1], &Nodes[sim2 - 1]);
                SimilarNodes.push_back(DirEdge1);
            }
        }
    }
    ~Graph()
    {
        delete[] Nodes;
    }

    void printSourceNodes(fstream &WritingFile);
    void printSimilarNodes(fstream &WritingFile);
    list<DirectedEdge *> SimilarNodess()
    {
        return SimilarNodes;
    }
    vector<vector<int>> Edges()
    {
        return edges;
    }
};
class CollapsedGraph
{
public:
    list<DirectedEdge *> NodesfromGraph;
    Node *Nodes;
    Graph *graph;
    int numNodes, connectedComponents = 0;
    vector<int> nodevalues;

    CollapsedGraph(Graph *graph)
    {
        this->graph = graph;
        this->NodesfromGraph = graph->SimilarNodess();
        numNodes = graph->numNodes;
        Nodes = new Node[numNodes];

        for (int i = 0; i < numNodes; i++)
        {
            Nodes[i].value = i + 1;
        }

        for (auto const &i : NodesfromGraph)
        {
            bool found = false, found2 = false;
            if (i->source->value == i->sink->value)
                continue;
            for (auto const &Val : Nodes[i->source->value - 1].adjacent)
            {
                if (Val->value == i->sink->value)
                {
                    found = true;
                    break;
                }
            }
            for (auto const &Val : Nodes[i->sink->value - 1].adjacent)
            {
                if (Val->value == i->source->value)
                {
                    found2 = true;
                    break;
                }
            }
            Nodes[i->source->value - 1].outgoing.push_back(&Nodes[i->sink->value - 1]);
            if (!found)
                Nodes[i->source->value - 1].adjacent.push_back(&Nodes[i->sink->value - 1]);
            Nodes[i->sink->value - 1].incoming.push_back(&Nodes[i->source->value - 1]);
            if (!found2)
                Nodes[i->sink->value - 1].adjacent.push_back(&Nodes[i->source->value - 1]);
        }
    }

    void MainDFS(fstream &WritingFile);
    void DFS(Node *node, vector<int> &vals);
};
#endif
