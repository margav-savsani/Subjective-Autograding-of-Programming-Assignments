#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include <vector>
#include <algorithm>

void Graph::DFS(Node node, BST *b,int parent)
{
  b->insert(node.value);

  instack[node.value - 1]++;
  if (instack[node.value - 1]==1)
      {
        nodes[node.value-1].st_pos[0]=stack.size();
      }
      else if (instack[node.value - 1]==2)
      {
        nodes[node.value-1].st_pos[1]=stack.size();
      }
  stack.push_back(node.value - 1);

  //cout << "parent:"<<node.value-1<< endl;
  visited[node.value - 1]++;

  for (auto neighbour : node.adjacencyList)
  {
   
      //cout << "neighbour:"<<neighbour<< endl;
     if(neighbour!=parent){
    if (instack[neighbour] != 0)
    {
       //cout << "neighbour_instack:"<<neighbour<< endl;
      int start;
      if (instack[neighbour] == 1)
      {
        start = nodes[neighbour].st_pos[0];
      }
      else if (instack[neighbour] == 2)
      {
        start = nodes[neighbour].st_pos[1];
      }
      for (int i = start+1; i < stack.size(); i++)
      {
        cycle[stack[i]] = true;
        //cout<<"true:"<<stack[i]<<endl;
      }
    }
     
    if (visited[neighbour] <= 1 && !edges[node.value-1][neighbour])
    {
      edges[node.value-1][neighbour]=true;
      edges[neighbour][node.value-1]=true;
      // int ind = 0;
      // for (auto it : nodes[neighbour].adjacencyList)
      // {
      //   if (it == node.value - 1)
      //   {
      //     nodes[neighbour].adjacencyList.erase(nodes[neighbour].adjacencyList.begin() + ind);
      //     break;
      //   }
      //   ind++;
      // }

      DFS(nodes[neighbour], b, node.value-1);
    }
     }
  }
   for (auto neighbour : node.adjacencyList)
  {
    edges[node.value-1][neighbour]=false;
    edges[neighbour][node.value-1]=false;
  }
  stack.pop_back();
  instack[node.value - 1]--;
  return;
}

void Graph::modifiedDFS()
{

  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 0)
    {
      BST *b = new BST();
      DFS(nodes[i], b,-1);
      trees.push_back(b);
    }
  }

  return;
}

void Graph::printResults()
{
  int visited_once = 0;
  int visited_twice = 0;
  int cycles = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 1)
    {
      visited_once++;
    }
    if (visited[i] == 2)
    {
      visited_twice++;
    }
    if (cycle[i])
    {
      cycles++;
    }
  }

  cout << "No. of connected components: " << trees.size() << endl;
  cout << "No. of nodes visited once: " << visited_once << endl;
  cout << "No. of nodes visted twice: " << visited_twice << endl;
  cout << "No. of nodes that are present in a cycle: " << cycles << endl;
  for (auto tree : trees)
  {
    tree->printBST("");
    cout << "===============================================\n";
  }
  return;
}

#endif
