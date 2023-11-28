#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class Node
{
public:
  int value;
  bool* outadjacency; //stores indices of outgoing edges
  bool* inadjacency;  //stores indices of incoming edges
  bool* sim;  //stores indices of similar nodes
  bool source = true; // checks whether a node is source
  bool change = false;  // checks if the value of node is changed
};

class Graph
{
  public:
  int numNodes;
  Node *nodes;
  ofstream outfile;
  Graph(int nNodes){  //default constructor
    outfile.open("outGraph.txt");
    numNodes=nNodes;
    nodes = new Node[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      nodes[i].outadjacency = new bool[nNodes];
      nodes[i].inadjacency = new bool[nNodes];
      nodes[i].sim = new bool[nNodes];
      for(int j = 0; j < nNodes; j++){
        nodes[i].sim[j]=false;
        nodes[i].outadjacency[j]=false;
        nodes[i].inadjacency[j]=false;
      }
      nodes[i].value = i + 1;
    }
    
  }
  void addedge(int m,int n); //adds edge
  void similar(int m,int n); // changes the similarity status
  void findsimilar(); // finds similarity
  bool case2(int m,int n);  // checks case2 of the similarity
  void collapsedgraph(); // prints the collapsed graph
  void printsource(); // prints the source nodes
  void changeval(int a, int b); // changes the value of the node while collapsing
};