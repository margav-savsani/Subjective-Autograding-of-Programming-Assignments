#include<iostream>
using namespace std;




template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

struct Node{
    int value;
    listOfObjects<Node> *toNodes;
    listOfObjects<Node> *fromNodes;
    int numToNodes;
    int numFromNodes;
    Node(){
        value = -1;
        toNodes = fromNodes = nullptr;
        numFromNodes= numToNodes = 0;
    }
    Node(int k){
        value=k;
        toNodes=nullptr;
        fromNodes=nullptr;
        numFromNodes=0;
        numToNodes=0;
    }
};

void add(listOfObjects<Node>* &head, Node n) {
    listOfObjects<Node> *newObject;
    newObject = new listOfObjects<Node>(n);
    if(head==nullptr){
        head=newObject;
    }
    else{
        listOfObjects<Node> *tail;
        tail = head;
        while(tail->next!=nullptr){
            tail = tail->next;
        }
        tail->next = newObject;
    }
}

void printList(listOfObjects<Node> *head){
    if(head==nullptr) {
        return;
    }
    else{
        listOfObjects<Node> *tail;
        tail = head;
        while(tail!=nullptr){
            cout<<tail->object.value<<endl;
            tail=tail->next;
        }
    }
    
}

class Graph{
    
    int numNodes;
    //int numEdges;
    public:
    Node* nodes;
    Graph(int N){
        numNodes=N;
        //numEdges=M;
        nodes = new Node[N];
        for(int i=0;i<numNodes;i++){
            nodes[i].value=i+1;
            nodes[i].numToNodes=0;
            nodes[i].numFromNodes=0;
            nodes[i].toNodes=nullptr;
            nodes[i].fromNodes=nullptr;
        }
    }
    int get_numNodes(){
        return numNodes;
    }
    // int get_numEdges(){
    //     return numEdges;
    // }
    void getValues(){
        for (int i=0;i<numNodes;i++){
            cout<<nodes[i].value<<endl;
        }
    }

    void addEdge(int a, int b){
        add(nodes[a-1].toNodes,nodes[b-1]);
        nodes[a-1].numToNodes++;
        add(nodes[b-1].fromNodes,nodes[a-1]);
        nodes[b-1].numFromNodes++;
    }

    void getSourceNodes(){
        for(int i=0;i<numNodes;i++){
            if(nodes[i].numFromNodes==0){
                cout<<nodes[i].value<<" ";
            }
        }
    }

    void getSinkNodes(){
        for(int i=0;i<numNodes;i++){
            if(nodes[i].numToNodes==0){
                cout<<nodes[i].value<<endl;
            }
        }
    }


};


