#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "graph.cpp"
#endif

int main(int argc,char **argv){
    Graph *mygraph;
    int numNodes;
    string file="outgraph.txt";//creates a file output.txt
    cin>>numNodes;
    mygraph=new Graph(numNodes,file);

    while(true){ //this loop takes in all the adjacent nodes 
        int a,b;
        cin>>a>>b;
        if(a==-1 && b==-1)break;
        mygraph->make_edge(a,b); 
    }

    while(true){ //these are the user defined similiar nodes
        int a,b;
        cin>>a>>b;
        if(a==-1 && b==-1)break;
        mygraph->similiar(a,b);
    }
    mygraph->findsim();
    mygraph->printresults();
    return 0;
}