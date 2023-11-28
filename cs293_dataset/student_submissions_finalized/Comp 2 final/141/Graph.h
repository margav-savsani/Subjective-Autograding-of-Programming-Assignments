#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <cassert>


struct Edge
{
  int node1, node2;

  Edge(){
    node1 = 0; 
    node2 = 0;
  }

  Edge(int a, int b) {
    node1 = a; node2 = b;
  }

  bool operator==(Edge b) {
    return (node1 == b.node1 && node2 == b.node2);
  }
};



class Node
{
public:
  // Assumption : Default value is set to 0 
  int value;

  // adjacency list 
  int* outadjacency;
  int* inadjacency;   
  int maxcount;
  int incurcount;
  int outcurcount;

  Node(int value, int maxcount){
    this->value = value;
    incurcount = 0; 
    outcurcount = 0;
    outadjacency = new int[maxcount];
    inadjacency = new int[maxcount];
    this->maxcount = maxcount;
  }

  void addoutadjacent(int value) {
    
    // adds an outedge from this node to the input value
    // this ---> value
    outadjacency[outcurcount] = value;
    outcurcount ++ ;
  }

  void addinadjacent(int value) {
  
    // Adds an inedge from the value to this node
    // this <--- value

    inadjacency[incurcount] = value;
    incurcount ++ ;
  }

  bool operator== (Node n) {
    if (this->value == n.value) {return true;}
    else return false;
  }
};

class Graph
{
  int numNodes;
  bool** edgematrix;
  bool** similar;
  Edge* similaredge;
  int simcount;
  Node **nodes;
  Edge* prospectsinit;
  int countinit;
  Edge* prospects;
  int countprospect;
  int* merged;
  fstream graphFile;

  void processprospects(int node1, int node2);

public:
  Graph(string gFileName)
  {
    /*
    Input format : 
    numNodes
    DirectedEdge1_source DirectedEdge1_target
    DirectedEdge2_source DirectedEdge2_targer
    ...
    -1 -1
    Pair1 of similar source nodes
    Pair2 of similar source nodes
    ...
    -1 -1
    */
    graphFile.open(gFileName, ios::out);

    cin >> numNodes ;
    prospectsinit = new Edge[numNodes*numNodes];
    prospects = new Edge[numNodes*numNodes*numNodes];
    merged = new int[numNodes];
    similar = new bool*[numNodes];
    similaredge = new Edge[numNodes*numNodes];
    edgematrix = new bool*[numNodes];
    simcount = 0;
    for (int i = 0; i < numNodes; i++) {similar[i] = new bool[numNodes]; edgematrix[i] = new bool[numNodes];}
    // Initialising all Nodes 
    nodes = new Node*[numNodes];
    for (int i = 0; i < numNodes; i++) {
      nodes[i] = new Node(i+1, numNodes);
    }

    for (int i = 0; i < numNodes; i++) merged[i] = 0;

    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < numNodes; j++) {
        similar[i][j] = 0; 
        edgematrix[i][j] = 0;
      }
    }

    int numEdges = 0; 
    int source, target;

    while (cin >> source >> target) {
      if (source == -1 && target == -1) {
        break;
      }

      // Pair of directed edges stored in source and target
      edgematrix[source-1][target-1] = 1;
      nodes[source-1]->addoutadjacent(target);
      nodes[target-1]->addinadjacent(source);
      numEdges++;
    }

    // -1 -1 detected : adding pairs of similar source nodes
    int node1, node2; 
    countprospect = 0;
    countinit = 0;
    while (cin >> node1 >> node2) {
      if (node1 == -1 && node2 == -1) {
        break;
      }
      // setting the value of that relation as TRUE. 
      similar[node1-1][node2-1] = 1;
      
      // add this edge in prospects. (in order to start recursion)
      // Once all source edges are added, "DFS" type logic can work. 
      prospectsinit[countinit] = Edge(node1, node2);
      countinit ++ ;
    }

    // Processing all the prospects : 
    /*
    1. Iterating over all source nodes that are given to be similar
    2. Calling prospect function on them
    3. Preprocessing is now done. 
    */

    for (int i = 0; i < countinit; i++) {
      processprospects(prospectsinit[i].node1, prospectsinit[i].node2);
    }

  }

  ~Graph()
  {
    delete[] nodes;
  }

  void printsourcenodes();
  void printsimilarnodes();
  void printcollapsed();

  bool checksimilar(int node1, int node2);

  void printResults();

};

#endif
