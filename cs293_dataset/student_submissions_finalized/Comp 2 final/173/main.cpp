#include "Graph.h"

int main () {
    directedGraph *g = new directedGraph("outgraph.txt");
    //cout << "Source Nodes: ";
    g->sourceNode();
    //cout << endl;

    g->calculateSim();
    //cout << "Similar Node Pairs: ";
    g->printSim();
    //cout << endl;

    g->DFS();
    //cout << "Collapsed graph:"<<"\n\n";
    g->collapsedGraph();
}