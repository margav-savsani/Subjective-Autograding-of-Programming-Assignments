#include<iostream>
#include <fstream>
#include "graph.h"
using namespace std;

int main(int argc,char* argv[]){
    if(argc != 2) exit(-1);
    ifstream graphfile;
    graphfile.open(argv[1]);
    int numNodes;
    graphfile>>numNodes;
    graph g(numNodes);
    while(true){
        int n1,n2;
        graphfile>>n1>>n2;
        if(n1 == -1) break;
        g.add_edge(n1,n2);
    }
    g.print_sources();
    while(true){
        int n1,n2;
        graphfile>>n1>>n2;
        if(n1 == -1) break;
        g.similar_nodes(n1,n2);
    }
    g.find_similar_nodes(); 
    g.print_similar_nodes();
    g.collapse();
    graphfile.close();
}
