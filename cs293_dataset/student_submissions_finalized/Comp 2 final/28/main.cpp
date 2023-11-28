#include "graph.cpp"
#include <fstream>

int main()
{
    int n;
    cin >> n;
    Graph a(n);
    //ofstream MyFile("outgraph.txt");
    a.getsimilarity();
    a.printsource();
    
}