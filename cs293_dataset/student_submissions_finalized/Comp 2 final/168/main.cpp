#include <iostream>
#include "Graph.cpp"
using namespace std;

int main(){
    //changing stdout to the file
    freopen ("outgraph.txt", "w", stdout);
    int numNodes;
    cin>>numNodes;
    //creating the graph, the constructor of which will handle all of our work
    Graph* dag = new Graph(numNodes,"out.txt");
}