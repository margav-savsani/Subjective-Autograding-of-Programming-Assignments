#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "graph.h"
#endif

#include "graph.h"

int main(int argc, char **argv){
        ofstream f("outgraph.txt");
        graph *myGraph;
        myGraph = new graph();
        myGraph->printsources(f);
        myGraph->similaredges();
        myGraph->printer(f);
}


