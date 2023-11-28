#include "graph.h"

using namespace std;

int main(){
    int n;
    cin>>n;
    
    Graph g = Graph(n);
    int a=0,b=0;
    cin>>a>>b; 

    while ((a != -1) || (b != -1)){
        bool check = g.insert_edge(a,b);
        g.edge_pair.insert(myPair(a-1,b-1));
        if (!check) cerr<<"Wrong inputs"<<endl;
        g.source[b-1] = false;
        cin>>a>>b;
    }

    cout<<"Source Nodes:";
    for (int i=0;i<n;i++){
        if (g.source[i]){
            cout<<" "<<i+1;
        }
    }
    cout<<endl;
    cout<<endl;

    cin>>a>>b; 

    while ((a != -1) || (b != -1)){
        if (!(g.source[a-1] && g.source[b-1])) cerr<<"Specified nodes are not source nodes"<<endl;
        g.similar[a-1][b-1] = true;
        g.checked[a-1][b-1] = true;
        g.queue_pair.insert(myPair(a-1,b-1));
        cin>>a>>b;
    }
    g.algo();
    cout<<endl;
    g.collapse();



}