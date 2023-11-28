#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(int i) { object = i;next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class Node {
 public:
  int value;
  // int nvisited;
  //nvisited stores number of times node is visited
  //if visited = 0 --unvisited
  //if visited = 1 --visited once
  //if visited = 2 --visited twice no more visits
  listOfObjects<int> adjacencyList;    //adjacency list
  int adj_list_size;
  Node *left;
  Node *right;
  Node *parent;
  // insert other fields and methods as appropriate
  //constructor
  Node(){
    // nvisited = 0;
    adjacencyList = new listOfObjects<int >(0);
    adj_list_size = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

class BST {
  // Add your own field and members here
private:
  Node *root;

public:
  // Feel free to use the printBST function used earlier
  void insert(Node *root, int index, Node *nodes);
  void printBinaryTree(Node *root, const string& prefix, bool isLeft);
};

//function that returns true if nodes with index n1 and n2 are connected
bool connected(int n1, int n2, Node *nodes)
{
  listOfObjects<int > adjlistcopy = nodes[n1].adjacencyList;
  while(adjlistcopy.object != 0)
  {
    if(adjlistcopy.object == nodes[n2].value)
      return true;
    else
    {
      adjlistcopy = adjlistcopy->next;
      continue;
    }
  }
  return false;
}
  // for(int i=0; i < nodes[n1].adj_list_size; i++)
  // {
  //   if((nodes[n1].adjacencyList)[i] == nodes[n2].value)
  //   {
  //     return true;
  //   }
  // }
  // return false;


class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  int once_visited;
  int twice_visited;
  int conn_comp;
  int nodes_in_cycle;
  // Add appropriate fields as necessary for your implementation

  
 public:
  // map<int, list<int> > adj;  //adjacency list
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    once_visited = 0;
    twice_visited = 0;
    conn_comp = 0;
    nodes_in_cycle = 0;
    
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

      if(!connected(n1, n2, nodes))
      {
        // addedge(n1, n2);
        listOfObjects<int > adjlistcopy = nodes[n1].adjacencyList;
        if(nodes[n1].adjacencyList.object == 0)
        {
          nodes[n1].adjacencyList.object = nodes[n2].value;
          adjlistcopy = adjlistcopy->next;
        }
        else{
          nodes[n1].adjacencyList->next = nodes[n2].value;
          adjlistcopy = adjlistcopy->next;
        }
        if(nodes[n2].adjacencyList.object == 0)
        {
          nodes[n2].adjacencyList = nodes[n1].value;
          adjlistcopy = adjlistcopy->next;
        }
        else{
          nodes[n2].adjacencyList->next = nodes[n1].value;
          adjlistcopy = adjlistcopy->next;
        }
        
        // (nodes[n1].adjacencyList)[nodes[n1].adj_list_size] = nodes[n2].value;
        // nodes[n1].adj_list_size++;
        // (nodes[n2].adjacencyList)[nodes[n2].adj_list_size] = nodes[n1].value;
        // nodes[n2].adj_list_size++;
      
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
      else
      {
        continue;
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

  void DFS(int index, int *visited, BST *T);
 void modifiedDFS();
  void printResults();
};

#endif
