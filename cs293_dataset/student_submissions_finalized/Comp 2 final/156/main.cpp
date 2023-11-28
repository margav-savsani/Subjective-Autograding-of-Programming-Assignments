#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif


int main(int argc, char **argv){
    
    Graph *myGraph;

    myGraph = new Graph("outGraph.txt");
    myGraph->checkSimilarity();

    // have to create a list for all the edges too as would be required
    // in node class n add a list that stores all the nodes that have a edge from them to node n

    // list of all similar node pairs
    /*listOfObjects<Similar> *similar_nodes = nullptr;

    int numNodes;
    cin >> numNodes;

    // stores what all nodes are sourceNodes
    bool sourceNode[numNodes];
    for(int i=0;i<numNodes;i++){
        sourceNode[i] = true;
    }
    
    int num1=0;
    int num2=0;

    // reading the directed edges from node1 to node2
    cin >> num1 >> num2;

    while(num1!=-1 && num2!=-1){
        //add edge from num1 to num2 first and then take input again
        sourceNode[num2-1] = false;
        cin >> num1 >> num2;
    }

    cout << "Source nodes:";
    for(int i=0;i<numNodes;i++){
        if(sourceNode[i]){
            cout << " " << i+1;
        }
    }
    cout << endl;
    cout << endl;

    // now we are done reading in the directed edges now read in the similar nodes
    cin >> num1 >> num2;

    while(num1!=-1 && num2!=-1){
        //add edge from num1 to num2 first and then take input again
        if(sourceNode[num1-1] && sourceNode[num2-1]){
            if(similar_nodes==nullptr){
                Similar *dummy = new Similar;
                similar_nodes = new listOfObjects<Similar>(*dummy);
                similar_nodes->object.set(num1,num2);
            }
            else{
                listOfObjects<Similar> *trial = similar_nodes;
                while(trial->next!=nullptr){
                    trial = trial->next;
                }
                Similar *dummy = new Similar;
                trial->next = new listOfObjects<Similar>(*dummy);
                trial->next->object.set(num1,num2);
            }
        }
        cin >> num1 >> num2;
    }

    listOfObjects<Similar> *trial = similar_nodes;
    cout << "Similar node pairs: ";
    while(trial!=nullptr){
        cout << "(" << trial->object.node1 << "," << trial->object.node2 << ")";
        trial = trial->next;
    }
    cout << endl;
    */
}