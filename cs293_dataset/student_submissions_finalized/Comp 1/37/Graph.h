#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <fstream>

#include <iostream>
#include <cstdlib>
using namespace std;
 
// Define the default capacity of the stack
#define SIZE 10

class listofnodes{
public:
  int index;
  listofnodes *next;
  listofnodes() : index(-1),next(nullptr){};
  listofnodes(int v) :index(v),next(nullptr){};
};


class Node
{
public:
  int value,nadjacent,time;
  
  listofnodes * adjacent,*last;
  Node() : value(0),nadjacent(0), time(-1),adjacent(nullptr),last(nullptr){}

};

class Edge{
public:
  int v1,v2;
  Edge() : v1(-1),v2(-1){};
  Edge(int a,int d): v1(a),v2(d){};
};
 

class TreeNode
{
public:
  int value;
  TreeNode *left,*right,*parent;
  TreeNode() : value(0), left(nullptr), right(nullptr) ,parent(nullptr){}
  TreeNode(int v): value(v), left(nullptr), right(nullptr) ,parent(nullptr){}
  
};

class BST
{
	TreeNode *root;



public:

	BST(){root=nullptr;}
	BST(TreeNode *root){this->root=root;}

  bool find(int value) {
      if(root==NULL)return false;
      TreeNode* curr = root;
      while(true){
        
          if(curr->value==value){
           return true;
          } else if(curr->value > value){
        
              if(curr->left==NULL){
                  return false;
              }else{
                  curr = curr->left;
              }
          }else{
              if(curr->right==NULL){
                  return false;
              }else{
                  curr = curr->right;
              }
          }
      }
      return false;
  }
  
  bool insert(int value) { 
    
      if(root == nullptr){
          root = new TreeNode(value);
          return true;
      }


      TreeNode *curr = root;
      while(true){

          if(value > curr->value){
              if(curr->right!=NULL){
                  curr = curr->right;
              }else{
                  curr->right = new TreeNode(value);
                  break;
                  
              }
          }else{
              
              if(curr->left!=NULL){
                  curr = curr->left;
              }else{
                  curr->left = new TreeNode(value);
                  break;
                  
              }
          }
      }

    return true;
  }
void printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->value<<')' << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
   

  
};

class Trees{
public:
  BST *tree;
  Trees *next;
  Trees() : tree(nullptr),next(nullptr){};
  Trees(BST* v) :tree(v),next(nullptr){};
};


class Graph
{
  int numNodes,nconnected;
  int numEdges;
  fstream graphFile;
  int * predecessor,*nvisited;
  bool * isincycle;
  Trees *trees;
  int *time1;
  Node *nodes;
  Edge *edges;

  
public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    nconnected=0;
    time1=new int[numNodes];
    trees=nullptr;
    numNodes = nNodes;
    numEdges = nEdges;
    isincycle= new bool[numNodes];
    predecessor= new int[numNodes];
    nvisited = new int[numNodes];
    edges=new Edge[nEdges];
    for(int i=0 ; i <numNodes; i++){
      isincycle[i]=false;
      predecessor[i]=-1;
      nvisited[i]=0;
    }
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);
      bool found=false;
      for(int i=0;i<countEdges ; i++){
        if((edges[i].v1 ==n1 && edges[i].v2 == n2  ) ||  (edges[i].v1 ==n2 && edges[i].v2 == n1  )){
          found=true;
          break;
        }
      }
      if(found) continue;
      edges[countEdges].v1=n1;
      edges[countEdges].v2=n2;
      if(nodes[n1].adjacent == nullptr){
        nodes[n1].adjacent=nodes[n1].last=new listofnodes(n2);
      }
      else{
        nodes[n1].last->next=new listofnodes(n2);
      }
      nodes[n1].nadjacent++;
      if(nodes[n2].adjacent == nullptr){
        nodes[n2].adjacent=nodes[n2].last=new listofnodes(n1);
      }
      else{
        nodes[n2].last->next=new listofnodes(n1);
      }
      nodes[n2].nadjacent++;

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }

    // Add appropriate code as necessary for your implementation
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void dfs(int curr,BST * tree,int last);
  void printResults();
};

#endif
