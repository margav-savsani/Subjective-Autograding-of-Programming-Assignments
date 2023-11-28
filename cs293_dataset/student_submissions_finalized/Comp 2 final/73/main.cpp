#include "Graph.cpp"

int main(int argv,char *argc[])
{
    int num;
    cin>> num;
    DirectedGraph graph(num);
    while(true)
    {//taking edges
        int n1,n2;
        cin>>n1;
        cin>>n2;
        if (n1 == -1 && n2 == -1)
            break;
        graph.AddEdge(n1-1,n2-1);
    }
    graph.printSourcenode();
    while (true)
    {//taking similar nodes
        int n1,n2;
        cin>>n1;
        cin>>n2;
        if (n1 == -1 && n2 == -1)
            break;
        if (graph.nodes[n1-1].similar == nullptr)
        {
            graph.nodes[n1-1].similar=new listOfObjects<int>(n2-1);
        }
        else
        {
            listOfObjects<int> *sample=new listOfObjects<int> (n2-1);
            sample->next=graph.nodes[n1-1].similar;
            sample->next->prev=sample;
            graph.nodes[n1-1].similar=sample;
        }
        if (graph.nodes[n1-1].symsimilar == nullptr)
            graph.nodes[n1-1].symsimilar=new listOfObjects<int>(n2-1);
        else
        {
            listOfObjects<int> *sample=new listOfObjects<int> (n2-1);
            sample->next=graph.nodes[n1-1].symsimilar;
            sample->next->prev=sample;
            graph.nodes[n1-1].symsimilar=sample;
        }
        if (graph.nodes[n2-1].symsimilar == nullptr)
            graph.nodes[n2-1].symsimilar=new listOfObjects<int>(n1-1);
        else
        {
            listOfObjects<int> *sample=new listOfObjects<int> (n1-1);
            sample->next=graph.nodes[n2-1].symsimilar;
            sample->next->prev=sample;
            graph.nodes[n2-1].symsimilar=sample;
        }
        graph.similar[n1-1][n2-1]=true;
    }
    graph.SimilarNode();
    graph.printsimlarpairs();
    graph.printclasses();
    graph.printclasses();
}
//by saran 210050036