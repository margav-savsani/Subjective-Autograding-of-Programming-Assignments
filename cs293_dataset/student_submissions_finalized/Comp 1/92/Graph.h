#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include<list>
#include<algorithm>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
class Node {
 public:
  int value;
  Node* p;
  Node* l;
  Node* r;
  Node(){value=0;}
  Node(int v){value=v;l=NULL;r=NULL;p=NULL;}
  // insert other fields and methods as appropriate
};

class BST {
 public:
  Node *root;
  void insert(int v) {
        Node *y;y=NULL;
        Node *x;x=root;
        Node *n;n=new Node(v);
        while(x!=NULL){
         y=x;
         if(v<x->value){x=x->l;}
         else{x=x->r;}
        }
         n->p=y;
         if(y==NULL){root=n;return;}
         else if(v<y->value){
            y->l=n;return;}
            else{y->r=n;return;}      }
// Return True, if the ticket with given attributes is found, false otherwise
bool find(int v) {
     Node *node;
    node=root;
    if(root==NULL){
        return 0;
    }
    if(node->value==v){//if it is matched with given data then it returns true
        return 1;
    }
    if(v<node->value){BST left(node->l);//using recursive functions to find in left or right subbranch
       return left.find(v);
    }
    else{BST right(node->r);//right subbranch
        return right.find(v);
    }
 }
  void printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        Node *curr = root;
        root = root->l;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->r;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
  BST(){root=NULL;}
  BST(Node *x){root=x;}
  BST(int v){root->value=v;root->l=NULL;root->r=NULL;root->p=NULL;}
};
int count1=0;
int count2=0;
list<int> dfsorder;
class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  list<int> *adjLists;//adjacency list array in which each element is list of integers
  int *count;//for modified dfs to check number of times the node has been visited

  Node *nodes;
  // Add appropriate fields as necessary for your implementation
  BST Tree;
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    adjLists=new list<int>[numNodes];
    count=new int[numNodes];
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if(find(adjLists[n1].begin(),adjLists[n1].end(),n2)==adjLists[n1].end()&&find(adjLists[n2].begin(),adjLists[n2].end(),n1)==adjLists[n2].end()){
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;}
      if(find(adjLists[n1].begin(),adjLists[n1].end(),n2)==adjLists[n1].end()){
        adjLists[n1].push_front(n2);
      }
      if(find(adjLists[n2].begin(),adjLists[n2].end(),n1)==adjLists[n2].end()){
        adjLists[n2].push_front(n1);
      }
    }

    // Add appropriate code as necessary for your implementation
  }
   void DFS(int vertex){
    count[vertex]++;
  if(count[vertex]==1){count1++;}
  else {count1--;count2++;}
  list<int> adjList=adjLists[vertex];
  dfsorder.push_front(vertex);
  Tree.insert(vertex);
  list<int>::iterator i;
  for(i=adjList.begin();i!=adjList.end();++i){
    if(count[*i]!=2 && *i!=vertex){DFS(*i);}
  }

  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
};

#endif
