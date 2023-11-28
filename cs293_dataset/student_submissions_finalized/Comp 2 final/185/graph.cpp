#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#include "graph.h"
using namespace std;

void Graph::find_similar_nodes(){
   
    for(int m=1; m<=numVertices; m++){  //to find nodes that only have one incoming egde. Then the node is similar to the source node of that egde. 
                                        //here indices represents the number(value) of the nodes in the pair
        if(nodes[m].incoming_list != nullptr && nodes[m].incoming_list->next == nullptr){ //if the incoming_list of the node contains exactly one element, then it is similar to the node in the incoming_list 
            similar_nodes[m][nodes[m].incoming_list->node_no] = 1;  //updating the value of the pair of nodes in similar_nodes 2D array to 1
        }
    }

    for(int i=1; i<=numVertices; i++){  //iterating through the similar_nodes array. here indices represents the number(value) of the nodes in the pair
        for(int j=1; j<=numVertices; j++){
            if(similar_nodes[i][j] == 1 && similar_nodes[j][i] == 1){  //if any node i is similar to j and vice versa, then the nodes in the outgoing_list of i and j will also be similar.
                adj_list *sim1 = nodes[i].outgoing_list;
                adj_list *sim2 = nodes[j].outgoing_list;
                if(sim2 != nullptr){  //iterating through the outgoing_lists of the similar nodes to mark the nodes in the outgoing_list of i similar to the nodes in the  outgoing_list of j. 
                    while(sim1 != nullptr){  // outgoing_lists of nodes i and j must not be empty
                            int temp1 = sim1->node_no;
                            int temp2 = sim2->node_no;
                            if(temp1 != temp2){
                            similar_nodes[temp1][temp2] = 1;  //updating the value of pair in siilar_nodes array to 1
                            similar_nodes[temp2][temp1] = 1;
                            }
                            sim1 = sim1->next;
                            if(sim1 == nullptr){  //if pointer reaches to the end of the outgoing_list of i, then again set it to the start and shift the pointer in the outgoing_list of j a place forward.
                                sim1 = nodes[i].outgoing_list;
                                sim2 = sim2->next;
                            }
                            if(sim2 == nullptr){  //if the pointer reaches the end of the outgoing_list of j, then break the loop. we have successfully stored all similar pairs of nodes in the similar_nodes array
                                break;
                            }
                        }
                    }
                else{
                    continue;
                }
            }
        }
    }
    return;
}

void Graph::DFS(int start, int count, int *maxx, int &max_identifier){ //DFS on the given graph but undirected
    maxx[start]= count;
    if(start>max_identifier){
        max_identifier = start;
    }
        for(int c=1; c<=numVertices; c++){
            if(similar_nodes[start][c] == 1){
                if(maxx[c] == -1){
                    DFS(c,count,maxx, max_identifier);
                }
            }
        }
        return;
    }


void Graph::find_collapsed_nodes(){

    for(int i=1; i<=numVertices; i++){  //making the given graph undirected
        for(int j=1; j<=numVertices; j++){  //all the pair of nodes i and j whose value in similar_nodes array is 1 are similar
            if(similar_nodes[i][j] == 1){
                similar_nodes[j][i] = 1;
            }
        }
    }
    final = new int[numVertices+1];
    for(int g=0; g<=numVertices; g++){
        final[g] = 0;
    }

    int max_identifier = 0;  //stores the maximum identifer in an equivalence class of the graph

    maxx = new int[numVertices];  //array in which each index represent a node and its corresponding value represent the maximum idetifier in the node's equivalence class
    for(int i=0; i<=numVertices; i++){
            maxx[i] = -1;
        } 

    for(int j=1; j<=numVertices; j++){  //applying DFS on each component of the undirected graph
        if(maxx[j] == -1){
            count++;
            maxx[j] = 0;
            max_identifier = j;
            DFS(j, count, maxx, max_identifier );
        
        for(int g=1; g<=numVertices; g++){
            if(maxx[g] == count){
                maxx[g] = max_identifier;

            }
        }
        final[j] = max_identifier;
        }


    }
    return;
}


void Graph::printResults(){

    //printing all source nodes
    string out = "outgraph.txt";
    fstream output;
    output.open(out, ios::out);
    output << "Source nodes:" << " ";
    //source_nodes();
     for(int i=0; i<numVertices; i++){  //if there is no incoming edge to a node, the it's value in the src_node will be zero. hence it is a source node
        if(src_nodes[i] == 0){
            //cout << i+1 << ' ';
            output << i+1 << " ";  //write the source node in the outgraph.txt file
        }
    }
    output << endl;
    //printing all similar nodes
    output << "Similar node pairs:" << " ";
    find_similar_nodes();
    for(int i=1; i<=numVertices; i++){
        for(int j=1; j<=numVertices; j++){  //all the pair of nodes i and j whose value in similar_nodes array is 1 are similar
            if(similar_nodes[i][j] == 1){
                output << "(" << i << "," << j << ")" << " "; 
            }
        }
    }
    output << endl;

     //printing all collapsed graph
    output << "Collapsed graph:" << endl << endl;  //storing collapsed graph in the outgraph.txt file
    find_collapsed_nodes();
     output << 1000+count << ": ";
    for(int i=1; i<=numVertices; i++){
        if(final[i] != 0){
            output << final[i] << " ";
        }
    }
    output << endl;
    int check[numVertices+1][numVertices+1];
    for(int y=0; y<=numVertices; y++){
        for(int x=0; x<=numVertices; x++)
            check[y][x] = 0;
    }
    for(int h=1; h<=numVertices; h++){
        while(nodes[h].outgoing_list != nullptr){
        if(maxx[h] != maxx[nodes[h].outgoing_list->node_no]){
            if(check[maxx[h]][maxx[nodes[h].outgoing_list->node_no]] == 0){
                output << maxx[h] << " " << maxx[nodes[h].outgoing_list->node_no] << endl ;
                check[maxx[h]][maxx[nodes[h].outgoing_list->node_no]] = 1;
            }
        }
        nodes[h].outgoing_list = nodes[h].outgoing_list->next;
        }
        }
    output.close();
    return;
}