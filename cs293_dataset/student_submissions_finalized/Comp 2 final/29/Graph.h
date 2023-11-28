#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#include <iostream>
#include <utility>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

// LinkList Class
template <typename T>
class Linklist {
   public:
    T object;
    Linklist* next;
    Linklist* prev;

    Linklist() {
        next = nullptr;
        prev = nullptr;
    }
    ~Linklist() {
        if (this->next != nullptr) delete this->next;
    }
};

// This function will add a new elemet at the beginning of a link list
template <typename T>
void addLinklist(Linklist<T>*& L, T N) {
    if (L == nullptr) {  // if link list is null then create
        L = new Linklist<int>();
        L->object = N;
        return;
    }
    L->prev = new Linklist<int>();  // insert
    L->prev->object = N;            // set value
    L->prev->next = L;
    L = L->prev;  // update pointer
}

// check if a value is please in a link list or not
template <typename T>
bool isInLinklist(Linklist<T>* L, T v) {
    if (L == nullptr) return false;  // if linklist is null then return false
    Linklist<int>* curr = L;
    while (curr != nullptr) {
        if (curr->object == v) return true;  // if exist then return true
        curr = curr->next;
    }
    return false;
}

// return size of a linklist
template <typename T>
int sizeLinklist(Linklist<T>* L) {
    int s = 0;
    if (L == nullptr) return s;
    Linklist<int>* curr = L;
    while (curr != nullptr) {
        curr = curr->next;
        s++;
    }
    return s;
}

// Node class
class Node {
   public:
    int collapseTo;
    Linklist<int>* adjacency;
    Linklist<int>* incoming;
    Linklist<int>* similarNodes;

    Node() {}                                                        // default constructor
    void addAdjacent(int N) { addLinklist(adjacency, N); }           //  add to adjacency list
    void addIncoming(int N) { addLinklist(incoming, N); }            //  add to incoming nodes list
    void addSimilar(int N) { addLinklist(similarNodes, N); }         // add to similar nodes list
    bool isadjacent(int v) { return isInLinklist(adjacency, v); }    // check if a node is in adjacent or not
    bool isSimilar(int v) { return isInLinklist(similarNodes, v); }  // check if a node is in similar or not
    bool isSource() { return (incoming == nullptr); }                // check if this node is a source or not
    ~Node() {                                                        // default destructor
        delete adjacency;
        delete similarNodes;
        delete incoming;
    }
};

// swap two values
void Exchange(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

// Graph class
class Graph {
   public:
    int numNodes;            // store number of nodes
    int NodesAfterCollapse;  // number of nodes after collapse
    fstream f;               // file to print results
    Node* nodes;             // nodes

    // default constructor
    Graph(int numNodes) {
        this->numNodes = numNodes;
        this->NodesAfterCollapse = numNodes;
        nodes = new Node[numNodes];
        for (int i = 0; i < numNodes; i++) {
            nodes[i].collapseTo = i;  // set all collapseTo inself
        }
        f.open("outgraph.txt", ios::out);
    }

    // take input from user
    void takeInput() {
        while (true) {
            int a, b;
            cin >> a >> b;
            if (a == -1 and b == -1) break;
            nodes[a - 1].addAdjacent(b - 1);  // store to adjacency nodes
            nodes[b - 1].addIncoming(a - 1);  // store to incoming nodes
        }
        while (true) {
            int a, b;
            cin >> a >> b;
            if (a == -1 and b == -1) break;
            if (nodes[a - 1].isSource() and nodes[b - 1].isSource()) {
                nodes[a - 1].addSimilar(b - 1);
            }
        }
    }

    // print Source nodes
    void printSource() {
        f << "Source nodes:";
        for (int i = 0; i < numNodes; i++) {
            if (nodes[i].incoming == nullptr) {
                f << " " << i + 1;
            }
        }
        f << endl << endl;
    }

    // add to similar nodes list
    void Similar(int a, int b) {
        nodes[a].addSimilar(b);
        nodes[b].addSimilar(a);
    }

    // check if a,b is similar or not
    bool isSimilar(int a, int b) {
        if (nodes[a].isSimilar(b)) return true;  // if exist in similar list then return true
        if (nodes[b].isadjacent(a) and sizeLinklist(nodes[a].incoming) == 1) {  // if only one incoming code
            nodes[a].addSimilar(b);                                             // update similar list
            return true;
        }

        // for all parent of a there exist a similar node in b then return true
        if (!(nodes[a].isSource() or nodes[b].isSource())) {
            Linklist<int>* A = nodes[a].incoming;
            while (A != nullptr) {
                Linklist<int>* B = nodes[b].incoming;
                bool isExist = false;
                while (B != nullptr) {
                    if (isSimilar(A->object, B->object)) {
                        isExist = true;
                        break;
                    }
                    B = B->next;
                }
                if (!isExist) return false;
                A = A->next;
            }

            A = nodes[b].incoming;
            while (A != nullptr) {
                Linklist<int>* B = nodes[a].incoming;
                bool isExist = false;
                while (B != nullptr) {
                    if (isSimilar(A->object, B->object)) {
                        isExist = true;
                        break;
                    }
                    B = B->next;
                }
                if (!isExist) return false;
                A = A->next;
            }
            Similar(a, b);
            return true;
        }
        return false;
    }

    // print similar nodes
    void printSimilar() {
        f << "Similar node pairs:";
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (isSimilar(i, j)) {
                    f << " (" << i + 1 << ", " << j + 1 << ")";
                }
            }
        }
        f << endl << endl;
    }

    // find final collapseTo value
    int getValue(int a) {
        while (nodes[a].collapseTo != a) a = nodes[a].collapseTo;
        return a;
    }

    // extend adjacency list
    void ExtendAdjacency(int i, int j) {
        Linklist<int>* A = nodes[i].adjacency;
        Linklist<int>* C = nullptr;
        while (A != nullptr) {
            int t = getValue(A->object);
            if (t != j and !isInLinklist(C, t)) {
                addLinklist(C, t);
            }
            A = A->next;
        }
        A = nodes[j].adjacency;
        while (A != nullptr) {
            int t = getValue(A->object);
            if (j != t and !isInLinklist(C, t)) addLinklist(C, t);
            A = A->next;
        }
        delete A;
        nodes[j].adjacency = C;
    }

    // delete if same node is repeated and replace with final collapse value
    void UpdateAdjacency(int i) {
        Linklist<int>* A = nodes[i].adjacency;
        Linklist<int>* C = nullptr;

        while (A != nullptr) {
            int t = getValue(A->object);
            if (t != i and !isInLinklist(C, t)) {
                addLinklist(C, t);
            }
            A = A->next;
        }
        delete nodes[i].adjacency;
        nodes[i].adjacency = C;
    }

    // ExtendAdjacency node of bigger node and collape smaller one
    void C(int a, int b) {
        int smallNode = getValue(a), bigNode = getValue(b);
        if (smallNode == bigNode) return;
        if (smallNode > bigNode) Exchange(smallNode, bigNode);
        ExtendAdjacency(smallNode, bigNode);
        nodes[smallNode].collapseTo = bigNode;
    }

    // collapse similar nodes and print final graph
    void Collapse() {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (i != j and nodes[i].isSimilar(j)) C(i, j);
            }
        }
        int newnodes = 0;
        Linklist<int>* NewNodes = nullptr;  // store new nodes after collapse
        for (int i = numNodes - 1; i > -1; i--) {
            if (nodes[i].collapseTo == i) {
                addLinklist(NewNodes, i);
                newnodes++;
            }
        }

        // print new graph
        f << "Collapsed graph:\n" << endl;
        f << newnodes << ":";
        Linklist<int>* curr = NewNodes;
        while (curr != nullptr) {
            f << " " << curr->object + 1;
            curr = curr->next;
        }
        f << endl;
        curr = NewNodes;
        while (curr != nullptr) {
            UpdateAdjacency(curr->object);  // update adjacency nodes
            Linklist<int>* adj = nodes[curr->object].adjacency;
            while (adj != nullptr) {
                f << curr->object + 1 << " " << adj->object + 1 << endl;
                adj = adj->next;
            }
            curr = curr->next;
        }
        f << endl;
    }

    ~Graph() { delete[] nodes; }
};
#endif