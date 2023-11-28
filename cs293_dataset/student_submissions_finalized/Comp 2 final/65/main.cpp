#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <vector>


using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv){
    Graph *mygraph;
    int nNodes;
    int nEdges=0;
    int check;
    cin>>nNodes;
    mygraph = new Graph(nNodes);
    int a1,a2;
    while(true){      
        cin>>a1>>a2;
        if(a1==-1 || a2==-1){
            break;
        }
        mygraph->makeedge(a1,a2);
        nEdges++;
    }
    a1=0;a2=0;
    mygraph->printsource();
    while(true){
        cin>>a1>>a2;
        if(a1==-1 || a2==-1){
            break;
        }
        mygraph->makegivensimilar(a1,a2);
    }
   
    mygraph->makesimilar();
    mygraph->printsimilar();
}