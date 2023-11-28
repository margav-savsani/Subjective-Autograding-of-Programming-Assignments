#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif
#include <fstream>

int main(int argc, char **argv)
{
    Graph *myGraph;
    int numNodes;
    cin >> numNodes;
    myGraph = new Graph(numNodes, "outgraph.txt");
    if (myGraph == nullptr)
    {
        cerr << "Memory allocation failure." << endl;
        exit(-1);
    }
    // fstream for writing in outgraph.txt
    fstream WritingFile;
    WritingFile.open("outgraph.txt", ios::out);
    if (!WritingFile.is_open())
    {
        cerr << "Couldn't open graph file "
             << "outgraph.txt"
             << " Aborting ..." << endl;
        exit(-1);
    }
    // printing source nodes:
    myGraph->printSourceNodes(WritingFile);
    // printing similar node pairs:
    myGraph->printSimilarNodes(WritingFile);

    CollapsedGraph *Collapsedgraph = new CollapsedGraph(myGraph);
    // printing Collapsed Graph by using DFS
    Collapsedgraph->MainDFS(WritingFile);

    WritingFile.close();
    // myGraph->modifiedDFS();
    // myGraph->printResults();

    return 0;
}
