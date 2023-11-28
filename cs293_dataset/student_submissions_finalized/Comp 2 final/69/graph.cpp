#ifndef GRAPH_CPP
#define GRAPH_CPP

#ifndef GRAPH_H
#include "graph.h"
#endif

#ifndef HEADERS_H
#include "headers.h"
#endif

using namespace std;

Pair::Pair(Node *n1, Node *n2)
{
    n1 = node1;
    n2 = node2;
}

Node::Node()
{
    value = in = out = 0;
}

Graph::Graph(int n)
    {
        numPairs = 0;
        numNodes = n;
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
    }

void Graph::update_adjs(int i, int j)
    {
        nodes[i].adj1.push_back(&nodes[j]);
        nodes[j].adj2.push_back(&nodes[i]);
        nodes[i].out++;
        nodes[j].in++;
    }

list<Node *> Graph::source_nodes()
    {
        list<Node *> p;
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].in == 0)
            {
                p.push_back(&nodes[i]);
            }
        }
        return p;
    }

list<Node *> Graph:: sink_nodes()
    {
        list<Node *> p;
        for (int i = 0; i < numNodes; i++)
        {
            if (nodes[i].out == 0)
            {
                p.push_back(&nodes[i]);
            }
        }
        return p;
    }

bool Graph:: source(int n)
    {
        if (nodes[n].in == 0)
        {
            return true;
        }
        return false;
    }

bool Graph::sink(int n)
    {
        if (nodes[n].out == 0)
        {
            return true;
        }
        return false;
    }

bool Graph::edge(int n1, int n2)
    {
        list<Node *> p = nodes[n1].adj1;
        while (p.front() != nullptr)
        {
            if (p.front() == &nodes[n2])
            {
                return true;
            }
            p.pop_front();
        }
        return false;
    }

bool Graph:: is_sim_pair(int n1, int n2)
    {
        list<Pair *> p = pairs;
        while (p.front() != nullptr)
        {
            if (p.front()->node1 == &nodes[n1] && p.front()->node2 == &nodes[n2])
            {
                return true;
            }
            p.pop_front();
        }
        return false;
    }

bool Graph:: is_second_case(int n1, int n2)
    {
        bool k;
        int v1 = 0;
        int v2 = nodes[n1].in + nodes[n2].out;
        list<Node *> p1 = nodes[n1].adj1;
        list<Node *> p2 = nodes[n1].adj2;
        while (p1.front() != nullptr)
        {
            list<Node *> q1 = nodes[n2].adj1;
            list<Node *> q2 = nodes[n2].adj2;
            while (q1.front() != nullptr)
            {
                if (is_sim_pair(p1.front()->value - 1, q1.front()->value - 1))
                {
                    v1++;
                }
                q1.pop_front();
            }
            while (q2.front() != nullptr)
            {
                if (is_sim_pair(p1.front()->value - 1, q2.front()->value - 1))
                {
                    v1++;
                }
                q2.pop_front();
            }
            p1.pop_front();
        }
        while (p2.front() != nullptr)
        {
            list<Node *> q1 = nodes[n2].adj1;
            list<Node *> q2 = nodes[n2].adj2;
            while (q1.front() != nullptr)
            {
                if (is_sim_pair(p2.front()->value - 1, q1.front()->value - 1))
                {
                    v1++;
                }
                q1.pop_front();
            }
            while (q2.front() != nullptr)
            {
                if (is_sim_pair(p2.front()->value - 1, q2.front()->value - 1))
                {
                    v1++;
                }
                q2.pop_front();
            }
            p2.pop_front();
        }
        if (v1 == v2)
        {
            k = true;
        }
        else
        {
            k = false;
        }
        return k;
    }

list<Pair *> Graph:: similarity(int n1, int n2)
    {
        if (!is_sim_pair(n1, n2))
        {

            // case 1
            if (nodes[n1].in == 0 && nodes[n2].in == 0 && is_sim_pair(n1, n2))
            {
                pairs.push_back(&Pair(&nodes[n1], &nodes[n2]));
                pairs.push_back(&Pair(&nodes[n2], &nodes[n1]));
                numPairs++;
            }
            // case 2
            if (is_second_case(n1, n2))
            {
                pairs.push_back(&Pair(&nodes[n1], &nodes[n2]));
                pairs.push_back(&Pair(&nodes[n2], &nodes[n1]));
                numPairs++;
            }
            // case 3
            if (nodes[n1].in == 1 && edge(n2, n1))
            {
                pairs.push_back(&Pair(&nodes[n1], &nodes[n2]));
                pairs.push_back(&Pair(&nodes[n2], &nodes[n1]));
                numPairs++;
            }
        }
    }

void Graph::sim_pairs(int i, int j)
    {
        pairs.push_back(&Pair(&nodes[i], &nodes[j]));
        pairs.push_back(&Pair(&nodes[j], &nodes[i]));
        numPairs++;
    }

void printResult(string gfile)
    {
        fstream graphfile;
        graphfile.open(gfile, ios::out);

        graphfile << "Source nodes: ";
        list<Node *> p = source_nodes();
        while (p.front() != nullptr)
        {
            graphfile << p.front()->value;
            p.pop_front();
        }
        graphfile << endl;

        graphfile << "Similar node pairs: ";
        list<Pair *> q = pairs;
        while (q.front() != nullptr)
        {
            graphfile << "(" << q.front()->node1->value << ", " << q.front()->node2->value << ") ";
            q.pop_front();
        }
        graphfile << endl;

        graphfile << "Collapsed graph:";
    }




#endif