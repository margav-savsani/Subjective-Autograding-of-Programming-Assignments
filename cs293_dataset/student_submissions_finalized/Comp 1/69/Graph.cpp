#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::DFS(Node *node)
{
    node->visit++;
    trees->insert(node->value);
    list<Node *> t = node->adj;
    while (t.front() != nullptr)
    {
        if (t.front()->visit < 2)
        {
            DFS(t.front());
        }
        t.pop_front();
    }
}

void Graph::printResults()
{
    cout << "No. of connected components:" << numComp() << endl; 
    cout << "No. of nodes visited once:" << numSingle() << endl;
    cout << "No. of nodes visited twice:" << numDouble() << endl;
    cout << "No. of nodes that are present in a cycle:" << numCycle() << endl;
    printTrees();
}

string Graph::numSingle()
{
    int countd = 0;
    string s = "(";
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].visit == 1)
        {
            countd++;
            s.append(to_string(nodes[i].value));
            s.append(",");
        }
    }
    s.pop_back();
    s.append(")");
    string d = to_string(countd);
    d.append(" ");
    d.append(s);
    return d;
}

string Graph::numDouble()
{
    int countd = 0;
    string s = "(";
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].visit == 2)
        {
            countd++;
            s.append(to_string(nodes[i].value));
            s.append(",");
        }
    }
    s.pop_back();
    s.append(")");
    string d = to_string(countd);
    d.append(" ");
    d.append(s);
    return d;
}


int Graph::numComp()
{
    return comp;
}

void Graph::modifiedDFS()
{
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].visit == 0)
        {
            comp++;
            DFS(&nodes[i]);
        }
    }
}

int Graph::numCycle()
{
    return 0;
}

void Graph::printTrees()
{
    BST *T = trees;
    // while (T != nullptr)
    // {
    //     T->printBST("");
    //     cout << endl;
    // }
    T->printBST("");
}

#endif