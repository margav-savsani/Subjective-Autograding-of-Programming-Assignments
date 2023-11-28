#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <iostream>
#include <fstream>

using namespace std;

class TreeNode{
public:
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  int value;
  TreeNode(int num){
    value = num;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  TreeNode(){
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

class BST
{
  TreeNode *root; 

public:
  BST(TreeNode *node) { this->root = node; }
  BST(){this->root =nullptr;}
  bool checkroot();
  bool insert(int value){
    // if (find(value)){
    //   return false;
    // }
    TreeNode *A = new TreeNode(value);
    TreeNode *y = nullptr;
    TreeNode *x = root;
    while (x != nullptr){
        y = x;
        if (value < x->value){
          x = x->left;
        }
      else{ x = x->right;}
    }
    A->parent = y;
    if (y == nullptr){
      root = A;
    }
    else if (A->value < y->value){
      y->left = A;
    }
    else{
      y->right = A;
    }
    return true;
  }
void printBST(const string& prefix, bool isLeft=false);

};

class Node{

public:
  int value;
  int visit1;
  int visit2;
  int cvisit;
  int *adjacency;
  int *adj;
  Node(){
    value = 0;
    visit2 = 0;
    visit1 = 0;
  }
  Node(int num){
    value = num;
    visit2 = 0;
    visit1 = 0;
  }
  // insert other fields and methods as appropriate
};

class Edges{
  public:
    int taken;
    Node N1;
    Node N2;
    // Edges(){
    //   taken = 0;
    //   N1.value = 0;
    //   N2.value = 0;
    // }
};

class Graph{
public:
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  Edges *Edge; 
  BST **Treelist;
  int connected;
  // Add appropriate fields as necessary for your implementation
  Graph(int nNodes, int nEdges, string gFileName){
    Treelist = new BST*[nNodes];
    for(int i=0;i<nNodes;i++){
      Treelist[i] = new BST();
    }
    connected=0;
    numNodes = nNodes;
    numEdges = nEdges;
    Edge = new Edges[nEdges];
    for(int i=0;i<nEdges;i++){
      Edge[i].taken=0;
    }
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()){
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr){
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++){
      nodes[i].value = i + 1;
      nodes[i].visit1 = 0;
      nodes[i].visit2 = 0;
      nodes[i].cvisit = 0;
      nodes[i].adjacency = new int[nEdges];
      nodes[i].adj = new int[nEdges];
      for (int j=0;j<numNodes;j++){
          nodes[i].adjacency[j] = 0;
      }
      for (int j=0;j<numNodes;j++){
          nodes[i].adj[j] = 0;
      }
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges){
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
        if(n1 != n2){
          int check = 0;
          for(int i=0;i<numEdges;i++){
             if((Edge[i].N1.value == n1 && Edge[i].N2.value == n2) || (Edge[i].N1.value == n2 && Edge[i].N2.value == n1)){
              check++;
              break;
             }
          }
          if(check ==0){
            Node Nx;
            Node Ny;
            for(int j=0;j<numNodes;j++){
                if(nodes[j].value==n1){
                  nodes[j].adjacency[n2]++;
                  nodes[j].adj[n2]++;
                  Nx = nodes[j];
                }
            }
            for(int j=0;j<numNodes;j++){
                if(nodes[j].value==n2){
                  nodes[j].adjacency[n1]++;
                  nodes[j].adj[n1]++;
                  Ny = nodes[j];
                }
            }
            int p=0;
            while(Edge[p].taken!=0){
              p++;
            }
            Edge[p].N1 = Nx;
            Edge[p].N2 = Ny;
            Edge[p].taken = 1;
            countEdges++;
          }
          graphFile << n1 + 1 << " " << n2 + 1 << endl;
        }

    
    }

    // Add appropriate code as necessary for your implementation
  }

  ~Graph(){
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    delete[] Edge;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  
  void modifiedDFS();
  void loopDFS(Node *node, Node *parent, BST *tree);
  void printResults();
  bool checkadjacency(int *adjacency,int *adj);
};

#endif
