#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class listOfObjects {
 public:
  int object;
  listOfObjects *next;
  listOfObjects *prev;
  
  // Constructor
  listOfObjects(int initValue) {object = initValue; next = prev = nullptr;}

  void push_back(int data){
    if (next != nullptr) return;
    listOfObjects* a = new listOfObjects(data);
    a->prev = this;
    next = a;
  }

  int get_at(int index){
    listOfObjects *a = this;
    for (int i=0;i<index;i++){
      a = a->next;
      if (a == nullptr) cerr<<"index out of bounds"<<endl;
    }
    return a->object;
  }

  bool is_in(int value){
    listOfObjects *a = this;
    while (a!=nullptr){
      if (value == a->object){
        return true;
      }
      a = a->next;
    }
    return false;
  }

  void print_list(){
    listOfObjects* a = this;
    cout<<"Neighb start"<<endl;
    while (a != nullptr){
      cout<<a->object<<endl<<endl;
      a = a->next;
    }
    cout<<"Neighb end"<<endl;
  }
  
  // Destructor
  ~listOfObjects() {;}
};

struct TreeNode{
    int value;	// Value
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNode(int val, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
  // Add your own field and members here
  TreeNode* root;
  
  public:

  BST(){
    root = nullptr;
  }
	BST(TreeNode *root){
    this->root = root;
  }
  bool insert(int val) { 
    
    bool left = true;
    TreeNode* prnt = nullptr;
    TreeNode* pos_ins = root;
    TreeNode* a = new TreeNode(val);
    a->left = nullptr;
    a->right = nullptr;
    if (root == nullptr){
        this->root = a;
        return true;
    }
    while (pos_ins != nullptr) {
        if (val < pos_ins->value){
            prnt=pos_ins;
            pos_ins=pos_ins->left;
            left=true;
        }
        else{
            prnt=pos_ins;
            pos_ins=pos_ins->right;
            left=false;
        }
    }
    pos_ins = a;
    pos_ins->parent = prnt;
    if (left) prnt->left = pos_ins;
    else prnt->right = pos_ins;
    return true;
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

  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  int no_of_visits;
  int arr_time;
  listOfObjects* neighbours;

  Node(){
    value = 0;
    no_of_visits = 0;
    neighbours = nullptr;
    arr_time = -2;
  }

  Node(int val){
    value = val;
    no_of_visits = 0;
    neighbours = nullptr;
    arr_time = -2;
  }

  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  BST* tree;
  int no_conn_comp;

  Node *nodes;

  int *DFS_array;
  int *parent1;
  int *parent2;
  bool* in_cycle;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    no_conn_comp = 0;
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    tree = new BST();

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    DFS_array = new int[numNodes];
    parent1 = new int[numNodes];
    parent2 = new int[numNodes];
    in_cycle = new bool[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i;
      nodes[i].no_of_visits = 0;
      DFS_array[i] = -1;
      parent1[i] = -1;
      parent2[i] = -1;
      in_cycle[i] = false;
    }    

    srand(0);
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

      if (!(nodes[n1].neighbours->is_in(n2))){
        if (nodes[n1].neighbours == nullptr) nodes[n1].neighbours = new listOfObjects(n2);
        else nodes[n1].neighbours->push_back(n2);
        if (nodes[n2].neighbours == nullptr) nodes[n2].neighbours = new listOfObjects(n1);
        else nodes[n2].neighbours->push_back(n1);
        graphFile << n1 << " " << n2 << endl;
        countEdges++;
      }
      
    }

    // for (int i=0;i<numNodes;i++){
    //   nodes[i].neighbours->print_list();
    // }

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

  void DFS(Node &node, int parent);
  void modifiedDFS();
  void printResults();

  /*void DFS(Node node, int parent){

    tree->insert(node.value);
    static int time = -1;
    time++;
    if (node.arr_time == -2) node.arr_time=time;
    node.no_of_visits++;
    if ((node.no_of_visits == 1) && (parent1[node.value] == -1)){
      parent1[node.value] = parent;
      DFS_array[node.value] = parent;
    }
    else if ((node.no_of_visits == 2) && (parent1[node.value] != -1) && (parent2[node.value] == -1)){
      parent2[node.value] = parent;
    }
    listOfObjects* a = node.neighbours;
    int back_index = node.value;
    while(a != nullptr){
      if ((nodes[a->object].no_of_visits == 2) && (nodes[a->object].value != parent1[node.value]) && (nodes[a->object].value != parent2[node.value])){
        if((nodes[a->object].no_of_visits == 1) && (nodes[a->object].arr_time < node.arr_time)){
          back_index = nodes[a->object].value;
          for (int i=node.value;i!=back_index;i=parent1[i]){
            in_cycle[i] = true;
          }
        }
      }
      
      if ((nodes[a->object].no_of_visits < 2) && (nodes[a->object].value != parent1[node.value]) && (nodes[a->object].value != parent2[node.value])){
        if((nodes[a->object].no_of_visits == 1) && (nodes[a->object].arr_time < node.arr_time)){
          back_index = nodes[a->object].value;
          for (int i=node.value;i!=back_index;i=parent1[i]){
            in_cycle[i] = true;
          }
        }
        DFS(nodes[a->object], node.value);
      }

      if (parent2[node.value] != -1){
        parent2[node.value] = -1;
      }
      else if (parent1[node.value] != -1){
        parent1[node.value] = -1;
      }
      a = a->next;
    }


  }

  void modifiedDFS(){
    for (int i=0;i<numNodes;i++){
      if (nodes[i].no_of_visits == 0){
        no_conn_comp++;
        DFS(nodes[i],-1);
      }
    }
  }
  void printResults(){
    cout<<no_conn_comp<<endl;
    int one = 0,two = 0, num = 0;
    for(int i=0;i<numNodes;i++){
      if (nodes[i].no_of_visits == 1) one++;
      else if (nodes[i].no_of_visits == 2) two++;
      if (in_cycle[i]) num++;
    }
    cout<<one<<endl;
    cout<<two<<endl;
    cout<<num<<endl;
    tree->printBST("",false);
  }*/
};

#endif
