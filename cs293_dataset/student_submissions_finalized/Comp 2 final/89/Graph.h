#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

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

class eq{
 public:  
  int max;
  int* l;  
  eq(int i){
    max=-1;
    l = new int[i];
    for(int i=0; i<i; i++)
     l[i]=0;
   } 
 }; 

class Node {
 public:
  int value;
  Node *left;
  Node *right;	
  Node *parent;
  listOfObjects<int>* inedge;
  listOfObjects<int>* Similar;
  listOfObjects<int>* sim;
  listOfObjects<int>* outedge;
  Node(){
   int a=-10;
   inedge=new listOfObjects<int>(a);
   outedge=new listOfObjects<int>(a);
   sim=new listOfObjects<int>(a);
   Similar=new listOfObjects<int>(a);
   }
  Node(int Value) : value(Value), left(nullptr), right(nullptr) {}
};

class BST {

  Node *root;

 public:
 
      BST(){root=NULL;}
      BST(Node* root){this->root=root;}

      void pre(){
        preorder(root);
        return;
       }
         
      void preorder(Node* Y){  
        Node* X=Y;     
        if(X==NULL) return;
        else
          {
            cout << X->value << endl;
            preorder(X->left);
            preorder(X->right);   
           } 
       }

      void insert(int value) {
        
        Node* Y=NULL;
        Node* X=root;
        Node* Z=new Node(value);
        
        while(X!=NULL)
         {
            Y=X;     
            if(value < X->value)
                   X=X->left;
            else       
                   X=X->right;
           }
         Z->parent=Y;
         if(Y==NULL)
             root=Z;
         else if (value < Y->value)
              Y->left=Z;
         else Y->right=Z;
        		
         return;            
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
          root = root->left;
          // enter the next tree level - left and right branch
          printBST( prefix + (isLeft ? "│   " : "    "), true);
          root = curr->right;
          printBST( prefix + (isLeft ? "│   " : "    "), false);
          root = curr;
        }
     }
};



class Graph {
  int numNodes;
  ifstream F;
  listOfObjects<BST> *trees;  
  Node *nodes;
  int *v;
  int *cl;
  int* source;
  listOfObjects<eq *>* classes; 

 public:
  Graph(string gFileName) {
    eq *C = new eq(1);
    classes = new listOfObjects<eq *>(C);
  
    int c=0;
    int x;
    F.open(gFileName, ios::out);
    if (!F.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    F >> x; 
    numNodes=x;
         
    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
    
    while (!F.eof()) {
    
     int n1;
     int n2;
     F >> x;
     if(x==-1)
       {
         F >> x;
         c=1;continue;
        } 
        
      if(c==1)
        {
          if(x==-1) break;
          n1=x;
          F>>x;
          n2=x;
          listOfObjects<int>* similar = nodes[n1-1].sim;
           int a=0;
         while(similar!=NULL){
           if(similar->object==n2-1)
            {
              a = 1; 
              break;
             }   
           if(similar->next==NULL) break;  
             similar=similar->next;
          }
         if(a==1) continue;
  
           similar->next = new listOfObjects<int> (n2-1);          
          
        } 
      else{  
        n1 = x;
        F >> x;
        n2 = x;
        listOfObjects<int>* edges = nodes[n1-1].outedge;
        int a = 0;
      
         while(edges!=NULL){
           if(edges->object==n2-1)
            {
              a = 1; 
              break;
             }   
           if(edges->next==NULL) break;  
           edges=edges->next;
          }
         if(a==1) continue;
  
      edges->next = new listOfObjects<int> (n2-1);
      
      listOfObjects<int>* edges1 = nodes[n2-1].inedge;
        while(edges1->next!=NULL)
           edges1=edges1->next;
  
        edges1->next = new listOfObjects<int> (n1-1);
       }

    }
     v = new int[numNodes];  // defined to keep track of how many times a node is visited 
     cl = new int[numNodes];  // defined to keep track whether the node already entered an equivalance class or not 
     source = new int[numNodes];  // tells whether a node is source node or not  
  }
      
  ~Graph() {
    if (F.is_open()) {
      F.close();
    }
    delete[] nodes;
  }
  void Class(int i,int j);
  void DFS(int i);
  void modifiedDFS();
  void add(int i, int j, int &x);
  void Similarity(int &x);
  void printResults();
};

#endif
