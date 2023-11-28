#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

using namespace std;

int main(int argc, char *argv[]){
    Graph g;
    g.getSourceNodes();
    g.computeSimilarity();
    g.printSimilar();
    g.collapse();
}