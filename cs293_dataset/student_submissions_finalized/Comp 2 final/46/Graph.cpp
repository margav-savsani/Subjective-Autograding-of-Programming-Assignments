#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include <fstream>
#endif

ofstream f_out("outgraph.txt");

Graph::Graph(int n,int **adj,int **sim,int **new_s, bool *arr) {
    numOfNodes = n;
    nodes = new Node[n];
    // assigning the labels to the nodes
    for(int i=1;i<=numOfNodes;i++){
        nodes[i-1] = Node(i);
        nodes[i-1].is_source = !(arr[i-1]);
    }
    adj_mat = adj;
    sim_mat = sim;
    new_sim = new_s;
    return;
}
void Graph::add_edge(int a, int b){ // adding the egde
    nodes[b-1].is_source = false;
    return;
}
void Graph::source(){
    f_out << "Source Nodes = ";
    for(int i=0;i<numOfNodes;i++){
        if(nodes[i].is_source){
            f_out <<nodes[i].val<<" "; // printing the source nodes
        }
    }
    f_out << "\n"<<endl;
    return;
}
void Graph::similar(){

    for(int i=0; i<numOfNodes;i++){
        for(int j=0; j<numOfNodes;j++){
            
            //case-1
            if(sim_mat[i][j]==1){
                if(nodes[i].is_source==1 && nodes[j].is_source==1) {
                    new_sim[i][j] = 1;
                }
            }

            if(i==j) continue;

            // case-3
            if(adj_mat[j][i]==1){
                int cnt=0;
                bool is_sim=true;
                for(int p=0;p<numOfNodes;p++){
                    if(cnt>1) {
                        is_sim=false; // not similar
                        break;
                    }
                    if(adj_mat[p][i]==1) cnt++; // incrementing the cnt
                }
                if(is_sim){
                    new_sim[i][j] = 1;
                }
            }

            //case-2
            if(nodes[i].is_source==false && nodes[j].is_source==false){
                
                bool t1=false,t2=false; // checking for vice-versa

                int a = 0,b=0;
                for(int k=0;k<numOfNodes;k++){
                    if(adj_mat[k][i]==0) continue;
                    a++;
                    // bool *tmp=new bool[numOfNodes];
                    for(int l=0;l<numOfNodes;l++) {
                        if(adj_mat[l][j]==1 && new_sim[k][l]==1) {
                            b++;
                            break; // found atlest one node
                        }
                    }
                    // if(t1) {
                    //     break;
                    // }
                }
                if(a==b) t1=true;
                a = 0;
                b = 0;
                for(int k=0;k<numOfNodes;k++) {
                    if(adj_mat[k][j]==0) continue;
                    a++;
                    for(int l=0;l<numOfNodes;l++) {
                        if(adj_mat[l][i]==1 && new_sim[k][l]==1) {
                            b++;
                            break; // found atlest one node
                        }
                    }
                    // if(t2) {
                    //     break;
                    // }
                }
                if(a==b) t2=true;
                if(t1&&t2){
                    new_sim[i][j] = 1; // modifying the similar table
                    new_sim[j][i] = 1;
                }
            }

        }
    }
    f_out << "Similar node pairs: ";
    for(int i=0; i<numOfNodes;i++){
        for(int j=0; j<numOfNodes;j++){
            if(new_sim[i][j]==1) {
                f_out <<"("<<i+1<<" ,"<<j+1<<") "; //printing into filr
            }
        }
    }
    f_out << "\n\n";
}

bool Graph::DFS(int i,int *m,int *arr){
       bool is_l = false;
        for(int j=0;j<numOfNodes;j++){
            if(new_sim[i][j]==1||new_sim[j][i]==1){ // check for similarity
                is_l = true;
                new_sim[i][j]=0;
                new_sim[j][i]=0;
                *m = max(j+1,*m); // updating the max value
                arr[i]=1; // visiting
                DFS(j,m,arr);
            }
        }
        arr[i]=1;
        return is_l;
}

void Graph::collapse(){

    // making undirected graph of smilar nodes
    for(int i=0;i<numOfNodes;i++){
        for(int j=0;j<numOfNodes;j++){
            if(new_sim[i][j]==1) new_sim[j][i]==1;
            if(new_sim[j][i]==1) new_sim[i][j]==1;
        }
    }

    int *st = new int[numOfNodes];
    for(int i=0;i<numOfNodes;i++){
        st[i]=0;
    }
    int cm=0;
    f_out << "Collapsed graph:"<<endl;

    for(int i=0;i<numOfNodes;i++){
        for(int j=0;j<numOfNodes;j++){
            if(new_sim[i][j]==1){
                new_sim[i][j]=0;
                new_sim[j][i]=0;
                int c = max(i+1,j+1); // max val of the eq. class
                int *p=&c;
                int *arr = new int[numOfNodes];
                for(int k=0;k<numOfNodes;k++){arr[k]=0;}
                arr[i]=1;
                if(DFS(j,p,arr)==true){ // calling dfs
                for(int k=0;k<numOfNodes;k++){
                    if(arr[k]==1){
                        nodes[k].val = *p;
                    for(int l=0;l<numOfNodes;l++){
                        if(adj_mat[k][l]==1) { // updating the edges
                            adj_mat[k][l]=0;
                            adj_mat[*p-1][l]=1;
                        }
                        if(adj_mat[l][k]==1) { // updating the edges
                            adj_mat[l][k]=0;
                            adj_mat[l][*p-1]=1;

                        }
                    }
                    }
                }
                }
                st[cm]=*p;
                cm++;
                *p = -1;
            }
        }
    }
    f_out <<cm<<": ";
    for(int i=0;i<cm;i++){ 
        f_out <<st[i]<<" ";
    }
    f_out << endl;
    for(int i=0;i<numOfNodes;i++){
        for(int j=0;j<numOfNodes;j++){
            if(adj_mat[i][j]==1 && i!=j){
                f_out <<i+1<<" "<<j+1<<endl;
            }
        }
    }
}
