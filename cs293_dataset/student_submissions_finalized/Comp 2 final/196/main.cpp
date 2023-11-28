//Main File
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;
#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

//Main
int main(){
    //Graph
    Graph* myGraph;
    //Taking number of nodes as input
    int numNodes;
    cin>>numNodes;
    //Creating graph with the number of nodes
    myGraph = new Graph(numNodes);
    if (myGraph == nullptr) {
        cerr << "Memory allocation failure." << endl;
        exit(-1);
    }
    //Taking input for edges
    //Exited if the input is -1 -1
    while(true){
        int sourcenode;
        int targetnode;
        cin>>sourcenode;
        cin>>targetnode;
        if(sourcenode==-1 && targetnode==-1){
            break;
        }
        //Adding the edge to the graph
        myGraph->addDirectedEdge(sourcenode,targetnode);
    }
    //Taking input for user defined similar node pair
    //Exiting when input is -1 -1
    while(true){
        int node1;
        int node2;
        cin>>node1;
        cin>>node2;
        if(node1==-1 && node2==-1) break;
        //Adding the similar node pair
        myGraph->addSimilar(node1,node2);
    }
    //Printing the source nodes
    myGraph->printSourceNodes();
    //Constructing all similar node pairs
    myGraph->constructSimilar();
    //Printing all similar node pairs
    myGraph->printSimilarNodes();
    //Collapsing and print the new graph based on similar nodes list
    myGraph->CollapseGraph();
    return 0;
}

// End Of Code :-)