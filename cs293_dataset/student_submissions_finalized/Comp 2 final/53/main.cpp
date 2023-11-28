#include "graph.cpp"

int main(){
    int numNodes;
    cin >> numNodes;
    Graph g(numNodes);
    g.print_sources();
}