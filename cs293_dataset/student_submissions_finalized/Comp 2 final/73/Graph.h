#include <bits/stdc++.h>
#include <iostream>
using namespace std;
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class Node
{//nodes
    public:
    listOfObjects<int> *fromnodes;
    listOfObjects<int> *tonodes;
    listOfObjects<int> *similar;
    listOfObjects<int> *symsimilar;
    Node()
    {
        fromnodes=nullptr;
        tonodes=nullptr;
        similar=nullptr;
        symsimilar=nullptr;
    }
};

class DirectedGraph
{
    public:
    Node* nodes;
    bool* isSource;
    bool** similar;
    int num;
    bool *visited;
    listOfObjects< listOfObjects<int>* > *classes;
    DirectedGraph(int v);
    void AddEdge(int v,int u);
    void printSourcenode();
    void SimilarNode();
    bool isSimilar(int node1,int node2);
    void printsimlarpairs();
    void getclasses();
    void DFS(int v,listOfObjects<int> *l);
    void printclasses();
};
//by saran 210050036