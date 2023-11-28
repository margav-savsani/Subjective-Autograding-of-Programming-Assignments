#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv)
{
    int numNodes;
    cin>>numNodes;

    Graph *myGraph = new Graph(numNodes, "outgraph.txt");

    myGraph->read_graph();

    myGraph->print_sources();

    myGraph->read_similar();

    myGraph->calc_similar();

    myGraph->print_similar();

    myGraph->collapse();

    myGraph->print_collapsed();

    delete myGraph;

    return 0;
}
