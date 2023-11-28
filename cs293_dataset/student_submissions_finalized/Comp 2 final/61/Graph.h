#ifndef GRAPH_BST_H
#define GRAPH_BST_H

using namespace std;

class Graph
{
   bool **edges;
   bool **similar;
   bool* source;
   int numNodes;
   bool* exist;
public:
  Graph(int nNodes)
  {
    numNodes=nNodes;
    exist= new bool[numNodes];
    source= new bool[numNodes];
    edges=new bool*[numNodes];
    similar=new bool*[numNodes];

    for (int i = 0; i < numNodes; i++)
    {
      edges[i]=new bool[numNodes];
      similar[i]=new bool[numNodes];
      source[i]=true;
      exist[i]=true;
    }
    for(int i=0;i<numNodes;i++){
      for(int j=0;j<numNodes;j++){
        edges[i][j]=false;
        similar[i][j]=false;
      }
    }
  }
  ~Graph(){}

  void addEdge(int src, int dest);
  void printSrcNodes();
  void printSimilar();
  void print();
  void print_collapsed();
  void processSimilar();
  void addSimilar(int node1,int node2);
  bool checkSimilar(int n1,int n2);
  void collapse();
  void createEquivalence();
};

#endif
