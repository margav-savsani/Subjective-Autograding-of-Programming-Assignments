#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#define cout graphFile

void Graph::read_graph(){
    // read the graph and also updates sources

    int n1, n2;
    cin >> n1 >> n2;
    while (n1!=-1 && n2 != -1) {
        if(nodes[n1-1].insertout(n2-1)){
            nodes[n2-1].insertin(n1-1);
            numEdges++;
            sources[n2-1] = false;
        }
        cin>>n1>>n2;
    }
}

void Graph::print_sources(){
    // prints sources
    cout<<"Source nodes:";
    for (int i = 0; i < numNodes; i++) {
        if(sources[i]) cout<<" "<<(i+1);
    }
    cout<<endl<<endl;
}

void Graph::read_similar(){
    // reads similar and updates the graph
    // condition 1
    int n1, n2;
    cin >> n1 >> n2;
    while (n1!=-1 && n2 != -1) {
        // nodes[n1-1].insertsimilar(n2-1);
        similarity[n1-1][n2-1] = 1;
        cin>>n1>>n2;
    }
}

void Graph::similar_check3(){
    // perform condition 3 on the graph

    for(int i=0; i<numNodes; i++){
        if(nodes[i].numin == 1){
            // nodes[i].insertsimilar(nodes[i].inedges->obj);
            similarity[i][nodes[i].inedges->obj] = 1;
        }
    }
}

// void Graph::calc_similar(){
//     // calculates similarity relations
//
//     similar_check3();
//
//     while(true){
//         bool found = false;
//         for(int i=0; i<numNodes; i++){
//             for(int j=0; j<numNodes; j++)
//             {
//                 if(sources[i] || sources[j]) continue;
//
//                 if(similarity[i][j]) continue;
//
//                 if(check2(i, j) && check2(j,i))
//                 {
//                     // nodes[j].insertsimilar(i);
//                     // nodes[i].insertsimilar(j);
//                     similarity[i][j] = true;
//                     similarity[j][i] = true;
//                     found = true;
//                 }
//             }
//         }
//         if(!found) break;
//     }
// }

void Graph::calc_similar(){
    // calculates similarity relations

    similar_check3();

    // calculating the similarity matrix
    for(int i=0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            if(similarity[i][j] == -1) 
                similar(i, j);
        }
    }
}

bool Graph::similar(int n1, int n2){
    // returns value of similarity matrix based on memoization
    if(similarity[n1][n2]==-1){
        if(sources[n1] || sources[n2]){
            similarity[n1][n2]=0;
        }
        else{
            if(check2(n1, n2) && check2(n2, n1)){
                similarity[n1][n2] = 1;
                similarity[n2][n1] = 1;
            }
            else{
                similarity[n1][n2] = 0;
            }
        }
    }
    return similarity[n1][n2];
}

bool Graph::check2(int n1, int n2){
    // does a one way condition 2 check on (n1, n2)
    auto temp1 = nodes[n1].inedges;
    while(temp1!= nullptr){
        auto temp2 = nodes[n2].inedges;
        bool found = false;
        while(temp2!=nullptr){
            if(similar(temp1->obj, temp2->obj)){
                found = true; 
                break;
            }
            temp2 = temp2->next;
        }
        if(!found) return false;
        temp1 = temp1->next;
    }
    return true;
}

void Graph::print_similar(){
    // prints similar nodes in reqd format
    cout<<"Similar node pairs:";
    for(int i = 0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            if(similarity[i][j] == 1) cout<<" ("<<i+1<<", "<<j+1<<")";
        }
    }
    cout<<endl<<endl;
}

void Graph::collapse(){
    // create a collapsed graph from the current graph

    // initialisation of components
    alias = new int[numNodes];
    bool* visited = new bool[numNodes];
    for(int i=0; i<numNodes; i++){
        visited[i] = false;
        alias[i] = 0;
    }

    // marking the nodes as their component number
    num_collcomp = 0;
    for(int i=0; i<numNodes; i++){
        if(visited[i]) continue;
        dfs(i, visited, num_collcomp);
        num_collcomp++;
    }
    delete[] visited;

    // initailising edges
    collapsegraph = new bool*[num_collcomp];
    for(int i =0; i<num_collcomp; i++){
        collapsegraph[i] =  new bool[num_collcomp];
        for(int j=0; j<num_collcomp; j++){
            collapsegraph[i][j]=false;
        }
    }

    // marking the edges
    for(int i=0; i<numNodes; i++){
        auto curr = nodes[i].outedges;
        while (curr!=nullptr){
            if(alias[i] != alias[curr->obj])
                collapsegraph[alias[i]][alias[curr->obj]] = true;
            curr = curr->next;
        }
    }

    // marking the collapsed value to the node
    collNodes = new int[num_collcomp];
    for(int i=0; i<num_collcomp; i++){
        for(int j= numNodes - 1; j>=0; j--){
            if(alias[j]==i){
                collNodes[i] = j;
                break;
            }
        }
    }

}

void Graph::print_collapsed(){

    // print sthe collapsed garph in required format

    cout<<"Collapsed graph:\n\n";
    cout<<num_collcomp<<":";
    for(int i=0; i<num_collcomp; i++){
        cout<<" "<<collNodes[i]+1;
    }
    cout<<endl;

    for(int i=0; i<num_collcomp; i++){
        for(int j= 0; j<num_collcomp; j++){
            if(collapsegraph[i][j]){
                cout<<collNodes[i]+1<<" "<<collNodes[j]+1<<endl;
            }
        }
    }
    cout<<endl;
}

void Graph::dfs(int n, bool* visited, int comp)
{
    // a helper dfs is used in collpasing and marking the edges
    alias[n] = comp;
    visited[n] =true;
    for(int i=0; i<numNodes; i++){
        if(visited[i]) continue;
        if(!(similarity[n][i] || similarity[i][n])) continue;
        dfs(i, visited, comp);
    }
}

#endif
