#ifndef GRAPH_H
#include "graph.h"
#endif

int main()
{
    Graph g("outgraph.txt");            // Creates graph
    g.getSourceNodes(); // Identifies and prints Source Nodes
    g.similarity();     // Identifies and prints similarity relations
    g.collapseGraph();  // Collapses graphs and prints
}
