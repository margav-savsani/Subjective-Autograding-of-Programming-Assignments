#include "stdHeaders.h"
#include "graph.cpp"

int main(int argc, char *argv[])
{
    Graph g("outgraph.txt");
    g.printSources();
    g.similarityC();
    g.similarityB();
    g.printRelated();
    g.collapse();
    g.printCollapse();
}