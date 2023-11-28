#include "std_headers.h"
using namespace std;

#include "acylicgraph.cpp"

int main()
{
  
    int count = 0;
   
    int num1;
    cin >> num1;


    ADG DirectedGraph(num1);
    int num = num1;
    //TO check for source nodes
    for (int i = 0; i < num; i++)
    {
        DirectedGraph.issource[i] = false;
    }
    int node1;
    int node2;
    //Adding the nodes to the graph
    while (true)
    {
        cin >> node1;
        cin >> node2;
        if (node1 != -1)
        {

            
            DirectedGraph.issource[node2 - 1] = true;
            DirectedGraph.createedge(node1, node2);
        }
        else
        {
            break;
        }
    }

    
    int n1;
    int n2;

    // Adding the similarity relation to the graph
    while (true)
    {
        cin>>n1;
        cin>>n2;

       
        if (n1!=-1)
        {
           

            DirectedGraph.addsimilar(n1, n2);
        }
        else
        {
            break;
        }
    }
    // Creates new similarity relation based on the points given in the question
    DirectedGraph.checksimilar();

    // Collapse the graph using symmetric and transistive closure
    DirectedGraph.collapse();

    // Print all the data according to the specification given in the question
    DirectedGraph.printsimilar();
}