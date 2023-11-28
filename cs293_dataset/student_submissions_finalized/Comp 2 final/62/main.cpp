#include<iostream>
#include<fstream>
using namespace std;
ofstream file;// found out too late we had to print to file, so had to make this global to do quickly
#include"graph.cpp"

int main(){
    //init graphs
    Graph *myGraph;
    int numNodes;
    cin>> numNodes;
    myGraph = new Graph(numNodes);
    //read edges
    int from,to;
    while (1){
        cin>>from >>to;
        if (from==-1) break;
        myGraph->addEdge(from,to);
    }
    LL sources = myGraph->getSource();
    //read relations
    while (1){
        cin>>from >>to;
        if (from==-1) break;
        myGraph->addRelation(from,to);
    }
    myGraph->computeRelations();
    file.open("outgraph.txt");
    file<<"Source nodes:";
    sources.print();// print sources
    file<<"\nSimilar node pairs: ";
    myGraph->printRelations();
    myGraph->collapse();//collapse the graph, btw this breaks the graph
    file<<"\nCollapsed graph:\n";
    myGraph->print();
    file.close();
    delete myGraph;
    return 0;
}