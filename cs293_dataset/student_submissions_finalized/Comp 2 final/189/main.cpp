#include"Graph.h"

int main(){
    int N;
    cin>> N;
    Graph *g;
    g=new Graph(N);
    // for(int i =0;i<g->get_numEdges();i++){
    //     int sourceNodeValue;
    //     int destinationNodeValue;
    //     cin>> sourceNodeValue;
    //     cin>> destinationNodeValue;
    //     g->addEdge(sourceNodeValue,destinationNodeValue);
        
    //}
    while(true){
        int sourceNodeValue;
         int destinationNodeValue;
         cin>> sourceNodeValue;
         cin>> destinationNodeValue;
         if(sourceNodeValue==-1 || destinationNodeValue==-1){
            break;
         }
         else{
            g->addEdge(sourceNodeValue,destinationNodeValue);
         }
    }
    cout<<"Source nodes are: ";
    g->getSourceNodes();
    // cout<<"Sink nodes are: "<<endl;
    // g->getSinkNodes();
    // int k;
    // cin>> k;
    // printList(g->nodes[k-1].toNodes);

    // Node *n;
    // n = new Node(1);
    // Node a(3),b(4),c(5);
    // add(n->toNodes,a);
    // add(n->toNodes,b);
    // add(n->toNodes,c);
    // printList(n->toNodes);
}