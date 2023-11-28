#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;

// Add code as appropriate for your implementation

void Graph::insertNode(int from_v, int to_v)
{
  int n1 = from_v - 1;
  int n2 = to_v - 1;

  nodes[n1].to[nodes[n1].tos] = &nodes[n2];
  nodes[n2].from[nodes[n2].froms] = &nodes[n1];
  nodes[n1].tos++;
  nodes[n2].froms++;
}

void Graph::checkSource()
{
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].froms == 0)
    {
      nodes[i].source = 1;
    }
  }
}

void Graph::insertSimilar(int similar1, int similar2)
{
  int n1 = similar1 - 1;
  int n2 = similar2 - 1;

  similar[n1][n2] = 1;
}

void Graph::checkSimilar3()
{
  // checking when only incoming edge is another node
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].froms == 1)
    {
      similar[i][nodes[i].from[0]->value - 1] = 1;
    }
  }
}

void Graph::checkSimilar2(int n)
{
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].source == 1)
      continue;

    for (int j = 0; j < numNodes; j++)
    {
      if (j == i or nodes[j].source == 1 or similar[i][j])
        continue;
      int similars_1 = 0;
      int similars_2 = 0;
      for (int k = 0; k < nodes[i].froms; k++)
      {
        for (int l = 0; l < nodes[j].froms; l++)
        {
          if (similar[nodes[i].from[k]->value - 1][nodes[j].from[l]->value - 1])
          {
            similars_1++;
            break;
          }
        }
      }
      for (int k = 0; k < nodes[j].froms; k++)
      {
        for (int l = 0; l < nodes[i].froms; l++)
        {
          if (similar[nodes[j].from[k]->value - 1][nodes[i].from[l]->value - 1])
          {
            similars_2++;
            break;
          }
        }
      }
      if (similars_1 == nodes[i].froms and similars_2 == nodes[j].froms)
      {
        similar[i][j] = 1;
        similar[j][i] = 1;
      }
    }
  }
  if (n == 0)
  {
    for (int i = 0; i < numNodes; i++)
    {
      for (int j = 0; j < numNodes; j++)
      {
        if (similar[i][j])
        {
          similarpairs[similarcount++] = i + 1;
          similarpairs[similarcount++] = j + 1;
        }
      }
    }
    return;
  }
  else
    checkSimilar2(n - 1);
}

void Graph::collapse()
{
  // completing equivalence
  for (int i = 0; i < numNodes; i++)
  {
    similar[i][i] = 1;
    for (int j = 0; j < numNodes; j++)
    {
      if (similar[i][j])
      {
        similar[j][i] = 1;
      }
      for (int k = 0; k < numNodes; k++)
      {
        if (similar[i][j] and similar[j][k])
        {
          similar[i][k] = 1;
        }
      }
    }
  }

  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (similar[i][j])
      {
        nodes[j].decomposed_value = max(i + 1, nodes[j].decomposed_value);
        nodes[i].decomposed_value = max(j + 1, nodes[i].decomposed_value);
      }
    }
  }

  for (int i = 0; i < numNodes; i++)
  {
    decomposed[nodes[i].decomposed_value - 1] = 1;
  }

  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < nodes[i].tos; j++)
    {
      // cout << i + 1 << " " << nodes[i].to[j]->value << endl;
      int exists = 0;
      for (int k = 0; k < countedges; k++)
      {
        if ((nodes[i].decomposed_value == collapsed_edges[k][0] and nodes[i].to[j]->decomposed_value == collapsed_edges[k][1]) or (nodes[i].decomposed_value == collapsed_edges[k][1] and nodes[i].to[j]->decomposed_value == collapsed_edges[k][0]))
          exists = 1;
      }
      if (nodes[i].decomposed_value == nodes[i].to[j]->decomposed_value)
        exists = 1;
      if (1 - exists)
      {
        collapsed_edges[countedges][0] = nodes[i].decomposed_value;
        collapsed_edges[countedges][1] = nodes[i].to[j]->decomposed_value;
        // cout << "EDGE:" << collapsed_edges[countedges][0] << " -- " << collapsed_edges[countedges][1] << endl;
        countedges++;
      }
    }
    for (int j = 0; j < nodes[i].froms; j++)
    {
      // cout << i + 1 << " " << nodes[i].from[j]->value << endl;
      int exists = 0;
      for (int k = 0; k < countedges; k++)
      {
        if ((nodes[i].decomposed_value == collapsed_edges[k][0] and nodes[i].from[j]->decomposed_value == collapsed_edges[k][1]) or (nodes[i].decomposed_value == collapsed_edges[k][1] and nodes[i].from[j]->decomposed_value == collapsed_edges[k][0]))
        {
          exists = 1;
        }
      }
      if (nodes[i].decomposed_value == nodes[i].from[j]->decomposed_value)
        exists = 1;
      if (1 - exists)
      {
        collapsed_edges[countedges][0] = nodes[i].decomposed_value;
        collapsed_edges[countedges][1] = nodes[i].from[j]->decomposed_value;
        // cout << "EDGE:" << collapsed_edges[countedges][0] << " -- " << collapsed_edges[countedges][1] << endl;
        countedges++;
      }
    }
  }
}

void Graph::printResults()
{
  ofstream myfile;
  myfile.open("outgraph.txt");

  // Printing the source nodes
  myfile << "Source nodes: ";
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].source == 1)
    {
      myfile << nodes[i].value << " ";
    }
  }
  myfile << "\n\nSimilar node pairs: ";

  for (int i = 0; i < similarcount; i += 2)
  {
    myfile << "(" << similarpairs[i] << "," << similarpairs[i + 1] << ") ";
  }

  myfile << "\n\nCollapsed graph:\n\n";
  int unique = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (decomposed[i] == 1)
    {
      unique++;
    }
  }
  myfile << unique << ":";
  for (int i = 0; i < numNodes; i++)
  {
    if (decomposed[i] == 1)
    {
      myfile << " " << i + 1;
    }
  }
  myfile << endl;
  // cout << countedges;
  for (int i = 0; i < countedges; i++)
  {
    myfile << collapsed_edges[i][0] << " " << collapsed_edges[i][1] << endl;
  }

  myfile.close();
}

#endif
