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

class Node {
 public:
  int value;
  Node *left;
  Node *right;	
  Node *parent;
  listOfObjects<int>* edge;
  Node(){
   int a=-10;
   edge=new listOfObjects<int>(a);
   }
  Node(int Value) : value(Value), left(nullptr), right(nullptr) {}
  // insert other fields and methods as appropriate
};

class BST {
  // Add your own field and members here
	
  // Feel free to use the printBST function used earlier 

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
  int numEdges;
  fstream graphFile;
  listOfObjects<BST> *trees;  
  Node *nodes;
  int *v;
  int* parent;
  int* c;
  int* cycle;
  // Add appropriate fields as necessary for your implementation
  
 public:
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
      
      listOfObjects<int>* edges = nodes[n1].edge;
      int a = 0;
      
         while(edges!=NULL){
           if(edges->object==n2)
            {
              a = 1; // this imply that we have an edge already created between nodes n1,n2
              break;
             }   
           if(edges->next==NULL) break;  
           edges=edges->next;
          }
         if(a==1) continue;
  
      edges->next = new listOfObjects<int> (n2);
      
      listOfObjects<int>* edges1 = nodes[n2].edge;
      listOfObjects<int>* edges_2;
        while(edges1->next!=NULL)
           edges1=edges1->next;
  
        edges1->next = new listOfObjects<int> (n1);
       
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
     v = new int[numNodes];  // defined to keep track of how many times a node is visited 
     parent = new int[numNodes]; // parent[node] stores the index of the parent of the node  
     cycle = new int[numNodes];  //if a node is in a cycle then cycle[node] will be 1 else it is 0
     c = new int[numNodes];  // array c is defined to detect cycles
    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void DFS(int i, int j, BST &tree);
  void modifiedDFS();
  void printResults();
};

#endif
