#include "Graph.h"

void Graph::similarity1() // this similarity is based on rule no-1 mentioned and added into vector of pairs named "similar"
{
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (nodes[i].to_this == 0 and nodes[j].to_this == 0)
      {
        bool it = user_similar.find(make_pair(i + 1, j + 1)); // adding only if provieded by user
        if (it)
        {
          similar.push_back(make_pair(i + 1, j + 1));
        }
      }
    }
  }
}

void Graph::similarity2() // this similarity is based on rule no-3 mentioned and added into vector of pairs named "similar"
{
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (nodes[i].to_this == 1 && nodes[j].adjacency[i] == 1) // adding only if there is only one incoming edge that is from n2
      {
        similar.push_back(make_pair(i + 1, j + 1));
      }
    }
  }
}

void Graph::similarity3() // this similarity is based on rule no-2 mentioned and added into vector of pairs named "similar"
{
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (nodes[i].to_this != 0 && nodes[j].to_this != 0)
      {
        for (int k = 0; k < numNodes; k++)
        {
          for (int l = 0; l < numNodes; l++)
          {
            if (nodes[k].adjacency[i] == 1 && nodes[l].adjacency[j] == 1)
            {
              bool it = similar.find(make_pair(k + 1, l + 1));
              bool it1 = similar.find(make_pair(l + 1, k + 1)); // adding only if both (l+1,k+1) and (k+1,l+1) are both present
              bool it2 = similar.find(make_pair(i + 1, j + 1));
              if (it && it1 & i != j && !it2)
              {
                similar.push_back(make_pair(i + 1, j + 1));
                similarity3(); // calling another in case other one is missed
              }
            }
          }
        }
      }
    }
  }
}

void Graph::connectedComponents()
{
  // Mark all the vertices as not visited
  bool *visited = new bool[numNodes];
  for (int v = 0; v < numNodes; v++)
    visited[v] = false;

  for (int v = 0; v < numNodes; v++)
  {
    if (visited[v] == false)
    {
      // save all reachable vertices
      // from v
      Vector<int> v1;
      DFSUtil(v + 1, visited, v1);
      components.push_back(v1);
    }
  }
  delete[] visited;
}

void Graph::DFSUtil(int v, bool visited[], Vector<int> &vect)
{
  // Mark the current node as visited and save it
  visited[v - 1] = true;
  if (!vect.find(v))
    vect.push_back(v);
  // Recur for all the vertices
  // adjacent to this vertex
  for (int i = 0; i < numNodes; i++)
    if (!visited[i] && (mnodes[v - 1].adjacency[i] == 1 || mnodes[i].adjacency[v - 1] == 1))
      DFSUtil(i + 1, visited, vect);
}

void Graph::printResults()
{
  ofstream output;
  output.open("outgraph.txt"); // storing the output in file
  output << "Source nodes: ";
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].to_this == 0)
    {
      output << i + 1 << " ";
    }
  }
  output << endl;
  output << endl;
  similarity1();
  similarity2();
  similarity3();
  output << "Similar node pairs: ";
  for (int i = 0; i < similar.size(); i++)
  {
    mnodes[similar[i].first - 1].adjacency[similar[i].second - 1] = 1;
    mnodes[similar[i].second - 1].adjacency[similar[i].first - 1] = 1;
    output << "(" << similar[i].first << ", " << similar[i].second << ") ";
  }
  output << endl;
  output << endl;
  connectedComponents();

  output << "Collapsed graph: " << endl;
  output << components.size() << " : ";
  int a[components.size()];
  for (int i = 0; i < components.size(); i++)
  {
    a[i] = components[i].max();
    output << a[i] << " ";
  }
  output << endl;
  for (int r = 0; r < original.size(); r++)
  {
    for (int i = 0; i < components.size(); i++)
    {
      if (components[i].find(original[r].first))
        original[r].first = a[i];
      if (components[i].find(original[r].second))
        original[r].second = a[i];
    }
    if (original[r].first != original[r].second && !final.find(make_pair(original[r].first, original[r].second)))
      final.push_back(make_pair(original[r].first, original[r].second));
  }
  output << endl;
  for (int i = 0; i < final.size(); i++)
  {
    output << final[i].first << " " << final[i].second << endl;
  }
  return;
}
