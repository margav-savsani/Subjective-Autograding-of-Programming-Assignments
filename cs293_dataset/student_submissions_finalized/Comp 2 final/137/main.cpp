#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_CPP
#include "graph.cpp"
#endif

int main()
{
    freopen ("outgraph.txt", "w", stdout);
    Graph *myGraph;
    myGraph = new Graph();
    myGraph->similarInput();
    myGraph->sourceNodes();
    cout<<endl;
    myGraph->computeSimilar();
    myGraph->printSimilar();
    cout<<endl;
    myGraph->collapsedNodes();
    myGraph->printCollapsedEdges();
    myGraph->printEqClass();
}