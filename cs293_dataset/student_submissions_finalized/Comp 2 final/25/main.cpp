#include <iostream>
#include "Graph.cpp"
using namespace std;

int main(){
    int n; cin>>n;
    DAG mygraph(n);
    mygraph.printSource();
    mygraph.similarPairs();
    mygraph.equivalance_class();
}