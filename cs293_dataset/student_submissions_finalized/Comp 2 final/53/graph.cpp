#include "graph.h"

void Graph::print_sources(){
    for(int i=0;i<numNodes;i++){
        if(nodes[i].incoming_adj == nullptr) cout << i+1 << " ";
    }
    cout << endl;
}