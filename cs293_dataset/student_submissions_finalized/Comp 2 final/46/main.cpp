#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_CPP
#include "Graph.cpp"
#endif

int *SplitStr(string str) { // function to obtain the input values from the file
    static int arr[2];
    int i=0;
    string s = "";

    for (auto x: str) {
        if(x == '-'){ // negative values i.e, -1
            arr[0] = -1;
            arr[1] = -1;
            return arr;
        }
        if (x == ' ') { // seperated by space
            arr[i]=(stoi(s));
            i++;
            s = "";
        }
        else { // appending to string
            s = s + x;
        }
    }
    arr[i]=(stoi(s));
    i++;
    return arr; // returning the values of nodes
}

int main(int argc, char **argv){

    string c;
    getline(cin,c);
    const int numOfNodes = stoi(c);

    // creating dynamic matrices
    int **adj_mat = new int*[numOfNodes];
    int **sim_mat = new int*[numOfNodes];
    int **new_sim = new int*[numOfNodes];
    bool *arr = new bool[numOfNodes];
    // initialising the matrices
    for(int i=0;i<numOfNodes;i++){
        arr[i] = 0;
        adj_mat[i] = new int[numOfNodes];
        sim_mat[i] = new int[numOfNodes];
        new_sim[i] = new int[numOfNodes];
        //initialisation
        for(int j=0;j<numOfNodes;j++){
            adj_mat[i][j] = 0;
            sim_mat[i][j] = 0;
            new_sim[i][j] = 0;
        }
    }
    
    // taking input from the file

    while(getline(cin,c)){ // reading as lines
        int *ar = SplitStr(c);
        if(ar[0]==-1) break;
        adj_mat[ar[0]-1][ar[1]-1] = 1;
        arr[ar[1]-1]=1;
    }
    while(getline(cin,c)){
        int *arr = SplitStr(c);
        if(arr[0]==-1) break;
        sim_mat[arr[0]-1][arr[1]-1] = 1;
    }

    // initialising the graph
    Graph graph(numOfNodes,adj_mat,sim_mat,new_sim,arr);
    graph.source();
    graph.similar();
    graph.collapse();
    f_out.close();
}