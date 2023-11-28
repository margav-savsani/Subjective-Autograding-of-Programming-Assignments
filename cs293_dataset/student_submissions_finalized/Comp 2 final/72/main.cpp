#include "std_headers.h"
#include "graph.cpp"
using namespace std;

int main()
{
  // Reading in the number of nodes and edges
  int nnodes;
  cin >> nnodes;
  Graph graph(nnodes);
  int n1 = 0, n2 = 0;
  while (true)
  {
    cin >> n1 >> n2;
    if (n1 == -1 || n2 == -1)
      break;
    graph.addEdge(n1 - 1, n2 - 1);
  }

  // Reading the similar node pairs
  while (true)
  {
    cin >> n1 >> n2;
    if (n1 == -1 || n2 == -1)
      break;
    graph.addSim(n1 - 1, n2 - 1);
  }

  // Checking for the similar nodes
  for (int i = 0; i < nnodes; i++)
  {
    listOfObjects<Node> *poin = graph.nodes[i].adjin;
    if (poin == nullptr)
      continue;
    if (poin->next != nullptr)
      continue;
    graph.addSim(i, poin->object.idx);
  }

  int cn = 0;
  for (int i = 0; i < nnodes; i++)
  {
    if (!graph.source[i])
    {
      for (int j = 0; j < nnodes; j++)
      {
        if (j != i && !graph.source[j])
        {
          bool c1 = false;
          bool c2 = false;
          listOfObjects<Node> *poin = graph.nodes[i].adjin;
          while (poin != nullptr)
          {
            int m1 = poin->object.idx;
            c1 = false;
            for (int m2 = 0; m2 < nnodes; m2++)
            {
              if (graph.SimPresent(m1, m2) && graph.edgePresent(m2, j))
              {
                c1 = true;
                break;
              }
            }
            if (c1 == true && poin->next == nullptr)
              break;
            if (c1 == false)
              break;
            poin = poin->next;
          }
          poin = graph.nodes[j].adjin;
          while (poin != nullptr)
          {
            int m2 = poin->object.idx;
            c2 = false;
            for (int m1 = 0; m1 < nnodes; m1++)
            {
              if (graph.SimPresent(m2, m1) && graph.edgePresent(m1, i))
              {
                c2 = true;
                break;
              }
            }
            if (c2 == true && poin->next == nullptr)
              break;
            if (c2 == false)
              break;
            poin = poin->next;
          }
          if (c1 == true && c2 == true)
            graph.addSim(i, j);
        }
      }
    }
    if (cn == 0 && i == nnodes - 1)
    {
      cn = 1;
      i = -1;
    }
  }
  //Printing the source nodes
  graph.file << "Source nodes: ";
  for (int i = 0; i < nnodes; i++)
  {
    if (graph.source[i])
    {
      graph.file << graph.nodes[i].value << " ";
    }
  }
  graph.file << "\n\n";

  // Printing the similar node pairs
  graph.file << "Similar node pairs: ";
  for (int i = 0; i < nnodes * nnodes; i++)
  {
    if (graph.simarray[i] == 1)
    {
      int s1 = i / nnodes;
      int s2 = i % nnodes;
      graph.connected[s1] = 2;
      graph.connected[s2] = 2;
      graph.file << "(" << graph.nodes[s1].value << "," << graph.nodes[s2].value << ") ";
    }
  }
  graph.file << "\n\nCollapsed graph:\n\n";

  // Collapsing the graph recursively
  int ctt = 0;
  while (ctt == 0)
  {
    ctt = 1;
    for (int i = 0; i < nnodes * nnodes; i++)
    {
      int s1 = i / nnodes;
      int s2 = i % nnodes;
      if (s1 == s2)
        continue;
      if (graph.simarray[i] == 1)
      {
        ctt = 0;
        graph.collapse();
        break;
      }
    }
  }

  // Printing the collapsed graph
  int cnt = 0;
  for (int i = 0; i < nnodes; i++)
  {
    if (graph.connected[i] == 0 || graph.connected[i] == 2)
      cnt++;
  }
  graph.file << cnt << ": ";
  for (int i = 0; i < nnodes; i++)
  {
    if (graph.connected[i] == 0 || graph.connected[i] == 2)
      graph.file << i + 1 << " ";
  }
  graph.file << endl;

  for (int i = 0; i < nnodes * nnodes; i++)
  {

    if (graph.adj[i] == 1)
    {
      int s1 = i / nnodes;
      int s2 = i % nnodes;
      if (s1 == s2)
        continue;
      graph.file << s1 + 1 << "  " << s2 + 1 << endl;
    }
  }
}