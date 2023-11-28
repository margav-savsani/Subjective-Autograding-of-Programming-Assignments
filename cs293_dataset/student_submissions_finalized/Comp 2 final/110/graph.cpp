#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "graph.h"

void Graph::addedge(int m,int n){
    nodes[n-1].source=false;        // changing the adjacencies accordingly
    nodes[m-1].outadjacency[n-1]=true;
    nodes[n-1].inadjacency[m-1]=true;
}

void Graph::similar(int m,int n){
    
    if(!nodes[m-1].sim[n-1]){    
        outfile<<"("<<m<<", "<<n<<") ";
        nodes[m-1].sim[n-1]=true;   //marking them as similar
    }
}

void Graph::printsource(){  // prints the source nodes
    outfile<<"Source nodes: ";
    for(int i=0;i<numNodes;i++){
        if(nodes[i].source) outfile<<i+1<<" ";
    }
    outfile<<endl;
    outfile<<endl;
}

bool Graph::case2(int m,int n){ //checks for case2 in similarity
    bool b=false;
    for(int i=0;i<numNodes;i++){
        if(nodes[m].inadjacency[i]){
            b=false;
            for(int j=0;j<numNodes;j++){
                if(nodes[n].inadjacency[j]){
                    if(nodes[i].sim[j] ){
                        b=true;
                    }
                }
            }  
            if(!b) break;  //even if one incoming node fails they are not similar    
        }   
    }
    return b;
}    

void Graph::findsimilar(){
    
    for(int i=0;i<numNodes;i++){    //case3 of similarity
        int k=0,h;
        for(int j=0;j<numNodes;j++){
            if(nodes[i].inadjacency[j]){
                k++;
                h=j;
            }
        }
        if(k==1) similar(i+1,h+1);
    }
    while(true){    //case2 of similarity
       int k=0;
        for(int i=0;i<numNodes;i++){
            for(int j=0;j<numNodes;j++){
                if(i!=j && case2(i,j) && case2(j,i)){
                    if(!(nodes[i].sim[j] && nodes[j].sim[i])){
                        k++;
                        similar(i+1,j+1);
                        similar(j+1,i+1);
                    }
                }
            }
        }
        if(k==0) break; // breaks, if no further similarities are added
    }
    outfile<<endl; outfile<<endl;
}

void Graph:: changeval(int a, int b){ // changes the value of the node while collapsing
    for(int i=0; i<numNodes; i++){
        if(nodes[i].value==b ){
            nodes[i].change=true;
            nodes[i].value=a;
        }
    }
}

void Graph:: collapsedgraph(){
    outfile<<"Collapsed graph:"<<endl;
    outfile<<endl; 
    bool val[numNodes][numNodes];   //to avoid the repetition of edges
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            val[i][j]=true; // setting all of them to true
            if(nodes[i].sim[j]){
                if(nodes[i].value>nodes[j].value){
                    changeval(nodes[i].value,nodes[j].value);
                }
                if(nodes[j].value>nodes[i].value){
                    changeval(nodes[j].value,nodes[i].value);
                }
            }
        }
    }
    int c=0;
    for(int i=0;i<numNodes;i++){
        if(!nodes[i].change) c++;   //counting no of collapsed edges
    }
    outfile<<c<<": ";
    for(int i=0;i<numNodes;i++){
        if(!nodes[i].change) outfile<<nodes[i].value<<" "; //printing the values
    }
    outfile<<endl;
    
    for(int i=0;i<numNodes;i++){    //printing the edges of the collapsed graph
        for(int j=0;j<numNodes;j++){
            if(nodes[i].outadjacency[j] && nodes[i].value!=nodes[j].value){
                if(val[nodes[i].value-1][nodes[j].value-1]){
                    val[nodes[i].value-1][nodes[j].value-1]=false;
                    outfile<< nodes[i].value << " "<< nodes[j].value<<endl;
                }
            }
        }
    }
    
}