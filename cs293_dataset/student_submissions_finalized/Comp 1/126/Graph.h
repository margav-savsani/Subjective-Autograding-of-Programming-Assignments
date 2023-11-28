#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class Journey{
public:
  unsigned int value; 
  Journey *left;
  Journey *right;
  Journey *parent;
 
  Journey(){
    value = -1; left=nullptr; right=nullptr;
  }
    
  bool operator < (Journey const &j){
    if(value < j.value) return true; else return false;
  } // Overloaded operator. Usage: if (journey1 < journey2) {...}

};

class BST {

public:
        // ************************************************************
        // Methods for Part I
  
	// Constructors!
    Journey *root;
    int longest=0, shortest=0;
	
BST(){
    root=nullptr;
 }
BST(Journey *root){
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool insert(int value) {   
    Journey *ins=new Journey;
    ins->value=value;
    ins->left=nullptr;
    ins->right=nullptr;
    Journey *y=nullptr; 
    Journey *x=root;
    while(x!=nullptr){
        y=x;
        if(value<(x->value)){
            x=x->left;
        }  
        else{
            x=x->right;
        }
    }
    ins->parent=y;
    if(y==nullptr){
        root=ins;
    }
    //instead of the following 4 lines, x=ins should work
    else if((y->value)>value)
        y->left=ins;
    else
        y->right=ins;
    return true;
  }
// Return True, if the ticket with given attributes is found, false otherwise
Journey* find(int value) { 
    Journey *x=root;
    while(x!=nullptr){
        if((x->value==value)){
            return x;
        }
        else if(x->value>value){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    return nullptr;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool remove(int value) {
    Journey *t=root;
    while(t!=nullptr){
        if((t->value==value)){
            break;
        }
        else if(t->value>value){
            t=t->left;
        }
        else{
            t=t->right;
        }
    }
    if(t==nullptr){
        return false;
    }
    else{
        //case1, t has 0 children
        if(t->left==nullptr&&t->right==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=nullptr;
                }
                else{
                    t->parent->right=nullptr;
                }
            }
            else{
                root=nullptr;
            }
        }
        //case2, t has 1 child
        else if(t->left==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=t->right;
                    t->right->parent=t->parent;
                    t=nullptr;
                }
                else{
                    t->parent->right=t->right;
                    t->right->parent=t->parent;
                    t=nullptr;
                }
            }
            else{
                root=t->right;
                root->parent=nullptr;
            }
        }
        else if(t->right==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=t->left;
                    t->left->parent=t->parent;
                    t=nullptr;
                }
                else{
                    t->parent->right=t->left;
                    t->left->parent=t->parent;
                    t=nullptr;
                }
            }
            else{
                root=t->left;
                root->parent=nullptr;
            }
        }
        else{
            //finding the successor
            Journey *temp=t->right;
            while(temp->left!=nullptr){
                temp=temp->left;
            }
            
            if(temp->right==nullptr){
                t->value=temp->value;
                if(temp->parent->left==temp){
                    temp->parent->left=nullptr;
                }
                else{
                    temp->parent->right=nullptr;
                }
            }
            else{
                if(temp->parent->left==temp){
                    temp->parent->left=temp->right;
                    temp->right->parent=temp->parent;
                }
                else{
                    temp->parent->right=temp->right;
                    temp->right->parent=temp->parent;
                }
                t->value=temp->value;
                temp=nullptr;
            }
        }
    }
    return true;
}

    void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr )
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__" );

            // print the value of the node
            cout << root->value<< endl;
            Journey *curr = root;
            root = root->left;
            // enter the next tree level - left and right branch
            printBST( prefix + (isLeft ? "│   " : "    "), true);
            root=curr;
            root = root->right;
            printBST( prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }

};

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
  int num;
  bool Cycle;
  listOfObjects<Node *> *neighbours;

  Node(){
    value=0;
    num=0;
    Cycle=false;
    neighbours=nullptr;
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  int connComp=0;
  int cycleNodes;
  listOfObjects<BST *> *DFSTLL;
  fstream graphFile;

  Node *nodes;


  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    cycleNodes=0;
    BST *DFSTree = new BST();
    DFSTLL= new listOfObjects<BST *>(DFSTree);
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

    //srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
    
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);
    
   /*
    cin>>n1;
    cin>>n2;
    */
      //Each node has a listOfObjects type node
      //First adding it to the node of n1
    listOfObjects<Node *> *temp2=nodes[n1].neighbours;
    bool check=false;
    while(temp2!=nullptr){
        if(temp2->object->value==n2+1){
            check =true;
            break;
        }
        temp2=temp2->next;
    }
    if(!check){
        listOfObjects<Node *> *temp=nodes[n1].neighbours;
        if(nodes[n1].neighbours==nullptr){
            nodes[n1].neighbours=new listOfObjects<Node *>(new Node());
            nodes[n1].neighbours->object=&nodes[n2];
        }
        else{
            while(temp->next!=nullptr){
                temp=temp->next;
            }
            Node *cons = new Node();
            temp->next=new listOfObjects<Node *>(cons);
            temp->next->object=&nodes[n2];
        }
        listOfObjects<Node *> *temp1=nodes[n2].neighbours;
        if(nodes[n2].neighbours==nullptr){
            nodes[n2].neighbours=new listOfObjects<Node *>(new Node());
            nodes[n2].neighbours->object=&nodes[n1];
        }
        else{
            while(temp1->next!=nullptr){
                temp1=temp1->next;
            }
            Node *cons=new Node();
            temp1->next=new listOfObjects<Node *>(cons);
            temp1->next->object=&nodes[n1];
        }

          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;
        }
    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    delete DFSTLL;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void DFS(Node *node, Node *prev, BST *DFST);
  void modifiedDFS();
  void printResults();
};

#endif
