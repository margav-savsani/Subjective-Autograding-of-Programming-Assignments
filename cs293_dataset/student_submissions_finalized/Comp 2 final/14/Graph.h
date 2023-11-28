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
  // cout << "graph checkpoint 5" << endl;

  //add v into the list u, and u into list v
  listOfObjects* vt = new listOfObjects(v);
  listOfObjects* curru = adj_list[u];
  
  while(curru->next != NULL)
  {
    curru = curru->next;
  }
  curru->next = vt;
}

void add_parent(int** par_list, int child, int parent, int* num_parents) 
{    
  // cout << "graph checkpoint 6" << endl;
  par_list[child][num_parents[child]] = parent;
  num_parents[child]++;
}

class Graph 
{
 public:
  int numNodes;
  int numEdges;
  int numSimPairs;
  int desrcnodes[200];
  int tarnodes[200];
  int sim1src[200];
  int sim2src[200];
  int* par_list[200];
  int num_parents[200];
  int* sim_list[200];
  int num_sims[200];
  listOfObjects* adj_list[200]; //assuming number of nodes doesn't cross this
  int srcnodes[200];
  int num_src_nodes = 0;
  int collapsed[200];
  int num_grps = 0;
  int grps[200];
  int num_results=0;
  
  int results1[100];
  int results2[100];

  int numofcomponents = 0;
  int n_visit_once = 0;
  int num_in_cycle = 0;
  int n_trees = 0;
  Graph(int num_nodes, int num_edges, int num_sim_pairs, int* ds, int *dt, int* sim1, int* sim2) 
  {
    // cout << "graph checkpoint 1" << endl;

    for(int j=0;j<100;j++)
    {
      results1[j] = 0;
      results2[j] = 0;
    }

    numNodes = num_nodes;
    numEdges = num_edges;
    numSimPairs = num_sim_pairs;

    for (int i=1; i<numNodes+1; i++)
    {
      // cout << "graph checkpoint 2" << endl;
      listOfObjects* a = new listOfObjects(-1);
      adj_list[i] = a;
      int* b = new int;
      par_list[i] = b;
      num_parents[i] = 0;
      int* c = new int;
      sim_list[i] = c;
      num_sims[i] = 0;
      collapsed[i] = i;
      grps[i]=0;
    }

    for(int i=0; i<numEdges; i++)
    {
      // cout << "graph checkpoint 4" << endl;

      desrcnodes[i] = ds[i];
      tarnodes[i] = dt[i];

      //add edge
      if(!(search(adj_list[desrcnodes[i]], tarnodes[i]) && search(adj_list[tarnodes[i]], desrcnodes[i])))
      {
        add_edge(adj_list, desrcnodes[i], tarnodes[i]);
        add_parent(par_list, tarnodes[i], desrcnodes[i], num_parents);
      }
    }

    for(int i=0; i<numSimPairs; i++)
    {
      // cout << "graph checkpoint 7" << endl;
      sim1src[i] = sim1[i];
      sim2src[i] = sim2[i];
    }

    // for(int i=0;i<numEdges;i++)
    // {
    //   cout << desrcnodes[i] << " " << tarnodes[i] << endl;
    // }

    // for(int i=0;i<numSimPairs;i++)
    // {
    //   cout << sim1src[i] << " " << sim2src[i] << endl;
    // }
    // printadjlist();
    // printparlist();
    similarity();
    // printsimilar();
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
    cout << "graph checkpoint 8" << endl;
    //to check printing adjacency list

    for(int i=1;i<numNodes+1;i++)
    {
      cout << i;
      cout << "->";
      listOfObjects* curr = adj_list[i];
      while(curr->next!=NULL)
      {
        curr = curr->next;
        cout << (curr->object) << ",";
      }
      cout << endl;
    }
  }

  void printparlist()
  {
    for(int i=1; i<numNodes+1; i++)
    {
      cout << "parents of " << i << " "; 
      for(int j=0;j<num_parents[i]; j++)
      {
        cout << par_list[i][j] << ",";
      }
      cout << endl;
    }
  }

  void printsimilar()
  {
    for(int i=1; i<numNodes+1; i++)
    {
      cout << "similar of " << i << " "; 
      for(int j=0;j<num_sims[i]; j++)
      {
        if(sim_list[i][j]!=0) cout << sim_list[i][j] << ",";
      }
      cout << endl;
    }
  }

  void printResults();
  void similarity();
  void task1();
  bool point2(int i,int j);
  void collapsefn();
  bool find(int n1, int n2);
};

#endif
