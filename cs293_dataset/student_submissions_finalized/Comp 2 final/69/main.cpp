#ifndef GRAPH_CPP
#include "graph.cpp"
#endif

#ifndef HEADERS_H
#include "headers.h"
#endif
using namespace std;

int main()
{
    
    int numNodes;
    cin >> numNodes;
    Graph* g = new Graph(numNodes);


    while (true)
    {
        int node, target;
        cin >> node >> target;
        if(node == -1 && target == -1){
            break;
        }
        g->update_adjs(node-1, target-1);
    }


    while(true){
        int sim_node1, sim_node2;
        cin >> sim_node1 >> sim_node2;
        if(sim_node1 == -1 && sim_node2 == -1){
            break;
        }
        g->sim_pairs(sim_node1-1, sim_node2-1);
    }

    g->printResult("output.txt");
    
    return 0;
}