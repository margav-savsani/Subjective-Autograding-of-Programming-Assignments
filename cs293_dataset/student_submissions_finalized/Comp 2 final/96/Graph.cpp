#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

bool find(int* arr,int n,int size){
    for(int i=0;i<size;i++){
        if(arr[i]==n) return true;
    }
    return false;
}

bool Node::isSource(int numNodes){
    for(int i=0;i<numNodes;i++){
        if(incoming[i]) return false;
    }
    return true;
}

bool Graph::isSimilar(int n1, int n2){

    if(nodes[n1].isSource(numNodes) && nodes[n2].isSource(numNodes) && nodes[n1].userSimilar[n2]) return true;

    if(nodes[n1].incoming[n2]){
        bool temp=true;
        for(int i=0;i<numNodes;i++){
            if(i!=n2 && nodes[n1].incoming[i]) temp=false;
        }

        if(temp) return true;
    }

    if(!nodes[n1].isSource(numNodes) && !nodes[n2].isSource(numNodes)){

        for(int i=0;i<numNodes;i++){
            if(nodes[n1].incoming[i]){
                bool temp=false;
                for(int j=0;j<numNodes;j++){
                    if(nodes[n2].incoming[j] && isSimilar(i,j)) temp=true;
                }
                if(!temp) return false;
            }
            if(nodes[n2].incoming[i]){
                bool temp=false;
                for(int j=0;j<numNodes;j++){
                    if(nodes[n1].incoming[j] && isSimilar(i,j)) temp=true;
                }
                if(!temp) return false;
            }
        }
        return true;
    }

    

    return false;
}

bool Graph::isConnected(int n1, int n2){
    if(nodes[n1].similar[n2]) return true;
    return false;
}

void Graph::printResults(){
    ofstream myFile("outgraph.txt");
    myFile<<"Source nodes: ";
    for(int i=0;i<numNodes;i++){
        if(nodes[i].isSource(numNodes)) myFile<<i+1<<" ";
    }
    myFile<<endl<<endl<<"Similar node pairs: ";
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(isSimilar(i,j)){
                nodes[i].similar[j]=true;
                nodes[j].similar[i]=true;
                myFile<<"("<<i+1<<", "<<j+1<<") ";
            }
        }
    }
    myFile<<endl<<endl<<"Collapsed graph:"<<endl<<endl;
    

    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(nodes[i].similar[j]){
                for(int k=0;k<numNodes;k++){
                    if(nodes[j].similar[k]){
                        nodes[i].similar[k]=true;
                        nodes[k].similar[i]=true;
                    }
                }
            }
        }
    }

    for(int i=0;i<numNodes;i++){
        int highest=-1;
        for(int j=0;j<numNodes;j++){
            if(nodes[i].similar[j]) highest=j;
        }
        if(highest==-1) collapsed[i]=i;
        else collapsed[i]=highest;
    }
    int count=0;
    for(int i=0;i<numNodes;i++){
        if(i==0 || !find(collapsed,collapsed[i],i)) count++;
    }
    myFile<<count<<": ";
    collapsedNodes=new int[count];
    count=0;
    for(int i=0;i<numNodes;i++){
        if(i==0 || !find(collapsed,collapsed[i],i)){
            collapsedNodes[count]=collapsed[i];
            count++;
            
        } 
    }
    sort(collapsedNodes,collapsedNodes+count);
    for(int i=0;i<count;i++){
        myFile<<collapsedNodes[i]+1<<" ";
    }

    for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            if(i!=j){
                for(int k=0;k<numNodes;k++){
                    if(nodes[collapsedNodes[i]].outgoing[k] && collapsed[k]==collapsedNodes[j]){
                        myFile<<endl<<collapsedNodes[i]+1<<" "<<collapsedNodes[j]+1;
                        break;
                    }
                }
            }
            
        }
    }
}