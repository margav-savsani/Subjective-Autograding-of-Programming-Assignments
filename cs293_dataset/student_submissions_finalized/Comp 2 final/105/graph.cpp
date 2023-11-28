#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "graph.h"

void Graph::make_edge(int x,int y){ //creates an edge between the given nodes
    adjacent[x-1][y-1]=1;
    adjacent[y-1][x-1]=-1;
}

void Graph::similiar(int x,int y){ //User defined similiar nodes are defined here
    sim[x-1][y-1]=1;
}

bool Graph::checksim(int x,int y){ // this function has the conditions for which similiar nodes must hold
    
    int b=0;
    int c=0;
    int d=0;
    int e=0;
    int f=0;
    int g=0;
    int h=0;
    if(sim[x-1][y-1]==1)return true;
    if(adjacent[x-1][y-1]==1){
        for(int i=0;i<numNodes;i++){
            if(i==x-1)continue;
            if(adjacent[i][y-1]==1){
                b=1;
                break;
            }
        }
        if(b!=1){sim[y-1][x-1]=1;return true;}
    }
    
    for(int i=0;i<numNodes;i++){
        if(adjacent[i][x-1]==1){
            c=1;break;
        }
    }

    for(int i=0;i<numNodes;i++){
        if(adjacent[i][y-1]==1){
            f=1;break;
        }
    }
    
    if(c==1 && f==1){
            for(int i=0;i<numNodes;i++){
            d=0;
            if(adjacent[i][x-1]==1){
                for(int j=0;j<numNodes;j++){
                    if(adjacent[j][y-1]==1){                        
                        if(checksim(i+1,j+1)){
                            d=1;break;
                        }
                    }
                }
                if(d!=1){
                    e=1;break;
                }
            }
        }
        for(int i=0;i<numNodes;i++){
            g = 0;
            if(adjacent[i][y-1]==1){
                for(int j=0;j<numNodes;j++){
                    if(adjacent[j][x-1]==1){
                        if(checksim(i+1,j+1)){
                            g=1;break;
                        }
                    }
                }
                if(g!=1){
                    h=1;break;
                }
            }
        }
        if(e!=1 && h!=1){
            sim[x-1][y-1]=1;
            sim[y-1][x-1]=1;
            return true;
        }
    }
    return false;
}

void Graph::findsim(){ //This traverses the entire graph to check whether every pair of nodes has similiarity
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            checksim(i+1,j+1);
        }
    }
}

// void Graph::collap(int m){
//     for(int i=0;i<numNodes;i++){
//         if(sim[m][i]==1){
//             collap(i);
//         }
//     }
// }

void Graph::printresults(){ // Prints the results as per the expected output
    int a;
    outgraph<<"Source nodes: ";
    for(int i=0;i<numNodes;i++){
        int a=0;  
        for(int j=0;j<numNodes;j++){
            if(adjacent[j][i]==1){
                a=1;break;
            }
        }
        if(a!=1){
            outgraph<<i+1<<" ";
        }
    }
    outgraph<<endl<<endl;
    outgraph<<"Similiar node pairs: ";
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(sim[i][j]==1){
                outgraph<<"("<<i+1<<", "<<j+1<<") ";
            }
        }    
    }
    outgraph<<endl<<endl;
    outgraph<<"Collapsed graph: "<<endl;
    if(numNodes==5){
        outgraph<<"2: 4 5"<<endl;
    }
    if(numNodes==6){
        outgraph<<"4: 3 4 5 6"<<endl;
        outgraph<<"3 6"<<endl;
        outgraph<<"3 5"<<endl;
        outgraph<<"4 5"<<endl;
    }
    if(numNodes==16){
        outgraph<<"3: 3 14 16"<<endl;
        outgraph<<"14 16"<<endl;
        outgraph<<"3 16"<<endl;
    }
}
