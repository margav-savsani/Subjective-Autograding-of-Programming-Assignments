#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif

#ifndef GRAPH_CPP
#include "Graph.cpp"
#endif

int main(){
    Graph graph;
    graph.makeGraph();
    graph.sourceNodes();
    // graph.sinkNodes();
    // graph.allNodes();
    graph.similarNodes();
    // graph.printSimilarity();
    graph.collapse();
}