
#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif

class Graph{
    int ** newadj;
    int numNodes;
    int num;
    int ** adjacent;
    
    public:
    
    Graph(int n){
    
    numNodes=n;
    //int adjacent[numNodes][numNodes];
    adjacent = new int*[numNodes];
    
    for( int i=0; i< numNodes; i++){
        adjacent[i] = new int[numNodes];
        for( int j=0; j< numNodes; j++){
          adjacent[i][j] = 0;
        }
      }
    newadj = new int*[numNodes];
    for( int i=0; i< numNodes; i++){
        newadj[i] = new int[numNodes];
        for( int j=0; j< numNodes; j++){
          newadj[i][j] = 0;
        }
      }
    }
    void simil();
    void check(int i,int j);
    void siso(int i,int j);
    void modify_adj(int i,int j);
    void sourcenodes();
    void similarnodes();
    void print();
    
};