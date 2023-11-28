#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include<cmath>

void Graph::checkSimilarity(){
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(nodes[j].num_from==1){
                if(nodes[j].from->object == nodes[i]){
                    similar_nodes[j][i] = true;
                }
            }
            
            int n1 = nodes[i].num_from;
            int n2 = nodes[j].num_from;
            if(n1!=0 && n2!=0){
                listOfObjects<Node> *adj1 = nodes[i].from;

                bool f1 = true;
                for(int k=0;k<n1;k++){
                    bool foundforcurr = false;
                    listOfObjects<Node> *adj2 = nodes[j].from;
                    for(int l=0;l<n2;l++){ 
                        if(similar_nodes[adj1->object.value-1][adj2->object.value-1]==1){
                            foundforcurr = true;
                        }
                        adj2 = adj2->next;
                    }
                    if(!foundforcurr){
                        f1 = false;
                    }
                    adj1 = adj1->next;
                }

                if(f1){
                    listOfObjects<Node> *adj1 = nodes[j].from;
                    int n1 = nodes[j].num_from;
                    int n2 = nodes[i].num_from;

                    bool f1 = true;
                    for(int k=0;k<n1;k++){
                        bool foundforcurr = false;
                        listOfObjects<Node> *adj2 = nodes[i].from;
                        for(int l=0;l<n2;l++){ 
                            if(similar_nodes[adj1->object.value-1][adj2->object.value-1]==1){
                                foundforcurr = true;
                            }
                            adj2 = adj2->next;
                        }
                        if(!foundforcurr){
                            f1 = false;
                        }
                        adj1 = adj1->next;
                    }
                    if(f1){
                        similar_nodes[i][j] = true;
                        similar_nodes[j][i] = true;
                    }
                }
            }            
        }
    }

    graphFile << "Similar node pairs:";
    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(similar_nodes[i][j]){
                graphFile.flush();
                graphFile << " (" << i+1 << "," << j+1 << ")";
            }
        }
    }
    /*
    int depth = 0;
    for(int i=0;i<numNodes;i++){
        if(sourceNode[i]){
            int x = DFS_fordepth(nodes[i],0);
            depth = max(depth,x);
        }
    }
    cout << depth << endl;

    listOfObjects<int> **levelarr = new listOfObjects<int>*();
    for(int i=0;i<=depth;i++){
        levelarr = nullptr;
    }
    for(int i=0;i<numNodes;i++){
        DFS_forsimilarity(nodes[i],levelarr,0);
    }
    */
}

void Graph::DFS_forsimilarity(Node node,listOfObjects<int> **levelarr,int level){
    if(level!=0){
        if(levelarr[level]==nullptr){
            levelarr[level]= new listOfObjects<int>(nodes[node.getvalue()-1].getvalue());
        }
        else{
            listOfObjects<int> *x = levelarr[level];
            bool found = false;
            while(x->next!=nullptr){
                if(x->object == nodes[node.getvalue()-1].getvalue()){
                    found = true;
                    break;
                }
                x= x->next;
            }
            if(!found){
                if(!(x->object == nodes[node.getvalue()-1].getvalue())){
                    x->next = new listOfObjects<int>(nodes[node.getvalue()-1].getvalue());
                }
            }
        }
    }
    
    listOfObjects<Node> *adj = nodes[node.getvalue()-1].to;
    while(adj!=nullptr){
        DFS_forsimilarity(nodes[adj->object.getvalue()-1],levelarr,level+1);
    }
}

int Graph::DFS_fordepth(Node node,int level){
    // for all nodes in adjto list for this node visit them and return maax of depth of all
    listOfObjects<Node> *adj = nodes[node.getvalue()-1].to;
    int z = level;
    while(adj!=nullptr){
        z = max(DFS_fordepth(adj->object,level+1),z);
        adj = adj->next;
    }
    return z;
}

#endif