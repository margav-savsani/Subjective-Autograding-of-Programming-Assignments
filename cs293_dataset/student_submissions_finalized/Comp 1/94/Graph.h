#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif
//The DFS function which is implemented
//Inserting inside the tree
//The adjacency list going iteratively
//Deleting the edge so it becomes directed
//Deleteing the edge when it backtraces
class TreeNode{
  public:
  int value;
  TreeNode*parent;
  TreeNode*left;
  TreeNode*right;
  TreeNode(){value=-1;parent=left=right=NULL;}
  TreeNode(int v){value=v;parent=left=right=NULL;}
};
//The DFS function which is implemented
//Inserting inside the tree
//The adjacency list going iteratively
//Deleting the edge so it becomes directed
//Deleteing the edge when it backtraces
class BST {
  public:
  TreeNode*root;
  BST(){
    root=NULL;
  }
  BST(TreeNode*r){
    root=r;
  }
  void insert(int v){
    if(root==NULL){
      root=new TreeNode(v);
    }
    else{
      insert_help(v,root);
    }
    return;
  }
  void insert_help(int v,TreeNode*r){
    TreeNode*r1=r;
    if(v<=r1->value){
        if(r1->left==NULL){
            r1->left=new TreeNode(v);
            r1->left->parent=r1;
        }
        else insert_help(v,r1->left);
    }
    else{
        if(r1->right==NULL){
            r1->right=new TreeNode(v);
            r1->right->parent=r1;
        }
        else insert_help(v,r1->right);
    }
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
//The DFS function which is implemented
//Inserting inside the tree
//The adjacency list going iteratively
//Deleting the edge so it becomes directed
//Deleteing the edge when it backtraces
class Node {
 public:
  int value;
  int color;
  int time;
  bool in_cyclic; 
  int count_visit;
  // insert other fields and methods as appropriate
  Node(){
    color=0;
    time=0;
    in_cyclic=false;
    value=-1;
    count_visit=0;
  }

  // insert other fields and methods as appropriate
};
class list{
  public:
  int value;
  list*next;
  list(){
    value=-1;
    next=NULL;
  }
  list(int v){
    value=v;
    next=NULL;
  }
  void append(int v){
    list*temp=next;
    if(temp==NULL){
      next=new list(v);
      return;
    }
    while(temp->next!=NULL){
      temp=temp->next;
    }
    list*l=new list(v);
    temp->next=l;
  }
  bool check(int v){
    if(value==v) return true;
    else{
      list*temp=next;
      while(temp!=NULL){
        if(temp->value==v) return true;
        temp=temp->next;
      }
      return false;
    }
  }
  void delete_edge(int v){
    if(next==NULL) return;
    if(next->value==v){
      next=next->next;
      return;
    }
    list*temp=next;
    list*prev=next;
    while(temp!=NULL){
      if(temp->value==v){
        prev->next=temp->next;
        return;
      }
      else{
        prev=temp;
        temp=temp->next;
      }
    }
    return;  
  }
};
//The DFS function which is implemented
//Inserting inside the tree
//The adjacency list going iteratively
//Deleting the edge so it becomes directed
//Deleteing the edge when it backtraces
class BSTstore{
  public:
  BST*b;
  BSTstore*next;
  BSTstore(){b=NULL; next=NULL;}
  BSTstore(BST*a){b=a;next=NULL;}
  void append(BST*a){
    if(b==NULL){
      b=new BST(a->root);
      return;
    }
    else{
      BSTstore*temp=next;
      if(temp==NULL){
        next=new BSTstore(a);
        return;
      }
      while(temp->next!=NULL){
        temp=temp->next;
      }
      BSTstore*l=new BSTstore(a);
      temp->next=l;
    }
    return;
  }

};


class Graph {
  int numNodes;
  int numEdges;
  int connected_comp;
  int time;
  fstream graphFile;
  BSTstore*b;
  Node *nodes;
  list**adj;
  list**adj_temp;
  list*cyclic;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    time=1;
    numNodes = nNodes;
    numEdges = nEdges;
    connected_comp=0;
    b=new BSTstore();
    adj=new list*[nNodes];
    adj_temp=new list*[nNodes];
    cyclic=new list();
    for(int i=0;i<numNodes;i++){
      adj[i]=new list();
      adj_temp[i]=new list();
    }
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

    srand(0);
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	      n1 = rand() % numNodes;
	      n2 = rand() % numNodes;
      } while (n1 == n2);
      // cout<<"n1"<<n1<<endl;
      // cout<<"n2"<<n2<<endl;
      bool found=false;

      if(adj[n1]->check(n2)) found=true; //Deleting the edge so it becomes directed
                                          //Deleteing the edge when it backtraces
      if(!found){
        adj[n1]->append(n2);
        adj[n2]->append(n1);
        adj_temp[n1]->append(n2);            //Deleting the edge so it becomes directed
                                            //Deleteing the edge when it backtraces
        adj_temp[n2]->append(n1);
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
  void modifiedDFS_help(int index,BST*b);
  void cycle(int index,int p);
};

#endif
