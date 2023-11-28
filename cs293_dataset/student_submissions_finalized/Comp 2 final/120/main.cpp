#include <iostream>
#include <fstream>
#include "similar.cpp"

using namespace std;

int main(){
    int t =0;
    int numNodes,word1,word2;
    cin>>numNodes;//numNodes as input
    Graph g(numNodes);
    while(t!=2){
        cin >> word1 >> word2;//Taking input from file
        if(word1 == -1 && word2 == -1){//stops when word1 and word2 are -1
            t++;
            continue;
        }
        else if(t==0){
            g.addedge(word1,word2);//adding edge in the graph
        }
        else if(t==1){
            g.addsimilar(word1,word2);//adding similar nodes in similarity matrix
        }
    }
    g.updatesimilar();//updating similar nodes 
    g.printsource();//printing source nodes and similar nodes in the graph
    g.collapse();//collapsing the graph
}