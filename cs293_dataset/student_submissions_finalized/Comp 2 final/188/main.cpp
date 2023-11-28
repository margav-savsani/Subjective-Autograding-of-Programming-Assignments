#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif
int main(int argc, char *argv[])
{
    int numNodes;
    cin >> numNodes;
    Graph *g = new Graph(numNodes);
    g->printSourceNodes();
    g->updateSimilarity();
    g->printSimilarNodes();
    g->printCollapsedGraph();
}
