#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv)
{
	Graph *myGraph;

	// string graphFileName = argv[1];

	myGraph = new Graph("outGraph.txt");
	if (myGraph == nullptr)
	{
		cerr << "Memory allocation failure." << endl;
		exit(-1);
	}

	int *srcNodes = myGraph->getSourceNodes();
	int numNodes = myGraph->getNumNodes();
	myGraph->graphFile << "Source nodes: ";
	for (int i = 0; i < myGraph->numSrcNodes; i++)
	{
		myGraph->graphFile << srcNodes[i] << " ";
	}
	myGraph->graphFile << endl << endl;
	// myGraph->printResults();
	myGraph->fillSimilarNodes(srcNodes);
	myGraph->printResults();
	myGraph->collapseSimilarNodes();

	return 0;
}
