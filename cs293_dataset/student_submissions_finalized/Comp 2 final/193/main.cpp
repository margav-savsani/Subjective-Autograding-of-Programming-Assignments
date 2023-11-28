#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
#include "Graph.cpp"

int main(int argc, char **argv)
{
    Graph *myGraph;
    int numNodes;
    int numEdges;
    int readvar1;
    int readvar2;
    cin >> numNodes;
    myGraph = new Graph(numNodes, "outgraph.txt");
    while (true)
    {
        cin >> readvar1;
        cin >> readvar2;

        if (readvar1 == -1 || readvar2 == -1)
        {
            break;
        }
        myGraph->insertEdge(readvar1, readvar2);
    }
    while (true)
    {
        cin >> readvar1;
        cin >> readvar2;

        if (readvar1 == -1 || readvar2 == -1)
        {
            break;
        }
        myGraph->addsourcerelations(readvar1, readvar2);
    }

    if (myGraph == nullptr)
    {
        cerr << "Memory allocation failure." << endl;
        exit(-1);
    }
    myGraph->listSourceNodes();
    myGraph->Find_recursive_Relation(myGraph->Relations, myGraph->visited);
    myGraph->add_edge_relations(myGraph->Relations);
    myGraph->printResults();
    return 0;
}
