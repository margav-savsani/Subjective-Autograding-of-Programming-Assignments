#ifndef STD_HEADERS
#include "stdheaders.h"
#endif

#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    string outputFileName = "outputgraph.txt";
    int numNodes;
    cin >> numNodes;
    Graph mygraph(numNodes, outputFileName);
    mygraph.calcSimPairs();
    mygraph.closurefunc();

    mygraph.printSimilar();
}