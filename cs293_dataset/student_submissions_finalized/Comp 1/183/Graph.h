#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


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
class Node {
 public:
  int value;
  int visited=0;
  int arr=0;
  Node *left=NULL;	
  Node *right=NULL;
  Node *parent=NULL;
  listOfObjects<int> *adjacentNodes=NULL;
  void addNeighbour(int v) {
    listOfObjects<int> *x=adjacentNodes;
    if(x==NULL){adjacentNodes=new listOfObjects <int> (v);}
    else{
      while(x->next!=NULL){
        x=x->next;
      }
      x->next=new listOfObjects <int> (v);
    }
  }
  // insert other fields and methods as appropriate
};
class BST {
  public:
  Node *root=NULL;
  bool insert(int v) { 
        if(root==NULL){root=new Node();root->value=v;return true;}
        //if(find(v)==true){return false;}
        Node *y=NULL;
        Node *x=root;
        while(x!=NULL){ 
                        y=x;
                        if(v<(x->value)){x=x->left;}
                        else{x=x->right;}
                      }
        Node *z=new Node();
        z->value=v;
        z->parent=y;
        if (y==NULL){root=z;}
            else if((z->value)<(y->value)){y->left=z;}
                else{y->right=z;}
        return true;} 
  void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        Node *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  }
  // Return True, if the ticket with given attributes is found, false otherwise
};
class Graph {
  int numNodes;
  int numEdges;
  int connected_comp=0;
  fstream graphFile;
  Node *nodes;
  BST b;
  int  *visited;

  // Add appropriate fields as necessary for your implementation
  
 public:
 bool *g;
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;
    nodes = new Node[numNodes];
    g=new bool[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      g[i]=false;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);
      listOfObjects<int> *x=nodes[n1].adjacentNodes;
      bool pre=false;
      while(x!=NULL){
        if(x->object==nodes[n2].value){pre=true;break;}
        x=x->next;
      }
      if(pre==false){
        nodes[n1].addNeighbour(nodes[n2].value);
        nodes[n2].addNeighbour(nodes[n1].value);

        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }
  int cycle=0;
  

  listOfObjects<int> *c=NULL;
  // Add appropriate method declarations as necessary for your implementation
  void DFS(Node* v,Node *p){
    bool found=true;
    listOfObjects<int> *y=c;
    if(y!=NULL){
        while(y->object!=v->value){
          y=y->next;
          if(y==NULL){break;}
        }
        int start=0;
        int p=0;
        int q=1;
        while(y!=NULL){
          g[y->object-1]=true;
          y=y->next;
        }
      
    }
    
    v->visited++;
    b.insert(v->value);
    listOfObjects<int> *x=v->adjacentNodes;
    listOfObjects<int> *d=c;
    listOfObjects<int> *e=new listOfObjects <int> (0);
    while(d!=NULL){
      listOfObjects<int> *f=e;
        while(f->next!=NULL){
        f=f->next;
        }
        f->next=new listOfObjects <int> (d->object);
      d=d->next;
    }
    e=e->next;
    y=c;
    if(c==NULL){c=new listOfObjects <int> (v->value);}
    else{
        while(y->next!=NULL){
          y=y->next;
        }
        y->next=new listOfObjects <int> (v->value);
    }
    listOfObjects<int> *y1=e;
    
    while(x!=nullptr){
      if ((nodes[x->object-1].visited<2)&&(&nodes[x->object-1]!=p)){
        DFS(&nodes[x->object-1],v);
      }
      x=x->next;
    }
    c=e;
    y=c;
  }
  void modifiedDFS();
  void printResults();
};

#endif


