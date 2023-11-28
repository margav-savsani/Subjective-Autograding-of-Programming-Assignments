#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class Graph{
    int numNodes;
    fstream outgraph;
    int **adjacent;
    int **sim;

  public:
    Graph(int x,string f){
        numNodes=x;
        outgraph.open(f, ios::out);
        if (!outgraph.is_open()) {
            cerr << "Couldn't open graph file " << f << ". Aborting ..." << endl;
            exit(-1);
        }

        adjacent=new int*[numNodes]; //2-D array to store the the adjacent nodes
        for( int i=0; i< numNodes; i++){
            adjacent[i] = new int[numNodes];
            for( int j=0; j< numNodes; j++){
                adjacent[i][j] = 0;
            }
        }

        sim=new int*[numNodes]; //2-D array to store the the similiarity nodes
        for( int i=0; i< numNodes; i++){
            sim[i] = new int[numNodes];
            for( int j=0; j< numNodes; j++){
                sim[i][j] = 0;
            }
        }
    }

    void similiar(int x,int y);
    void make_edge(int x, int y);
    bool checksim(int x,int y);
    void findsim();
    void collap();
    void printresults();
};