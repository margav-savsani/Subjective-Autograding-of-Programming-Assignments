#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>

vector<vector<int>> cycles;   // a vector of vector for storing all the cycles
int cyclenumber = 0;  // global variable showing the number of cycles in the graph


// BST Treenode class
struct TreeNode{
  int price;		
  TreeNode *left;	
  TreeNode *right;	
  TreeNode *parent;	
  TreeNode() : price(0),left(nullptr), right(nullptr) {}
  TreeNode(int jrnyPrice) : price(jrnyPrice), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice),left(leftChild), right(rightChild), parent(parent) {}
};

class BST{
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  public:
  	TreeNode *root; 
	  BST(){root = NULL; }
	  BST(TreeNode *root){this->root = root; }

    // function to print BST
	  void printBST(const string& prefix, bool isLeft=false){
      if( root != nullptr ){
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );
        cout << '('<<root->price<<')' << endl;
        TreeNode *curr = root;
        root = root->left;
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
      }
    }

    // function finds if the price is already present in the BST, returns true if found else false
	  bool find(int price) {
      if(root==NULL)return false;
      TreeNode* curr = root;
      while(true){
        if(curr->price==price) return true;
        else if(curr->price > price){     
          if(curr->left==NULL) return false;
          else curr = curr->left;
        }
        else{
            if(curr->right==NULL)return false;
            else curr = curr->right;
        }
      }
      return false;
    }

    // function to insert a node into the BST
	  bool insert(int price) { 
      if(root == NULL){
        root = new TreeNode(price,NULL,NULL,NULL);
        return true;
      }
      if(find(price))return false;
      TreeNode *curr = root;
      while(true){
        if(price > curr->price){
            if(curr->right!=NULL) curr = curr->right;
            else{
              curr->right = new TreeNode(price,NULL,NULL,curr);
              break;
            }
        }
        else{
            if(curr->left!=NULL) curr = curr->left;
            else{
              curr->left = new TreeNode(price,NULL,NULL,curr);
              break;   
            }
        }
      }
      return true;
    }
};

// class fo list
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
  // insert other fields and methods as appropriate
 public:
  int value;
  listOfObjects<Node *> *adja;  //store the adjacency list of the node
  Node(int val){
    value = val;
    adja = nullptr;
  }
  Node(){
    value = 0;
    adja = nullptr;
  }
};

class Graph {
  // Add appropriate fields as necessary for your implementation
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  int *visitcnt;  //array which stores the visit number corresponding to each node; is of size numNodes
  BST *all_trees; //an array of all the component BSTs
  int connected_comp; //keeps cnt of number of connected componenets in the graph
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    //all the initialisations
    all_trees = nullptr;  
    connected_comp = 0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    all_trees = new BST[numNodes];
    visitcnt = new int[numNodes];
    //initialised to 0 since initial visit cnt of each node is 0
    for (int i=0;i<numNodes;i++){
      visitcnt[i]=0;
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
      bool found = false;
      listOfObjects<Node*> *temp = nodes[n1].adja;  //copy created to traverse
      // checks if an edge between n2 and n1 already exists
      while(temp != nullptr){
        if(temp->object->value != n2+1){
          temp = temp->next;
        }
        else{
          found = true;
          break;
        }
      }
      //if doesnt exist then addedge function called
      if(found == false){
        addEdge(n1,n2);
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
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  // function which adds an edge between integers m and n i.e, nodes with values m and n
  void addEdge(int m, int n){
    Node *n1 = new Node(n+1);
    Node *n2 = new Node(m+1);
    listOfObjects<Node*> *l1 = new listOfObjects<Node*> (n1);
    listOfObjects<Node*> *l2 = new listOfObjects<Node*> (n2);
    if(nodes[m].adja == nullptr) nodes[m].adja = l1 ;
    else nodes[m].adja->next = l1;
	  if(nodes[n].adja == nullptr) nodes[n].adja = l2;
    else nodes[n].adja->next = l2;
  }

  // a utility function for performing the dfs; this function manages the dfs within each component 
  // and the modifieddfs function manages the number of components and calls the dfs utility function for each connected component
  void dfs(Node a, BST &tree){
    visitcnt[a.value -1]++; //visitcnt of this node ncremented by 1
    int ind = a.value;
    tree.insert(a.value); //node inserted into bst; ie, the value of the node
    listOfObjects<Node*> *adj_nodes = nodes[ind-1].adja;  //list of nodes adjacent to the argument node
    listOfObjects<Node*> *t1 = adj_nodes; //copy created to traverse
    while (t1!=nullptr){
      if(visitcnt[t1->object->value -1] < 2){       
        dfs(t1->object->value, tree);
      }
      t1 = t1->next;
    }
    return;
  }

  // functions traces the cycles and the count of cycles using dfs ; color shows if the node is visited once or twice and so on
  void dfs_cycle(int u, int p, int color[], int par[], int& cyclenumber){
    if (color[u] == 2) return;  //if already visited completely
    if (color[u] == 1) {  //visiterd partially
        vector<int> v;
        cyclenumber++;           
        int cur = p;
          v.push_back(cur);
        while (cur != u) {
            cur = par[cur];
            v.push_back(cur);
        }
        cycles.push_back(v);
        return;
    }
    par[u] = p;
    color[u] = 1;
    listOfObjects<Node*> *adj_nodes = nodes[u-1].adja;  //adjacency list
    listOfObjects<Node*> *t1 = adj_nodes; //copy to travers
    while (t1!=nullptr){  //perform dfs on the adjacent node s of node with value u 
      if(t1->object->value ==par [u-1]){  
        continue;     
      }
      dfs_cycle(t1->object->value, u, color, par, cyclenumber); //dfs called recursively
      t1 = t1->next;
    }
    color[u] = 2; //marked that this node viited completely
  }
  // function which stores into the in_cycle array if node is present or not in the cycle and returns the number of nodes in the cycle
  int Cycles(int& cyclenumber){
    bool in_cycle[numNodes];
    for(int i=0;i<numNodes;i++){
      in_cycle[i] = false;
    }
    for (int i = 0; i < cyclenumber; i++) {
        for (int x : cycles[i])
          in_cycle[x] = true;
    }
    int nodes_cycle = 0;
    for(int i=0;i<numNodes;i++){
      if (in_cycle[i] == true) nodes_cycle++;
    }
    return nodes_cycle;
}

  void modifiedDFS();
  void printResults();

};

#endif
