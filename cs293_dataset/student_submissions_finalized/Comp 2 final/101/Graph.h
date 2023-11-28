#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Node;
class List;
class ListOfNodes;
class List;

//Node object for list
class ListOfNodes{
    public:
    Node* value;
    ListOfNodes* next;
    ListOfNodes(Node *v) : value(v), next(nullptr) {};
    ListOfNodes(Node *v, ListOfNodes * n) : value(v), next(n) {};

};

//Linked List
class List{
    public:
    ListOfNodes* start;
    ListOfNodes* end;
    int size;
    List() : start(nullptr), end(nullptr), size(0){};
    List(ListOfNodes *N) : start(N), end(N),size(1){};
    bool insert(ListOfNodes *N){
        if ( start == nullptr ){
            start = new ListOfNodes(N->value);
            end = new ListOfNodes(N->value);
            start = N;
            end = N;
            size++;
        }
        else{
            end->next = new ListOfNodes(N->value);
            end->next = N;
            end = end->next;
            size++;
        }
        return true;
    }
    bool insert(Node *N){
        ListOfNodes *temp = new ListOfNodes(N);
        insert(temp);
        return true;
    }
};

//Node class for Graph
class Node{
    public:
    bool isSimilar;
    int id;
    List *adjList;
    List *similarList;
    List *parentList;
    List *similarConnections;
    int component_number = 0;
    int collapsedId = 0;
    Node() : id(0), isSimilar(false){
        parentList = new List();
        adjList = new List();
        similarList = new List();
        similarConnections = new List();
    }
    Node(int i) : id(i), isSimilar(false){ 
        parentList = new List();
        adjList = new List();
        similarList = new List();
        similarConnections = new List();
    };
};

//Graph class
class Graph{
    public:
        int nNodes;
        int nEdges;
        Node* nodes;
        bool* isSource;
        bool* isSink;
        Graph(int n1, int n2);
        Graph(int n1);
        bool checkSimilar(int value1, int value2);
        void makeSimilar(int value1, int value2);
        bool customSimilarity(int value1, int value2);
        void singleSimilarity();
        bool updateSimilarity(int value1, int value2);
        int max ( int a , int b);
        int simDFS(Node *Source, bool* hasVisited, int seriesNumber);

    //Defined a subclass to store edges of collapsed graph
    struct pair{
        int v1;
        int v2;
        pair() : v1(0) , v2(0) {};
        pair(int a, int b) : v1(a) , v2(b) {};
        bool operator == (struct pair p){
            if( v1 == p.v1 && v2 == p.v2 ){
                return true;
            }
            else{
                return false;
            }
        }
    };

    //Node of Linked list of edges
    class pairNode{
        public:
        struct pair *value;
        pairNode *next;
        pairNode(){
            value = nullptr;
            next = nullptr;
        }
        pairNode(struct pair *v){
            value = new struct pair();
            value = v;
        }
    };

    //Linked List of edges
    class pairNodeList{
        public:
        pairNode* start;
        pairNode* end;

        pairNodeList() : start(nullptr) , end(nullptr) {};

        //Inserts only if pair is not present earlier
        bool insert(int v1, int v2){
            struct pair *temp = new struct pair(v1,v2);
            
            if(start == nullptr){
                start = new pairNode(temp);
                end = start;
                return true;
            }

            pairNode*checker = start;
            while(checker != nullptr ){
                if (*(checker->value)==*temp){
                    return false;
                }
                checker = checker->next;
            }
            end->next = new pairNode(temp);
            end = end->next;
            return true;
        }
        
        //Prints the linked list
        void print(){
            pairNode*printer = start;
            while (printer!=nullptr){
                cout << printer->value->v1 << " " << printer->value->v2 << endl;
                printer = printer->next;
            }
        }

    };
    void printEdges();
    int similarDFS();
};