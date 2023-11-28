#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
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
  Node *left;	// Left Child of this Node (NULL, if None)
  Node *right;	// Right Child of this Node (NULL, if None)
  Node *parent;
  // insert other fields and methods as appropriate
  public:
   Node(int valu)
  {
    value=valu;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
  }
};
class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  Node *root;

	// result variable is for testing purposes, Do not tamper with it!
	vector<string> result;
  public:
 
  bool insert(int value) { 
    if(root==NULL)
    {
        root=new Node(value);
        root->parent=NULL;
      
        return true;
    }
    BST n;
    n.root=root;
    if(n.root->left ==NULL && n.root->right==NULL ){
        if(n.root->value>=value){
            n.root->left=new Node(value);
            n.root->left->parent=n.root;
        }
        if(n.root->value<value){
            n.root->right=new Node(value);
            n.root->right->parent=n.root;
        }
        return true;
    }
    if(n.root->left ==NULL && n.root->right!=NULL ){
        if(n.root->value>=value){
            n.root->left=new Node(value);
            n.root->left->parent=n.root;
            return true;}
            else {n.root=n.root->right;
                return n.insert(value);}
        
        
    }
    if(n.root->left !=NULL && n.root->right==NULL ){
        if(n.root->value<value){
            n.root->right=new Node(value);
            n.root->right->parent=n.root;
            return true;}
            else{n.root=n.root->left;
            return n.insert(value);}
    }
    
    if(n.root->value>=value)
    {
        n.root=n.root->left;
        n.insert(value);
    }
    if(n.root->value<value)
    {
        n.root=n.root->right;
        n.insert(value);
    }
    return false; 
    }

// Return True, if the ticket with given attributes is found, false otherwise

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



class N
{
  public:
  int value;
  int color;
  int pos;
  bool incycle;
  int no_v;
  N()
  {
    pos=0;
    no_v=0;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  int *adjacency;//adjacency matrix 
  fstream graphFile;
  int count;//counts the position 
  N *nodes;
  BST b;//creates a new BST
  int no_co;//counts the no of components 
  int one_time;//counts the no of nodes with one time
  int two_time;//counts the no of nodes with two times visited
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    no_co=0;// initiliazes no_co to zero
    one_time=0;// initiliazes one_time to zero
    two_time=0;//initiliazes two_time to zero
    numNodes = nNodes;
    numEdges = nEdges;
    adjacency=new int[numNodes*numNodes];
    nodes = new N[numNodes];
    for (int i = 0; i <numNodes*numNodes; i++)
    {
      adjacency[i]=0;
    }
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i;
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
      if(adjacency[n1+numNodes*n2]==1)//if the edge already exists process continue
      {continue;}
      adjacency[n1+numNodes*n2]=1;
      adjacency[n2+numNodes*n1]=1;

      graphFile << n1 +1<< " " << n2+1 << endl;
      countEdges++;
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

 
  void modifiedDFS();

    
 void newDFS(int p,int l)//reccursive call for no of times visited
  {
    b.insert(nodes[p].value+1);
    nodes[p].no_v++;
    nodes[p].color=1;
    for (int i = 0; i < numNodes; i++)
    {
      if(adjacency[nodes[p].value+numNodes*i]==1)//checks for any adjacent elements
      {
        if((nodes[i].color==0||nodes[i].color==1)&&nodes[i].no_v<2&&i!=l)
        {
          newDFS(i,p);
        }
      }
    }
    nodes[p].color=2;
  }
  void DFS(int p,int l)//reccursive call for no of cycle elements
  {
    b.insert(nodes[p].value+1);
    nodes[p].color=1;
    nodes[p].pos=count;
    count++;//increments the count 
    for (int i = 0; i < numNodes; i++)
    {
      if(adjacency[nodes[p].value+numNodes*i]==1)
      {
        if(nodes[i].color==1 && nodes[i].value!=l &&nodes[i].pos!=0)//if there is a cycle then all the elements in the cucle equate the bool to true
        {
          for (int s=0;s<numNodes;s++)
          {
          for (int j = nodes[i].pos; j<count;j++)
          {
            
            if(nodes[s].pos==j)
            nodes[s].incycle=true;
          }
          }
        }
        if((nodes[i].color==0||nodes[i].color==1)&&nodes[i].no_v<2&&i!=l)
        {
          DFS(i,p);
        }
        if(nodes[i].color==0)
        {
          DFS(i,p);
        }
      }
    }
    nodes[p].pos=0;//equate the position of the node to zero
    nodes[p].color=2;//equates the color to black
    count--;// decrement the count when we back traces 

  }
  
  void printResults();
};

#endif
