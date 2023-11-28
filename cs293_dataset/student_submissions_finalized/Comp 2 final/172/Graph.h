
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class listOfObjects {
    public:
    T object;
    listOfObjects<T> *next;
    listOfObjects(T initValue) {object = initValue; next =nullptr;}
    listOfObjects(){}
    ~listOfObjects() {;}
};

class Node {
    public:
    int value;
    listOfObjects<Node*>* incoming;
    listOfObjects<Node*>* outgoing;
    Node(){}
    Node(int value){
        this->value=value;
    }
  // insert other fields and methods as appropriate
};

class Similar_Nodes{
    public:
    Node* node_1;
    Node* node_2;
    Similar_Nodes(int value1,int value2){
        node_1=new Node(value1);
        node_2=new Node(value2);
    }
};

class Graph {
    int numNodes;
    listOfObjects<Node*>* sourceNodes;
    listOfObjects<int>* collapsed_nodes;  // nodes after collapsing graph
    listOfObjects<Similar_Nodes*>* similarnodes; // linked list of similar nodes
    listOfObjects<Similar_Nodes*>* directed_edges;  // edges in collapsed graph
    listOfObjects<Similar_Nodes*>* final_list;      // list of similar nodes in closure 
    // Add appropriate fields as necessary for your implementation
    
    public:
    Node* nodes;
    bool* visited;

    Graph(int nNodes) {
        collapsed_nodes=nullptr;
        directed_edges=nullptr;
        similarnodes=nullptr;
        final_list=similarnodes;
        numNodes = nNodes;
        sourceNodes=nullptr;
        nodes = new Node[numNodes];
        if (nodes == nullptr) {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
        }

        for (int i = 0; i < numNodes; i++) {
            nodes[i].value = i+1;
        }

        visited=new bool[numNodes];
        for(int i=0; i<numNodes;i++){
            visited[i]=false;
        }
    }

    void makeEdge(int n1,int n2);    // forms a directed edge from n1 to n2
    void DFS(int starting_vertex);
    void callDFS();
    void PrintSourceNodes(string filename);

    void similar_type1(int n1, int n2){    // adds nodes which are similar by criteria 1 to similarnodes list
        if(similarnodes==nullptr){
            similarnodes=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,n2));
        }
        else{
            listOfObjects<Similar_Nodes*>* a=similarnodes;
            while(similarnodes->next!=nullptr){
                similarnodes=similarnodes->next;
            }
            similarnodes->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,n2));
            similarnodes=a;
        }
    }

    void similar_type2();  // adds nodes which are similar by criteria 2 to similarnodes list
    void similar_type3();  // adds nodes which are similar by criteria 3 to similarnodes list
    bool check_similar(int n1, int n2);    // checks if nodes n1 and n2 are similar by criteria 2
    bool isTransitive(int n1, int n2,listOfObjects<int>* intlist);   // checks if nodes n1 and n2 are similar by transitive property
    listOfObjects<listOfObjects<int>*>* collapsing_nodes();  // function which collapses nodes and returns the partitioned list
    void PrintSimilarNodes(string filename); // prints the similarnodes in output file
    bool ispresent(int n1, int n2);  // checks if n1 and n2 is present in final_list
    void printCollapsedNodes(string filename);  // prints the nodes in collapsed graph and also edges in it
};
      

