#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <iostream>
#include <fstream>

using namespace std;

class Node{
    public:
        int value;
        int source;
        int target;
        int* similartail; // Tail of similar nodes where this is head
        int* similarhead; // Head of similar nodes where this is tail
        int* outadj;    //Edges from this node to other
        int* inadj;     //Edges from other node to this
        Node(){
            this->value = 0;
            this->source = 0;
            this->target = 0; 
        }
        Node(int value){
            this->value = value;
            this->source = 0;
            this->target = 0;
        }
};

class Edge{
  public:
    int taken;
    int nsource;
    int ntarget;
};

class SimilarNodes{
  public:
    int taken;
    int Node1;
    int Node2;
};

class Graph{
    public:
    int numNodes;
    int numEdges;
    Node *nodes;
    Edge *Edges;
    SimilarNodes *simnodes;
    int *sourcenodes;
    ofstream file;
    Graph(int nNodes){
        numNodes = nNodes;
        nodes = new Node[numNodes];
        simnodes = new SimilarNodes[10000];
        sourcenodes = new int[numNodes];
        file = ofstream("outgraph.txt");
        for(int i=0;i<numNodes;i++){
            nodes[i].value=i+1;
            nodes[i].inadj = new int[numNodes];
            nodes[i].outadj = new int[numNodes];
            for(int j=0;j<numNodes;j++){
                nodes[i].inadj[j]=0;
                nodes[i].outadj[j]=0;
            }
        }
        for(int i=0;i<numNodes;i++){
            sourcenodes[i]=0;
        }
        for(int i=0;i<numEdges;i++){
            Edges[i].taken=0;
        }
        for(int i=0;i<numEdges;i++){
            simnodes[i].taken=0;
        }
    }

    

    void makeedge(int n1, int n2);
    void printsource();
    void makegivensimilar(int n1,int n2);
    void makesimilar();
    bool checksimilarity(Node n1,Node n2);
    void printsimilar();

    ~Graph(){
    if (file.is_open())
    {
      file.close();
    }
    delete[] nodes;
    delete[] Edges;
    delete[] sourcenodes;
    delete[] simnodes;
  }
};

#endif