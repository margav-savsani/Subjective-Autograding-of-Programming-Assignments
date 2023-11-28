#ifndef GRAPH_H
#include "Graph.h"
#endif

//Implementation of graph functions

//Constructor 1
Graph::Graph(int n1, int n2){
    nNodes = n1;
    nEdges = n2;
    nodes = new Node[nNodes];
    isSource = new bool[nNodes];
    isSink = new bool[nNodes];
    for ( int i = 0 ; i < nNodes ; i++ ){
        isSource[i]=true;
        isSink[i]=true;
    }
}

//Constructor 2
Graph::Graph(int n1){
    nNodes = n1;
    nodes = new Node[nNodes];
    isSource = new bool[nNodes];
    isSink = new bool[nNodes];
    for ( int i = 0 ; i < nNodes ; i++ ){
        isSource[i]=true;
        isSink[i]=true;
    }
}

//Returns true if n1 is similar to n2, false otherwise
bool Graph::checkSimilar(int value1, int value2){
    if ( nodes[value1].isSimilar && nodes[value2].isSimilar ){
        ListOfNodes *iter = nodes[value1].similarList->start;
        bool areSim = false;
        while ( iter != nullptr ){
            if( iter->value == &nodes[value2] ){
                areSim = true;
                break;
            }
            iter = iter->next;
        }
        return areSim;
    }
    else{
        return false;
    }
}

//Modifies the graph to make n1 similar to n2
void Graph::makeSimilar(int value1, int value2){
    if (!checkSimilar(value1,value2)){
        nodes[value1].isSimilar = true;
        nodes[value2].isSimilar = true;
        nodes[value1].similarList->insert(&nodes[value2]);
        nodes[value1].similarConnections->insert(&nodes[value2]);
        nodes[value2].similarConnections->insert(&nodes[value1]);
    }
}

//Used to make 2 source nodes similar as directed by the user
bool Graph::customSimilarity(int value1, int value2){
    if ( isSource[value1] && isSource[value2] ){
        makeSimilar(value1, value2);
        return true;
    }
    return false;
}

//Used to implement condition 3 of the question
void Graph::singleSimilarity(){
    for ( int i= 0 ; i < nNodes ; i++ ){
        if ( nodes[i].parentList->size==1 ){
            makeSimilar(nodes[i].id-1, nodes[i].parentList->start->value->id-1 );
        }
    }
}

//updates the similarity by running through the graph till now more changes are detected
bool Graph::updateSimilarity(int value1, int value2){
    if(checkSimilar(value1, value2)){
        return false;
    }
    Node *n1 = &nodes[value1];
    Node *n2 = &nodes[value2];

    if ( !isSource[value1] && !isSource[value2] ){ 
        //all nodes in parent of n1 are similar to some node in parent of n2
        ListOfNodes* n1parents = nodes[value1].parentList->start ;
        int areSim1 = 1;
        while(n1parents!=nullptr ){
            int match = 0;
            ListOfNodes* n2parents = nodes[value2].parentList->start;
            while(n2parents!=nullptr){
                if (checkSimilar(n1parents->value->id-1,n2parents->value->id-1)){
                    match = 1;
                    break;
                }
                n2parents = n2parents->next;
            }
            if(match==0){
                areSim1 = 0;
                break;
            }
            n1parents = n1parents->next;
        }
        ListOfNodes* n2parents = nodes[value2].parentList->start ;
        int areSim2 = 1;
        while(n2parents!=nullptr ){
            int match = 0;
            ListOfNodes* n1parents = nodes[value1].parentList->start;
            while(n1parents!=nullptr){
                if (checkSimilar(n2parents->value->id-1,n1parents->value->id-1)){
                    match = 1;
                    break;
                }
                n1parents = n1parents->next;
            }
            if(match==0){
                areSim1 = 0;
                break;
            }
            n2parents = n2parents->next;
        }
        if (areSim1){
            makeSimilar(value1, value2);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

//Simple helper function for max
int Graph::max ( int a , int b){
    if (a>b){
        return a;
    }
    else{
        return b;
    }
}

//A modified DFS for connected component of graph that returns the maximum id present in the component
int Graph::simDFS(Node *Source, bool* hasVisited, int seriesNumber){
    hasVisited[Source->id-1] = true;
    Source->component_number = seriesNumber;
    ListOfNodes* adjNode = Source->similarConnections->start;
    int m = Source->id;
    while(adjNode!=nullptr){
        if(!hasVisited[adjNode->value->id-1]){
            m = max(m, simDFS(adjNode->value, hasVisited, seriesNumber));
        }
        adjNode = adjNode->next;
    }
    return m;
};

//Prints the edges of collapsed graphs
void Graph::printEdges(){
    pairNodeList P;
    for ( int i = 0 ; i < nNodes ; i++ ){
        ListOfNodes* adjNode = nodes[i].adjList->start;
        while(adjNode!=nullptr){
            if ( nodes[i].component_number!=adjNode->value->component_number ){
                P.insert(nodes[i].collapsedId,adjNode->value->collapsedId  );
                //cout << nodes[i].collapsedId << " " << adjNode->value->collapsedId << endl;
            }
            adjNode = adjNode->next;
        }
    }
    P.print();
}

//Modified DFS on multi component graph
int Graph::similarDFS(){
    bool* hasVisited = new bool[nNodes];
    int* ids = new int[nNodes];
    int count = 0;
    for ( int i = 0 ; i < nNodes ; i++ ){
        if (!hasVisited[i]){
            count++;
            int v = simDFS(&nodes[i], hasVisited, count);
            ids[i]=v;
            for ( int j = 0  ; j < nNodes ; j++ ){
                if(nodes[j].component_number==count){
                    nodes[j].collapsedId = v;
                }
            }
        }
    }
    cout << count << ": ";
    for ( int i = 0 ; i < nNodes; i++ ){
        if(ids[i]!=0){
            cout << ids[i] << " ";
        }
    }
    cout << endl;
    printEdges();

    return count;

}