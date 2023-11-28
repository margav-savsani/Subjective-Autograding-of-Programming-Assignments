#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T>
class LinkedList_node{
  public:
    T a;
    LinkedList_node *next,*prev;  
    LinkedList_node(T x){a=x;}
};

template <typename T>
class LinkedList{
  public:
    LinkedList_node<T> *node=nullptr;
    
    // function to add a new LinkedList_node at end with a in it equal to passed argument
    void push(T x){
      if(node==nullptr){node = new LinkedList_node(x); 
        node->prev = nullptr; node->next=nullptr;
      }
      else{
        LinkedList_node<T> *l = node;
        while(l->next!=nullptr){
          l = l->next;
        }
        l->next = new LinkedList_node(x);
        l->next->prev = l;
      }
    }
    
    //function to where given element is present in Linkedlist
    bool find(T x){
      if(node==nullptr){return false;}
      else{
        LinkedList_node<T> *n=node;
        bool found= false;
        while(n!=nullptr){
          if(n->a==x){
            found = true;
            break;
          }
          n = n->next;
        }
        return found;
      }
    }
    
    //function to remove Linkedlistnode present at the starting of Linkedlist
    void remove(){
       LinkedList_node<T> *x = node;
       node = node->next;
       delete x;
     }
};


class Node {
 public:
  int value;
  int no_of_visits = 0;
  LinkedList<int> l;    // adjaceny list of neighbouring nodes
  LinkedList<int> prev;
  int degree = 0;       // indicates no of neighbouring nodes(i.e length of list)
};

//for nodes in BST
class Treenode {
 public:
  int value;
  Treenode *parent,*left,*right;
};

class BST {

  
  Treenode* root;
  
  public:
    // function to insert treenode with value in it equal to passed argument into BST
    void insert(int x){
       if(root==nullptr){root = new Treenode;
         root->value = x;
       }
       else{
        Treenode* p,*c;
        int i;
        p = root;
        if(p->value>x){c=p->left;i=0;}
        else if(p->value==x){i=2;}
        else{c=p->right;i=1;}
        if(i!=2){
        while(c!=nullptr&&i!=2){
          p = c;
          if(p->value>x){c=p->left;i=0;}
          else if(p->value==x){i=2;}
          else{c=p->right;i=1;}
        }
        if(i==0){p->left=new Treenode;
          p->left->value = x;p->left->parent=p;
        }
        else if(i==2){}
        else{p->right=new Treenode;
          p->right->value = x;p->right->parent = p;
        }
        }
       }
       return;
    }
    
    // for printing Values in BST
    void printBST(const string& prefix, bool isLeft=false)
   {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the Treenode
        cout << '('<< root->value<<')' << endl;
        Treenode *curr = root;
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

  Node *nodes;
  LinkedList<BST *> b;
  
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

      if(!nodes[n1].l.find(n2+1)){
        nodes[n1].l.push(n2+1);nodes[n2].l.push(n1+1);
        nodes[n1].degree++;                 // increasing no of neighbouring nodes
        nodes[n2].degree++;
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;}
    }

  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  
  //function for making dfs visit of passed node and adding into bst.
  void DFS_visit(Node *n,BST *bst){
    n->no_of_visits = n->no_of_visits + 1;    
    
    {bst->insert(n->value);}
    LinkedList_node<int> *curr = n->l.node;      
    
    //while loop for making DFS_visit of each of the neighbouring nodes
    while(curr!=nullptr){
      if(nodes[curr->a-1].no_of_visits<2){
        if(!n->prev.find(curr->a)){
          nodes[curr->a-1].prev.push(n->value);
        DFS_visit(&nodes[curr->a-1],bst); }}
      
      curr=curr->next;
    }
    return;
  }
  
  //function to return no of nodes present in all cycles of the graph
  int no_of_nodes(){
      int no=0;LinkedList<int> list;
      int visited[numNodes] ;
      for(int i=0;i<numNodes;i++){visited[i]=0;}
      while(true){
          
         for(int i=0;i<numNodes;i++){
          if(nodes[i].degree==1&&visited[i]==0){
              list.push(i);
              visited[i]=1;
          }
         }
         if(list.node==nullptr) break;
      while(list.node!=nullptr){
          int first = list.node->a;
          list.remove();
          visited[first] = 1;

          for(int i=0;i<nodes[first].degree;i++){
            LinkedList_node<int> *curr;
            curr = nodes[first].l.node;
            while(curr!=nullptr){
              nodes[curr->a-1].degree--;
              curr = curr->next;
            }
          }
         }
      }

      for(int i=0;i<numNodes;i++){
        if(visited[i]==0&&nodes[i].degree!=0){
           no++;
        }
      }
      return no;
  }
  void modifiedDFS();
  void printResults();
};

#endif
