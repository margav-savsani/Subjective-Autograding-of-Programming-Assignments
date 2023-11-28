#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


#include "graph.cpp"


int main(int argc, char **argv)
{
    Graph* g;
    int n;
    cin>>n;
    g= new Graph(n);
    while(true){
        int p,q;
        cin>>p; cin>>q;
        if(p==-1) break;
        if(p<=n && q<=n){
            g->addedge(p,q);
        }
    }
    g->printsource();
    g->outfile<<"Similar node pairs: ";
    while(true){
        int p,q;
        cin>>p; cin>>q;
        if(p==-1) break;
        if(p<=n && q<=n){
            g->similar(p,q);
        }
    }
    
    g->findsimilar();
    g->collapsedgraph();
}
