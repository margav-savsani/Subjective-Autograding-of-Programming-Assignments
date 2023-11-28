#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.h"
#endif

int main() {
    int numNodes;
    cin >> numNodes;     // take number of notes
    Graph G(numNodes);   // create graph
    G.takeInput();       // take input from user
    G.printSource();
    G.printSimilar();  // print similar nodes
    G.Collapse();        // print Collapsed graph
    return 0;
}
