#include "std_headers.h"

#include "Graph.cpp"

int main()
{
    Graph myGraph;

    std::ofstream f("outgraph.txt");

    f << "Source nodes: ";
    for (int k : myGraph.source())
        f << k << ' ';
   
    f << "\n\nSimilar node pairs: ";
    for (Pair<int> p : myGraph.similar_pairs())
        f << '(' << p.v1 << ", " << p.v2 << ") ";
    
    f << "\n\nCollapsed graph:\n\n";
    myGraph.collapse_similarity(f);
    
    f.close();

    return 0;
}
