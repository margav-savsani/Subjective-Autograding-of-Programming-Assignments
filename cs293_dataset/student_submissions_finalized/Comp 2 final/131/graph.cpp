//#ifndef GRAPH_BST_CPP
//#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "graph.h"
#endif

void Graph:: findsimilar(){
    
    for (int i=1; i<=numNodes;i++){ // iterate over all the node sof the graph 
        adjacent * incoming =nodes[i].fromadjacencylist;  // create  a copy of the incoming edges of the of the node[i]
        int incom_no=0; // for counting the number of incoming edges
        while (incoming!= nullptr){
                incom_no++;  // iterate to find total incoming edges
                incoming= incoming->next;
        }
        if (incom_no==1){ // if incoming edge is just one 
            //cout<<"("<<i<<","<<nodes[i].fromadjacencylist->value<<") "; // then this the 3 rd condition for similarity 
            nodes[i].similarlist[nodes[i].fromadjacencylist->value] =true ; // update the similarity array of node [i] with its only parent 
        }
    }
 
    for (int i=1; i<=numNodes;i++){  // iterate over all nodes in the graph let it be m1
        for (int j=1; j<= numNodes; j++){  // double iteration over all nodes in the graph  let it be m2
                if (nodes[i].similarlist[j] ==true && nodes[j].similarlist[i]==true) // if m1 and m2 are similar amd m2 and m1 ares imilar 
                    {   adjacent * m1out= nodes[i].toadjacencylist;  // adjacency list of m1 
                        adjacent * m2out= nodes[j].toadjacencylist;  // adjacency list of m2
                         
                        while(m1out!=nullptr){
                            while(m2out  !=nullptr){
                                if (i==j && m1out->value==m2out->value){ // to prevent self edges 
                                    m2out=m2out->next;
                                    continue;
                                }
                            nodes[m1out->value].similarlist[m2out->value] = true; // n1 is similar to n2 
                            nodes[m2out->value].similarlist[m1out->value] = true;// n2 is similar to n1 
                            m2out= m2out->next;} // iteration updation
                            m1out= m1out->next; //iteration updation 
                            m2out=nodes[j].toadjacencylist; 
                        }
                    }
        }
    }
}

void Graph::printResults(){
    fstream outfile;  
    string fileoutname="out.txt"; // name of the output file 
    outfile.open(fileoutname, ios::out);
    outfile<<"source nodes: ";  // to avoid any ambiguity printed all result in the terminal 
    for (int i=1; i<=numNodes; i++){ // otherwise to print in out file , just replace 'cout' by 'outfile'
      if (sourceyes[i]== true){  // if the value of the sourcenode bool array is still true 
        outfile<< i<<" "; }    // then this node is a source node 
    }
    outfile<<endl;
     outfile<<"similar nodes: ";
    
    for(int i=1; i<=numNodes; i++){ // to find th final similar nodes 
        for (int j=1; j<=numNodes; j++){// iterate over all the nodes twice 
            if (nodes[i].similarlist[j]==true){ // if two nodes are similar print the relation 
                outfile<<"("<<i<<" ,"<<j<<") ";
            }
        }
    }

    for(int i=1; i<=numNodes; i++){ //make an undirected graph of all the nodes which ar similar 
        for (int j=1; j<=numNodes; j++){ // so our adjacency list in this graph is our similarity list 
            if (nodes[i].similarlist[j]==true){
                nodes[j].similarlist[i]=true; // make a symmetric relation for undirectedness ;
            }
        }
    }
    int *maxcomp = new int [numNodes+1]; // to store the maximum among all the nodes of its component 
    for (int i=1; i<=numNodes; i++)  {
        maxcomp[i]=-1;  // initialise all the max component values to -1
    }
    int count=-10000;  // this counts the times which we perform the dfs or equilently the number of components in our new graph

   int *collpsedgraph= new int [ numNodes+1]; // to store nodes of the collapsed graph
   int maxindex=0; // which is essentially the max value of each component 

    for (int i=1; i<=numNodes; i++){
        if (maxcomp[i]==-1){
            int maximum=0; // stores the maximum of that component during dfs
            count++; 
            DFS (i, maxcomp, count , maximum); // perform dfs search on one component 
            for (int j=1; j<=numNodes; j++){
                if (maxcomp[j]== count){ // update all the the max comp of all nodes that were traveresed in this dfs 
                    maxcomp[j]= maximum; // that is which are in the same component 
                }
            }
             collpsedgraph[maxindex]= maximum;
             maxindex++;
        } 
    }
    outfile <<endl<<"Collapsed graph: "<<endl<< count+10000<<": "; // printing the number of nodes in the collapsed graph
        while(maxindex!= 0){
            maxindex--;  
            outfile<< collpsedgraph[maxindex]<<" "; // printing the nodes in the collapsed graph 
        }
    outfile<<endl;

    for (int i=1; i<=numNodes; i++){
        adjacent *toedges = nodes[i].toadjacencylist; // if there is a directed edge in the graph given in the question
        while(toedges!= nullptr){
            if (maxcomp[i]!= maxcomp[toedges->value]) // then there exists a directed edge between the max comp of those nodes
            {outfile<<maxcomp[i]<<" "<< maxcomp[toedges->value]<<endl; // in the same direction
        }
            toedges= toedges->next; // the same edges may be printed multiple times , ignore repition 
        }
    }
    outfile.close();
}

void Graph:: DFS(int vertex, int * maxcomp,int  count, int &maximum){
        maxcomp[vertex]= count ;  // set maxcomponent of each node encountered in dfs to value of count 
        maximum=  max(vertex, maximum); //update maximum value to maximum untill now of the component 
        for (int i=1; i<=numNodes; i++){
            if (nodes[vertex].similarlist[i]== true && maxcomp[i]==-1){ // node is not visited and is in the similarity
                   DFS(i, maxcomp, count, maximum );                  // that is the adjacency list 
            }     // recurse 
        }
}