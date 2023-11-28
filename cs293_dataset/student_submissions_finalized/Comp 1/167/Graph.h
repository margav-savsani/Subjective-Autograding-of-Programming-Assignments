#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


class node{
  public:
    int data;
    node* next;
    node(){
      next=NULL;
    }
    node(int s){
      this->data = s;
      this->next = NULL;
    }
};

class Linkedlist {
    public:
    node* head;

    // Default constructor
    Linkedlist() { head = NULL; }
    void insertNode(int k);
    node* find(int k);
    void printList();
};

void Linkedlist::insertNode(int k)
{
    // Create the new Node.
    node* newNode = new node(k);
  
    // Assign to head
    if (head == NULL) {
        head = newNode;
        return ;
    }
  
    // Traverse till end of list
    node* temp = head;
    while (temp->next != NULL) {
        // Update temp
        temp = temp->next;
    }
  
    // Insert at the last.
    temp->next = newNode;
}
void Linkedlist::printList()
{
    node* temp = head;
  
    // Check for empty list.
    if (head == NULL) {
        cout << "List empty" << endl;
        return;
    }
  
    // Traverse the list.
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}
  
node* Linkedlist::find(int k)
{
    node* temp = head;
  
    // Check for empty list.
    if (head == NULL) {
        //cout << "List empty" << endl;
        return NULL;
    }
  
    // Traverse the list.
    while (temp != NULL) {

        if(temp->data==k) return temp;
        temp = temp->next;
    }
    return NULL;
}

class Node {
 public:
  int value; //range from 1 to N inclusive
  Linkedlist adjacency;
  bool incycle;
  Node *left=NULL;	// Left Child of this Node (NULL, if None)
  Node *right=NULL;	// Right Child of this Node (NULL, if None)
  Node *parent=NULL;	// The Parent Node, NULL in case of Root
  // insert other fields and methods as appropriate

};
class BST {
  public:
    Node* root=NULL;
    void printBST(const string& prefix, bool isLeft);
    bool find(int amt);
    bool insert(int amt);
};
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->value<<')' << endl;
        Node *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

bool BST::find(int amt) {
   
    Node *x=root;
     while(x != nullptr ){
         if (x->value >= amt ) {
           if(x->value==amt) return true;
           else x=x->left;
          }
         else {
           if(x->value==amt) return true;
           else x=x->right;
          }
         }
  return false;}


bool BST::insert(int amt) { 
    if(root == NULL){
        root = new Node();
        root->value=amt;
        return true;
    }
    // Checking if similar node already exists
    //if(find(amt))return false;
    Node *curr = root;
    while(true){
        // Moving to the right, if price is greater
        if(amt > curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }
            else{
                curr->right = new Node();
                curr->right->value=amt;
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }
            else{
                curr->left = new Node();
                curr->left->value=amt;
                break;
                
            }
        }
    }
    return true;
}


class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int *visited;
  Node *nodes;
  BST tree;
  int connectcomp=0;
  Linkedlist dfsele;
  int ncycles=0;
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
    visited=new int[numNodes];
    nodes = new Node[numNodes];
    for(int i=0;i<numNodes;i++){
      visited[i]=0;
    }
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
      bool already=false;
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);
      node* x=nodes[n1].adjacency.find(nodes[n2].value-1);
      node* y=nodes[n2].adjacency.find(nodes[n1].value-1);
      if(x!=NULL || y!=NULL) {continue;}
      nodes[n1].adjacency.insertNode(nodes[n2].value-1);
      nodes[n2].adjacency.insertNode(nodes[n1].value-1);
      //nodes[n1].adjacency.printList();
      
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

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }
  void dfs(int k,int p);
  void modifiedDFS();
  void printResults();
};

#endif
