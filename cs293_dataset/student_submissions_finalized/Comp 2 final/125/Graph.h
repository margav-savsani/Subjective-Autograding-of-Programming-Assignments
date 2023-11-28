#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class Node;
class listOfNodes{
  public:
    bool allowed;
    listOfNodes* head;
    Node* node;
    listOfNodes* next;
    listOfNodes* prev;
    listOfNodes(Node* x, listOfNodes* hd){
      allowed = true;
      next = prev = NULL;
      head = hd;
      node = x;
    }
};

class Node {
 public:
  int value;
  int collapsed_to;
  listOfNodes* to_edges;
  listOfNodes* from_edges;
  Node(){
    value = -1;
    collapsed_to = -1;
    to_edges = NULL;
    from_edges = NULL;
  }
  bool insert_to(Node *x){
    if(to_edges==NULL){
      to_edges = new listOfNodes(x, NULL);
      to_edges->head = new listOfNodes(x, NULL);
      return true;
    }
    listOfNodes* y = to_edges->head;
    while(y!=NULL){
      if(y->node->value==x->value) return false;
      y = y->next;
    }
    to_edges->next = new listOfNodes(x, to_edges->head);
    to_edges->next->prev = to_edges;
    if(to_edges->prev==NULL){
      to_edges->head->next = to_edges->next;
    }
    to_edges = to_edges->next;
    return true;
  }
  bool insert_from(Node *x){
    if(from_edges==NULL){
      from_edges = new listOfNodes(x, NULL);
      from_edges->head = new listOfNodes(x, NULL);
      return true;
    }
    listOfNodes* y = from_edges->head;
    while(y!=NULL){
      if(y->node->value==x->value) return false;
      y = y->next;
    }
    from_edges->next = new listOfNodes(x, from_edges->head);
    from_edges->next->prev = from_edges;
    if(from_edges->prev==NULL){
      from_edges->head->next = from_edges->next;
    }
    from_edges = from_edges->next;
    return true;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  int* visited;
  int* sources;
  int** similar;
  Node *nodes;
  ofstream file;
  public:
  Graph() {
    file.open("outgraph.txt");
    cin >> numNodes;
    nodes = new Node[numNodes];
    visited = new int[numNodes];
    sources = new int[numNodes];
    similar = new int*[numNodes];
    for(int i = 0; i < numNodes; i++){
      similar[i] = new int[numNodes];
    }
    for(int i = 0; i < numNodes; i++){
      nodes[i].value = i;
    }

    int n1, n2;
    int countEdges = 0;
    
    while(true){
      cin >> n1 >> n2;
      if(n1==-1) break;
      if(!nodes[n1-1].insert_to(&nodes[n2-1])) continue;
      nodes[n2-1].insert_from(&nodes[n1-1]);
      countEdges++;
    }
    numEdges = countEdges;

    for(int i = 0; i < numNodes; i++){
      for(int j = 0; j < numNodes; j++){
        similar[i][j] = -1;
        if(nodes[i].from_edges==NULL&&nodes[j].from_edges==NULL) similar[i][j] = 0;
      }
    }

    while(true){
      cin >> n1 >> n2;
      if(n1==-1) break;
    similar[n1-1][n2-1]=1;
    }

  }
      
  ~Graph() {
    file.close();
    delete[] nodes;
  }

  void getSourceNodes();
  void computeSimilarity();
  int recursiveComputeSimilarity(int i, int j);
  void printSimilar();
  void collapse();
  int DFS_Similar(int x);
  void DFS_Collapse(int x, int mx);
};

#endif
