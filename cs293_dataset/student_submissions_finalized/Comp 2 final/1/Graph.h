#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

//used as a graph node
struct Node{
    int val;
    int in_degree;
    int out_degree;
    //for DFS
    int arrTime = 0;
    int depTime = 0;
    //list of parent node values
    int *parents;
    //for DFS
    bool visited = false;
    //CONSTRUCTOR
    Node(int a = 0, int b = 0, int c = 0){
        val = a;
        in_degree = b;
        out_degree = c;
    }
    //make list of parents using adjacency
    void add_parents(bool **adjacency, int numNodes){
        parents = new int[in_degree]; //#parents = in-degree
        int fill = 0;
        for(int i = 0; i < numNodes; i++){
            if(adjacency[i][val - 1]){
                parents[fill] = i + 1;
                fill++;
            }
        }
    }
};

struct Graph{
    int numNodes;
    Node *nodes;
    //2d array for adjacency
    bool **adjacency;
    Graph(int a){
        numNodes = a;
        nodes = new Node[numNodes];
        for(int i = 0; i < numNodes; i++){
            nodes[i].val = i + 1; //set values
        }
        adjacency = new bool *[numNodes];
        for(int i = 0; i < numNodes; i++){
            adjacency[i] = new bool[numNodes];
        }
    }
    //adding an edge to the graph
    void add_edge(int start, int end){
        //change degrees
        nodes[start - 1].out_degree++;
        nodes[end - 1].in_degree++;
        //update adjacency
        adjacency[start - 1][end - 1] = true;
    }
};

//visit of a DFS on a node
void DFS_node(Graph &G, int node){
    static int time = 0;
    G.nodes[node].visited = true;
    time++;
    //set arrival time
    G.nodes[node].arrTime = time;
    //call recursively on non-visited children
    for(int i = 0; i < G.numNodes; i++){
        if(G.adjacency[node][i] == true && !G.nodes[i].visited){
            DFS_node(G, i);
        }
    }
    time++;
    //set departure time
    G.nodes[node].depTime = time;
}
//for the entire graph
//call on unvisited nodes, in order
void DFS_graph(Graph &G){
    for(int i = 0; i < G.numNodes; i++){
        if(!G.nodes[i].visited){
            DFS_node(G, i);
        }
    }
}

//arranges nodes in decreasing order of departure times
//so that all the parents of each node are strictly before it
int *topological_sort(Graph &G){
    int *temp = new int[2 * G.numNodes];
    for(int i = 0; i < 2 * G.numNodes; i++){
        temp[i] = -1;
    }
    for(int i = 0; i < G.numNodes; i++){
        temp[G.nodes[i].depTime - 1] = i + 1;
    }
    int *to_return = new int[G.numNodes];
    int fill = 0;
    for(int i = 2 * G.numNodes - 1; i >= 0; i--){
        if(temp[i] != -1){
            to_return[fill] = temp[i];
            fill++;
        }
    }
    return to_return;
}