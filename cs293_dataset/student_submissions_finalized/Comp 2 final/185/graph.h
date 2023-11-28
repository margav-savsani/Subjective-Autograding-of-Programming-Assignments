//#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;


class adj_list{  //class of adjacency list for storing incoming and outgoing edges 
    public:
    int node_no; //stores the node number
    adj_list *prev;  //pointer to the prev and the next adj_list
    adj_list *next;

    adj_list(int num){ //constructor
        node_no = num;
        prev = nullptr;
        next = nullptr;
    }
 };

class Node{  //class for the nodes of the graph
    public:
    int value;  //node number
    adj_list *incoming_list;  //adjacency list of the incoming edged to the node
    adj_list *outgoing_list;  //adjacency list of the outgoing edged to the node

    Node(){  //constructor
        value = 0;
        incoming_list = nullptr;
        outgoing_list = nullptr;
    }
};

class Graph{  
    int numVertices;   //total number of nodes/verties in the graph
    Node *nodes;  //array of nodes
    public:
    int count = -1000;  //to count total number of components of the given graph but undirected
    int *arr;
    int *src_nodes;  //array to store 0 and 1. 0 if the node is a source node, 1 if the node is not a source node
    int similar_nodes[100][100];  //2D array. similar_nodes[i][j] = 1 if i and j are similar nodes and 0 otherwise.
    int *final;  //stores nodes present in the collapsed graph
    int *maxx;  
    Graph(string graphfile){

        fstream input;
        input.open(graphfile, ios::in);
        int temp;
        stringstream numbers;

        int ext = 0;
        int src = 0, dest = 0;

        input >> temp;  //reading input from graphFile
        numVertices = temp;
        src_nodes = new int[numVertices];
        arr = new int[numVertices+1];

        for(int k=0; k<=numVertices; k++){
            arr[k] = 0;
        }
        for(int k=0; k<numVertices; k++){
            src_nodes[k] = 0;
        }
        for(int k=0; k<100; k++){
            for(int l=0; l<100; l++){
            similar_nodes[k][l] = 0;
            }
        }

        nodes = new Node[numVertices];

        while(!input.eof()){
            input >> src >> dest;
            if(src == -1 && dest == -1){  
                if(ext == 0){
                    ext = 1;
                }
                else if(ext == 1){  //indicates end of file
                    ext = 2;
                    break;
                }
            }
            else if(ext == 1){  //start reading similar nodes
                similar_nodes[src][dest] = 1;
   
            }
            else if(src != -1 && dest != -1){  //read the directed edges from graph and store in the adjacency lists
                src_nodes[dest-1] = 1;
                adj_list *nod = new adj_list(dest);
                nod->next = nodes[src].outgoing_list;
                nodes[src].outgoing_list = nod;
                adj_list *dest_nod = new adj_list(src);
                dest_nod->next = nodes[dest].incoming_list;
                nodes[dest].incoming_list = dest_nod;
            }
        }
        input.close();  //close file after reading
         
    }
    void source_nodes();
    void find_similar_nodes();
    void DFS(int start, int count, int*max, int &maxim);
    void find_collapsed_nodes();
    void printResults();
};
