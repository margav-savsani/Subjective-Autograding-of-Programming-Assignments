#include <iostream>
#include <fstream>

using namespace std;

struct myPair{
    int first;
    int second;

    myPair(){
        first = 0;
        second = 0;
    }

    myPair(int f, int s){
        first = f;
        second = s;
    }

    bool operator == (myPair obj){
        if ((first == obj.first) && (second == obj.second)) return true;
        return false;
    }

    friend ostream & operator << (ostream &out, const myPair &p);
};

ostream & operator << (ostream &out, const myPair &p){
    out<<"("<<p.first+1<<", "<<p.second+1<<")";
    return out;
}

template <class T>
struct LinkedListNode{
    T value;
    LinkedListNode* next;

    LinkedListNode(T val){
        value = val;
        next = nullptr;
    }
};

template <class T>
struct LinkedList{
    LinkedListNode<T>* head;
    int len;

    LinkedList(){
        head = nullptr;
        len = 0;
    }

    void insert(T val){
        LinkedListNode<T>* trav= head;
        if (head == nullptr) {
            head = new LinkedListNode<T>(val);
            len=1;
            return;
        }
        while (trav->next != nullptr){
            trav = trav->next;
        }
        trav->next = new LinkedListNode<T>(val);
        len++;
    }

    bool find(T val){
        LinkedListNode<T>* trav= head;
        while (trav != nullptr){
            if (trav->value == val){
                return true;
            }
            trav = trav->next;
        }
        return false;
    }

    void print(){
        LinkedListNode<T>* trav = head;

        if (head == nullptr){
            cout<<"Empty List"<<endl;
            return;
        }

        while (trav != nullptr){
            cout<<trav->value<<endl;
            trav = trav->next;
        }
    }
};

class Graph{

    public:
    
    int no_nodes;

    LinkedList<int> *arr_start;
    LinkedList<int> *arr_end;
    bool* source;
    bool** similar;
    bool** checked;
    int* visited;
    LinkedList<int> *arr_similar;
    LinkedList<myPair> edge_pair;
    LinkedList<myPair> queue_pair;

    Graph(int num_nodes){
        no_nodes = num_nodes;
        arr_start = new LinkedList<int>[no_nodes];
        arr_end = new LinkedList<int>[no_nodes];
        source = new bool[no_nodes];
        visited = new int[no_nodes];
        arr_similar = new LinkedList<int>[no_nodes];
        for (int i=0;i<no_nodes;i++){
            visited[i] = -1;
        }
        
        for (int i=0;i<no_nodes;i++){
            source[i] = true;
        }
        similar = new bool*[no_nodes];
        checked = new bool*[no_nodes];
        for (int i=0;i<no_nodes;i++){
            similar[i] = new bool[no_nodes];
            checked[i] = new bool[no_nodes];
        }
        for (int i = 0; i < no_nodes; i++) {
            for (int j = 0; j < no_nodes; j++) {
                similar[i][j] = false;
                checked[i][j] = false;
            }
        }
    }

    bool insert_edge(int source, int dest){
        if ((source == -1) && (dest == -1)) return false;
        if ((source > no_nodes) || (dest > no_nodes)) return false;
        if ((source < 1) || (dest < 1)) return false;
        arr_start[source-1].insert(dest-1);
        arr_end[dest-1].insert(source-1);
        return true;
    }

    void check_similar_nodes(int n1, int n2){
        checked[n1][n2] = true;
        checked[n2][n1] = true;
        LinkedList<int> l1 = arr_end[n1];
        LinkedList<int> l2 = arr_end[n2];
        LinkedListNode<int> *trav1 = l1.head;
        LinkedListNode<int> *trav2 = l2.head;
        while (trav1 != nullptr){
            bool found1 = false;
            while (trav2 != nullptr){
                if (similar[trav1->value][trav2->value]) found1 = true;
                trav2 = trav2->next;
            }
            if (found1 == false) return;
            trav2 = l2.head;
            trav1 = trav1->next;
        }
        trav1 = l1.head;
        trav2 = l2.head;
        while (trav2 != nullptr){
            bool found1 = false;
            while (trav1 != nullptr){
                if (similar[trav2->value][trav1->value]) found1 = true;
                trav1 = trav1->next;
            }
            if (found1 == false) return;
            trav1 = l1.head;
            trav2 = trav2->next;
        }
        similar[n1][n2] = true;
        similar[n2][n1] = true;
        queue_pair.insert(myPair(n1,n2));
        queue_pair.insert(myPair(n2,n1));
    }

    void check_similar_parents(myPair p){
        int prnt1 = p.first;
        int prnt2 = p.second;
        LinkedList<int> l1 = arr_start[prnt1];
        LinkedList<int> l2 = arr_start[prnt2];
        LinkedListNode<int> *trav1 = l1.head;
        LinkedListNode<int> *trav2 = l2.head;
        int n1,n2;
        while (trav1 != nullptr){
            while (trav2 != nullptr){
                n1 = trav1->value;
                n2 = trav2->value;
                if (!(checked[n1][n2])) check_similar_nodes(n1,n2);
                trav2 = trav2->next;
            }
            trav1 = trav1->next;
        }
    }

    void algo(){
        cout<<"Similar node pairs:";
        for (int i = 0;i<no_nodes;i++){
            if (arr_end[i].len == 1){
                myPair a = myPair(i,arr_end[i].head->value);
                queue_pair.insert(a);
            }
        }
        LinkedListNode<myPair>* trav_queue = queue_pair.head;
        while(trav_queue != nullptr){
            cout<<" "<<trav_queue->value;
            check_similar_parents(trav_queue->value);
            trav_queue = trav_queue->next;
        }
        cout<<endl;
    }

    void rec_DFS(int v, int i){
        visited[v] = i;
        LinkedListNode<int>* trav = arr_similar[v].head;
        while (trav != nullptr){
            if (visited[trav->value] == -1){
                rec_DFS(trav->value,i);
            }
            trav = trav->next;
        }
    }

    void collapse(){
        cout<<"Collapsed graph:"<<endl;
        cout<<endl;
        int no_comp = 0;
        LinkedListNode<myPair>* trav_queue = queue_pair.head;
        while (trav_queue != nullptr){
            if (trav_queue->value.first == trav_queue->value.second) {
                trav_queue = trav_queue->next;
                continue;
            }
            if (!(arr_similar[trav_queue->value.first].find(trav_queue->value.second))) arr_similar[trav_queue->value.first].insert(trav_queue->value.second);
            if (!(arr_similar[trav_queue->value.second].find(trav_queue->value.first))) arr_similar[trav_queue->value.second].insert(trav_queue->value.first);
            trav_queue = trav_queue->next;
        }
        for (int i=no_nodes;i>=0;i--){
            if (visited[i] == -1) {
                no_comp++;
                rec_DFS(i,i);
            }
        }
        cout<<no_comp<<":";
        for (int i=0;i<no_nodes;i++){
            if (i == visited[i]) cout<<" "<<i+1;
        }
        cout<<endl;
        LinkedList<myPair> comp_pair;
        LinkedListNode<myPair>* trav_edge = edge_pair.head;
        while (trav_edge != nullptr){
            int a = visited[trav_edge->value.first];
            int b = visited[trav_edge->value.second];
            if (a == b) {
                trav_edge = trav_edge->next;
                continue;
            }
            if (!(comp_pair.find(myPair(a,b)))){
                comp_pair.insert(myPair(a,b));
            }
            trav_edge = trav_edge->next;
        }

        LinkedListNode<myPair>* trav_comp = comp_pair.head;
        while (trav_comp != nullptr){
            cout<<trav_comp->value.first+1<<" "<<trav_comp->value.second+1<<endl;
            trav_comp = trav_comp->next;
        }

    }

};