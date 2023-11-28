#ifndef GRAPH_H
#define GRAPH_H

#ifndef HEADERS_H
#include "headers.h"
#endif

using namespace std;

class Node
{
public:
    int value;
    int in;
    int out;
    list<Node *> adj1;
    list<Node *> adj2;
    Node();
    ~Node() { ; }
};


class Pair
{
public:
    Node *node1;
    Node *node2;
    Pair(Node *n1, Node *n2);
    ~Pair()
    {
        ;
    }
};



class Graph
{
private:
    int numNodes;
    Node *nodes;
    int numPairs;
    list<Pair *> pairs;

public:
    Graph(int n);

    ~Graph()
    {
        delete[] nodes;
    }

    void update_adjs(int i, int j);

    list<Node *> source_nodes();

    list<Node *> sink_nodes();

    bool source(int n);

    bool sink(int n);

    // ->
    bool edge(int n1, int n2);

    bool is_sim_pair(int n1, int n2);

    bool is_second_case(int n1, int n2);

    list<Pair *> similarity(int n1, int n2);

    void sim_pairs(int i, int j);

    void printResult(string gfile);
};

#endif