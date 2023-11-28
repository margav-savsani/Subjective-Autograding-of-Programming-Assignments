#include <iostream>
#include "Graph.cpp"
using namespace std;


int main()
{
    int n  ; 
    cin>>n ; 
    Graph graph(n);
    //intialisation of the graph 
    while (true)  { 
         int from_node , to_node ; 
         cin>>from_node>>to_node ; 
         if (from_node != -1 && to_node !=-1 )  { 
              graph.addEdge(from_node-1,to_node-1);         
         }
         else break ; 
    }
    while (true)  { 
         int from_node , to_node ; 
         cin>>from_node>>to_node ; 
         if (from_node != -1 && to_node !=-1 )  { 
              graph.similar->addSimilar(from_node-1,to_node-1) ;         
         }
         else break ; 
    }
    //find the similar nodes 
    graph.similarNodes();
    //temporary graph 
    Graph tempGraph(n) ;
    //vector to contain the maximum values  of the collapsed nodes 
    vector<int> maxCollapsed ; 
    //update the collapsed edges of the original graph (graph)
    tempGraph.collapsedGraph(&graph , &maxCollapsed ) ;
    //print the results from original graph
    graph.printResults(maxCollapsed);
}



                   