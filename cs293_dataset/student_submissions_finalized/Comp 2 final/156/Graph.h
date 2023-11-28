#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class listOfObjects {
    public:
    T object;
    listOfObjects<T> *next;

    // Constructor
    listOfObjects(){
        next = nullptr;
    }

    listOfObjects(T initValue) {object = initValue; next = nullptr;}

    // Destructor
    ~listOfObjects() {;}
};

class Node{
public:
    int value;
    int num_to;
    int num_from;
    listOfObjects<Node> *to;
    listOfObjects<Node> *from;

    Node(){
        value = -1;
        num_to = 0;
        num_from = 0;
        to = nullptr;
        from = nullptr;
    }

    bool operator ==(Node n1){
        return value==n1.value;
    } 

    void add_to_adjfrom(Node adj_node){
        if(from==nullptr){
            from = new listOfObjects<Node>(adj_node);
        }
        else{
            listOfObjects<Node> *x = from;
            while(x->next!=nullptr){
                x = x->next;
            }
            x->next = new listOfObjects<Node>(adj_node);
        }
        num_from++;
    }

    void add_to_adjto(Node adj_node){
        if(to==nullptr){
            to = new listOfObjects<Node>(adj_node);
        }
        else{
            listOfObjects<Node> *x = to;
            while(x->next!=nullptr){
                x = x->next;
            }
            x->next = new listOfObjects<Node>(adj_node);
        }
        num_to++;
    }

    void setvalue(int value){
        this->value = value;
    }

    int getvalue(){
        return value;
    }
};

class Graph{
public:
    // list of all similar node pairs
    int numNodes;
    int num_source_nodes;
    bool **similar_nodes;
    bool *sourceNode;
    ofstream graphFile;
    Node *nodes;

    Graph(string filename){
        cin >> numNodes;
        num_source_nodes = numNodes;

        nodes = new Node[numNodes];
        for(int i=0;i<numNodes;i++){
            nodes[i].setvalue(i+1);
        }

        graphFile.open(filename);

        similar_nodes = new bool*[numNodes];
        for(int i=0;i<numNodes;i++){
            similar_nodes[i] = new bool[numNodes];
        }

        for(int i=0;i<numNodes;i++){
            for(int j=0;j<numNodes;j++){
                similar_nodes[i][j] = false;
            }
        }

        sourceNode = new bool[numNodes];
        
        for(int i=0;i<numNodes;i++){
            sourceNode[i] = true;
        }

        int num1=0;
        int num2=0;

        // reading the directed edges from node1 to node2
        cin >> num1 >> num2;

        while(num1!=-1 && num2!=-1){
            //add edge from num1 to num2 first and then take input again
            if(sourceNode[num2-1]){
                sourceNode[num2-1] = false;
                num_source_nodes--;
            }
            nodes[num1-1].add_to_adjto(nodes[num2-1]);
            nodes[num2-1].add_to_adjfrom(nodes[num1-1]);
            cin >> num1 >> num2;
        }

        graphFile << "Source nodes:";
        for(int i=0;i<numNodes;i++){
            if(sourceNode[i]){
                graphFile << " " << i+1;
            }
        }
        graphFile << endl;
        graphFile << endl;

        cin >> num1 >> num2;

        while(num1!=-1 && num2!=-1){
            if(sourceNode[num1-1] && sourceNode[num2-1]){
                similar_nodes[num1-1][num2-1] = true;
            }
            cin >> num1 >> num2;
        }
    }

    void checkSimilarity();
    int DFS_fordepth(Node node,int level);
    void DFS_forsimilarity(Node node,listOfObjects<int> **levelarr,int level);
};

#endif