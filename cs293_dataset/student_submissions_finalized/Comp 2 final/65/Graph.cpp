#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;
void Graph::makeedge(int n1,int n2){
        nodes[n1-1].source++;
        nodes[n2-1].target++;
        nodes[n1-1].outadj[n2-1]++;
        nodes[n2-1].inadj[n1-1]++;
    }    


void Graph::printsource(){
    file<<"Source nodes: ";
    for(int i=0;i<numNodes;i++){
        if(nodes[i].target==0){
            sourcenodes[i]++;
            file<<nodes[i].value<<" ";
        }
    }
    file<<endl;
}

void Graph::makegivensimilar(int n1,int n2){
    if(sourcenodes[n1-1]!=0 && sourcenodes[n2-1]!=0){
        int p=0;
        while(simnodes[p].taken!=0){
            p++;
        }
        simnodes[p].taken++;
        simnodes[p].Node1=n1;
        simnodes[p].Node2=n2;
    }
}

void Graph::makesimilar(){
    for(int i=0;i<numNodes;i++){
        if(nodes[i].target==1){
            int n2;
            for(int j=0;j<numNodes;j++){
                if(nodes[i].inadj[j]!=0){
                    n2 = j+1;
                    break;
                }
            }
            int p=0;
            while(simnodes[p].taken!=0){
                p++;
            }
            simnodes[p].taken++;
            simnodes[p].Node2=n2;
            simnodes[p].Node1=nodes[i].value;
        }
    }

    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(i!=j && sourcenodes[i]==0 && sourcenodes[j]==0){
                if(checksimilarity(nodes[i],nodes[j])){
                    int p=0;
                while(simnodes[p].taken!=0){
                    p++;
                }
                simnodes[p].taken++;
                simnodes[p].Node1=nodes[i].value;
                simnodes[p].Node2=nodes[j].value;
                simnodes[p+1].taken++;
                simnodes[p+1].Node1=nodes[j].value;
                simnodes[p+1].Node2=nodes[i].value;
                }
            }
        }
    }
}

bool Graph::checksimilarity(Node n1,Node n2){
    int len1=0;
    int len2=0;
    for(int i=0;i<numNodes;i++){
        if(n1.inadj[i]!=0){
            len1++;
        }
        if(n2.inadj[i]!=0){
            len2++;
        }
    }

    if(len1==0 || len2==0){
        return false;
    }

    int inadj1[len1];
    int inadj2[len2];
    int a=0;
    int b=0;
    for(int i=0;i<numNodes;i++){
        if(n1.inadj[i]!=0){
            inadj1[a]=i+1;
            a++;
        }
        if(n2.inadj[i]!=0){
            inadj2[b]=i+1;
            b++;
        }
    }
    a=0;
    b=0;
    for(int i=0;i<len1;i++){
        int check=0;
        int p=0;
        while(simnodes[p].taken!=0){
            if(simnodes[p].Node1==inadj1[i]){
                check++;
            }
            p++;
        }
        if(check==0){
            return false;
        }
    }
    
    for(int i=0;i<len2;i++){
        int check=0;
        int p=0;
        while(simnodes[p].taken!=0){
            if(simnodes[p].Node1==inadj2[i]){
                check++;
            }
            p++;
        }
        if(check==0){
            return false;
        }
    }

    for(int i=0;i<len1;i++){
        int check=0;
        int p=0;
        while(simnodes[p].taken!=0){
            if(simnodes[p].Node1==inadj1[i]){
                int n2value = simnodes[p].Node2;
                if(n2.inadj[n2value-1]!=0){
                    check++;
                }
            }
            p++;
        }
        if(check==0){
            return false;
        }
    }

    for(int i=0;i<len2;i++){
        int check=0;
        int p=0;
        while(simnodes[p].taken!=0){
            if(simnodes[p].Node1==inadj2[i]){
                int n1value = simnodes[p].Node2;
                if(n2.inadj[n1value-1]!=0){
                    check++;
                }
            }
            p++;
        }
        if(check==0){
            return false;
        }
    }
    return true;
}
void Graph::printsimilar(){
    file<<"Similar node pairs: ";
    int p=0;
    while(simnodes[p].taken!=0){
        file<<"("<<simnodes[p].Node1<<", "<<simnodes[p].Node2<<") ";
        p++;
    }
    file<<endl;
    file<<"Collapsed Graph: "<<endl;
}


#endif