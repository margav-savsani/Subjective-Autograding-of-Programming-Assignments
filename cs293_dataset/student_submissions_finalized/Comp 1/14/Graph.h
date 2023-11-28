#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode
{
  int value;		// value
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  
  //constructor
  
  TreeNode() : value(-1), left(nullptr), right(nullptr) {}
  TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
  TreeNode(int value, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) :  value(value), left(leftChild), right(rightChild), parent(parent) {}
  
};

class BST 
{
  // Add your own field and members here
  TreeNode *root;

  public:
    // Constructors!
    BST() {root = nullptr; }
    BST(TreeNode *curr_root) {root = curr_root; }

    // Implement your own destructor
    ~BST() {delete root;};

    TreeNode* getroot() {return root;}
    
    // Inserts the element and returns True otherwise
    bool insert(int value)
    {
      if(root == NULL)
      {
        root = new TreeNode(value,NULL,NULL,NULL);
        return true;
      }
    
      TreeNode *curr = root;
      while(true)
      {
        // Moving to the right, if price is greater
        if(value > curr->value)
        {
          if(curr->right!=NULL)
          {
              curr = curr->right;
          }
          else
          {
            curr->right = new TreeNode(value,NULL,NULL,curr);
            break;   
          }
        }
        else
        {
          // moving to left if its smaller
          if(curr->left!=NULL)
          {
            curr = curr->left;
          }
          else
          {
            curr->left = new TreeNode(value,NULL,NULL,curr);
            break;    
          }
        }
    }
    return true;
    }

    void printBST(const string& prefix, bool isLeft=false)
    {
      if( root != nullptr )
      {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value<< endl;
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

  // insert other fields and methods as appropriate
};

class listOfObjects 
{
  public:
    int object;
    listOfObjects *next;
    listOfObjects *prev;
    
    // Constructor
    listOfObjects(int initValue) {object = initValue; next = prev = nullptr;}
    
    // Destructor
    ~listOfObjects() {;}
};

void add_edge(listOfObjects** adj_list, int u, int v) 
{    
  //add v into the list u, and u into list v
  listOfObjects* vt = new listOfObjects(v);
  listOfObjects* ut = new listOfObjects(u);
  listOfObjects* curru = adj_list[u];
  listOfObjects* currv = adj_list[v];
  while(curru->next != NULL)
  {
    curru = curru->next;
  }
  curru->next = vt;
  while(currv->next != NULL)
  {
    currv = currv->next;
  }
  currv->next = ut;
}

class Graph 
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  listOfObjects* adj_list[100]; //assuming number of nodes doesn't cross this
  int counter = 1;
  int cyc_idx = 0;
  int visited[100];
  int ar1[100];
  int dr1[100];
  int ar2[100];
  int dr2[100];
  bool incycle[100];
  int recstack[200]; //number of times a number is occuring in recursion stack
  
  Node *nodes;

  // Add appropriate fields as necessary for your implementation

 public:
  int numofcomponents = 0;
  int n_visit_once = 0;
  int num_in_cycle = 0;
  int n_trees = 0;
  BST* trees[100]; //max number of trees asuming it doesn't exceed
  Graph(int nNodes, int nEdges, string gFileName) 
  {
    numNodes = nNodes;
    numEdges = nEdges;
    // listOfObjects* adj_list[nNodes];
    

    for (int i=0;i<nNodes;i++)
    {
      visited[i] = 0;
      recstack[i] = 0;
      ar1[i] = 0;
      dr1[i] = 0;
      ar2[i] = 0;
      dr2[i] = 0;
      incycle[i] = false;
    }
    
    for (int i=0;i<nNodes;i++)
    {
      listOfObjects* a = new listOfObjects(-1);
      adj_list[i] = a;
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

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) 
    {
      // cout << "because3";
      do 
      {
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

      //check if the edge is present aldready
      if(!(search(adj_list[n1], n2) && search(adj_list[n2], n1)))
      {
        add_edge(adj_list,n1,n2);
        countEdges++;
      }

      graphFile << n1+1 << " " << n2+1 << endl;
      
    }

    // printadjlist();
    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() 
  {
    if (graphFile.is_open()) 
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  int getnumnodes(){return numNodes;}

  bool search(listOfObjects* head, int x)
  {
    // Base case
    if (head == NULL)
        return false;
    // If key is present in current node, return true
    if (head->object == x)
        return true;
    // Recur for remaining list
    return search(head->next, x);
  }

  void printadjlist()
  {
    //to check printing adjacency list
    for(int i=0;i<numNodes;i++)
    {
      cout << i+1;
      cout << "->";
      listOfObjects* curr = adj_list[i];
      while(curr->next!=NULL)
      {
        curr = curr->next;
        cout << (curr->object) +1 << ",";
      }
      cout << endl;
    }
  }

  void modifiedDFS();
  void DFSutil(int i, BST* tree, int not_this);
  void printResults();
};

#endif
