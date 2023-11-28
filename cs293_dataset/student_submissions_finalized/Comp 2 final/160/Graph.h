#include "Vector.h"
#include "Pair.h"

class Node // this is the node class for graph
{
public:
  int value;       // value contained in the node of graph
  int to_this;     // number of directed edges ending at this node
  int from_this;   // number of directed edges starting at this node
  bool *adjacency; // adjacency list of the node
  Node()           // constructor
  {
    value = -1;
    to_this = 0;
    from_this = 0;
    adjacency = nullptr;
  }
};

class Graph
{
  int numNodes;                   // number of nodes in the graph
  Vector<Pair<int>> user_similar; // this vector contains ordered pair of nodes which are declared as similar by user
  Vector<Pair<int>> similar;      // this vector contains ordered pair of nodes declared by similarity rules mentioned.
  Vector<Pair<int>> original;     // contains the edges for the original graph given
  Vector<Pair<int>> final;        // contains the edges for the graph obtained after collapsing
  Vector<Vector<int>> components; // contains vectors of nodes present in each component
  Node *nodes;                    // contains nodes of the original graph
  Node *mnodes;                   // nodes created for the similar nodes(like for a graph for easy calculation)

public:
  Graph()
  {
    cin >> numNodes;
    // initializing based on numNodes
    nodes = new Node[numNodes];
    mnodes = new Node[numNodes];
    for (int j = 0; j < numNodes; j++)
    {
      nodes[j].adjacency = new bool[numNodes];
      nodes[j].value = j + 1;
      mnodes[j].adjacency = new bool[numNodes];
      mnodes[j].value = j + 1;
    }

    // taking data inputs
    int i = 0;
    bool find = false;
    while (true)
    {
      int p, q;
      cin >> p >> q;
      if (p == -1 or q == -1)
      {
        find = !find;
        i++;
        if (i == 2)
          break;
        continue;
      }
      if (!find)
      {
        nodes[p - 1].from_this++;
        nodes[q - 1].to_this++;
        nodes[p - 1].adjacency[q - 1] = 1;
        original.push_back(make_pair(p, q));
      }
      if (find)
      {
        user_similar.push_back(make_pair(p, q));
      }
    }
  }

  ~Graph()
  {
    delete[] nodes;
    delete[] mnodes;
  }

  void similarity1();
  void printResults();
  void similarity2();
  void similarity3();
  void connectedComponents();
  void DFSUtil(int v, bool visited[], Vector<int> &vect);
};
