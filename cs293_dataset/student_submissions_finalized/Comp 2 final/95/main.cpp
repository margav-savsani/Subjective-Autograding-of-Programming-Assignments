#include<iostream>
#include"Graph.cpp"
using namespace std;
int main(){
int num_nodes;
cin>>num_nodes;
Graph *graph=new Graph(num_nodes); 
int a=0,b;
while(a!=-1){
    cin>>a;
    cin>>b;
    graph->add_edges(a,b);
    graph->numEdges++;
}
a=0;
while (a!=-1)
{
   cin>>a>>b;
   if(graph->nodes[a-1].source_node==true&&graph->nodes[b-1].source_node==true){
    graph->nodes[a-1].similar_nodes.push_back(b);
   }
}
graph->check_similar();
graph->collapse_graph();
graph->print_results();

return 0;
}