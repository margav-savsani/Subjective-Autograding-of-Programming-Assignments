#include "Graph.cpp"

int main(){
    
    Graph* test_graph = new Graph("graphFile.txt");
    std::cout << "Source nodes: " << test_graph -> get_source_nodes() << "\n";
    std::cout << "Similar node pairs: " << test_graph -> get_similar_nodes() << "\n\n";
    std::cout << test_graph -> nodes.get_size() << ": " << test_graph -> get_nodes() << "\n";
}