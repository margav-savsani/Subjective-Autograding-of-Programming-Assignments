#include<iostream>
#include<fstream>
#include<string>
#include "graph.cpp"
using namespace std;


int main(){
    // reads no.of nodes
    int num;
    cin>>num;

    //intialize a array which checks if node is sourcenode 
    bool *source_arr;
    source_arr = new bool[num];
    for(int i=0;i<num;i++){
        source_arr[i] = true;   //intialize all to true
    }

    //intialize a 2d array which checks 2 nodes are adjacent
    bool **edge_arr;
    edge_arr = new bool*[num];
    for(int i=0;i<num;i++){
        edge_arr[i] = new bool[num];
        for(int j=0;j<num;j++){
            edge_arr[i][j]=false;//intialize all to false
        }
    }

    //intialize a 2d array which checks 2 nodes are similar
    bool **sim_arr;
    sim_arr = new bool*[num];
    for(int i=0;i<num;i++){
        sim_arr[i] = new bool[num];
        for(int j=0;j<num;j++){
            sim_arr[i][j]=false;//intialize all to false
        }
    }

    // reads edges
    int x,y;
    cin>>x>>y;
    while(x!=-1 and y!=-1){
        edge_arr[x-1][y-1]=true;//update adjacencymatrix
        source_arr[y-1]=false; // checks if a node is source node or not in *O(n) time*.
        cin>>x>>y;
    }
    //reads similar nodes from user input
    cin>>x>>y;
    while(x!=-1 and y!=-1){
        sim_arr[x-1][y-1]=true;//update 2d matrix of similar nodes
        cin>>x>>y;
    }

    graph g(num,edge_arr,sim_arr,source_arr);
    g.print_source_nodes();
    fout<<endl;
    g.update_similar_nodes();
    g.print_similar_nodes();
    fout<<endl;
    g.collapse();
    fout.close();
}
