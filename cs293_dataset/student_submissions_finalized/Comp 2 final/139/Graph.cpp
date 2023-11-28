#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
#include <algorithm>
#include <fstream>
#endif

void Graph::printSourceNodes(fstream &WritingFile)
{
    WritingFile << "Source nodes:";
    for (auto const &i : SourceNodes)
    {
        WritingFile << " " << i->value;
    }
    WritingFile << endl
                << endl;
}

void Graph::printSimilarNodes(fstream &WritingFile)
{
    for (int i = 0; i < numNodes; i++)
    {
        if (Nodes[i].incoming.size() == 1)
        {
            DirectedEdge *DirEdge = new DirectedEdge(&Nodes[i], Nodes[i].incoming.at(0));
            DirectedEdge *DirEdg2 = new DirectedEdge(&Nodes[i], Nodes[i].incoming.at(0));
            SimilarNodes.push_back(DirEdge);
        }
    }
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            if (i == j)
                continue;
            if ((!std::count(SourceNodes.begin(), SourceNodes.end(), &Nodes[i])) && (!std::count(SourceNodes.begin(), SourceNodes.end(), &Nodes[j])))
            {
                vector<bool> check1;
                vector<bool> check2;
                for (auto const &K : Nodes[i].incoming)
                {
                    for (auto const &L : Nodes[j].incoming)
                    {
                        for (auto const &Sim : SimilarNodes)
                        {
                            if (Sim->source->value == K->value && Sim->sink->value == L->value)
                            {
                                check1.push_back(true);
                            }
                            else
                            {
                                check1.push_back(false);
                            }
                        }
                    }
                }
                for (auto const &K : Nodes[j].incoming)
                {
                    for (auto const &L : Nodes[i].incoming)
                    {
                        for (auto const &Sim : SimilarNodes)
                        {
                            if (Sim->source->value == K->value && Sim->sink->value == L->value)
                            {
                                check2.push_back(true);
                            }
                            else
                            {
                                check2.push_back(false);
                            }
                        }
                    }
                }
                int count1 = 0;
                int count2 = 0;
                for (int k = 0; k < check1.size(); k++)
                {
                    if (check1[k])
                    {
                        count1++;
                    }
                }
                for (int k = 0; k < check2.size(); k++)
                {
                    if (check2[k])
                    {
                        count2++;
                    }
                }
                if (count1 >= Nodes[i].incoming.size() && count2 >= Nodes[j].incoming.size())
                {
                    DirectedEdge *DirEdge = new DirectedEdge(&Nodes[i], &Nodes[j]);
                    bool found = false;
                    for (auto const &h : SimilarNodes)
                    {
                        if (h->source->value == DirEdge->source->value && h->sink->value == DirEdge->sink->value)
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        SimilarNodes.push_back(DirEdge);
                    }
                    bool b = false;
                    for (auto const &h : SimilarNodes)
                    {
                        if (h->sink->value == DirEdge->source->value && h->source->value == DirEdge->sink->value)
                        {
                            b = true;
                            break;
                        }
                    }
                    if (!b)
                    {
                        SimilarNodes.push_back(new DirectedEdge(&Nodes[j], &Nodes[i]));
                    }
                }
            }
        }
    }
    WritingFile << "Similar node pairs:";
    for (auto const &i : SimilarNodes)
    {
        WritingFile << " (" << i->source->value << ", " << i->sink->value << ")";
    }
    WritingFile << endl;
    WritingFile << endl;
}

void CollapsedGraph::DFS(Node *node, vector<int> &vals)
{
    vals.push_back(node->value);
    node->isvisit = true;
    for (auto const &i : node->adjacent)
    {
        if (!i->isvisit)
        {
            DFS(i, vals);
        }
    }
}
int Find(vector<vector<int>> Vals, int number)
{
    for (auto v : Vals)
    {
        if (std::count(v.begin(), v.end(), number))
        {
            int max = -1;
            for (auto j : v)
            {
                if (max < j)
                    max = j;
            }
            return max;
        }
    }
    return -1;
}
void CollapsedGraph::MainDFS(fstream &WritingFile)
{
    vector<vector<int>> Values;
    for (int i = 0; i < numNodes; i++)
    {
        if (!Nodes[i].isvisit)
        {
            vector<int> vals;
            connectedComponents++;
            DFS(&Nodes[i], vals);
            Values.push_back(vals);
        }
    }
    vector<int> maxs;
    for (auto const &i : Values)
    {
        int max = -1;
        for (auto const &j : i)
        {
            if (max < j)
            {
                max = j;
            }
        }
        maxs.push_back(max);
    }
    WritingFile << "Collapsed graph:" << endl
                << endl
                << connectedComponents << ":";
    sort(maxs.begin(), maxs.end());
    for (auto const &i : maxs)
    {
        WritingFile << " " << i;
    }
    WritingFile << endl;
    vector<vector<int>> compressedEdges;
    for (auto const &i : graph->edges)
    {
        int node1 = Find(Values, i.at(0));
        int node2 = Find(Values, i.at(1));
        if (node1 != node2)
        {
            bool found = false;
            for (auto o : compressedEdges)
            {
                if (o.at(0) == node1 && o.at(1) == node2)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                vector<int> compressedEdge;
                compressedEdge.push_back(node1);
                compressedEdge.push_back(node2);
                compressedEdges.push_back(compressedEdge);
                WritingFile << node1 << " " << node2 << endl;
            }
        }
    }
}