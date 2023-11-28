#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::addEdge(int src, int dest)
{
  // cout<<src<<":"<<dest<<endl;
  edges[src-1][dest-1] = true;
  source[dest-1] = false;
}

void Graph::printSrcNodes()
{
  cout << "Source Nodes: ";
  for (int i = 0; i < numNodes; i++)
  {
    if (source[i])
    {
      cout << i + 1 << " ";
    }
  }
  cout << endl;
}
void Graph::printSimilar()
{
  cout << "Similar node pairs: ";
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (similar[i][j])
      {
        cout << "(" << i + 1 << "," << j + 1 << ")";
      }
    }
  }
  cout << endl;
}
void Graph::print()
{
  cout << "Graph: ";
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (edges[i][j])
      {
        cout << "(" << i + 1 << "," << j + 1 << ")";
      }
    }
  }
  cout << endl;
}
void Graph::print_collapsed()
{
  int num=0;
  cout << "Collapsed graph: \n";
  cout<<endl;
  for (int i = 0; i < numNodes; i++)
  {
    if (exist[i])
    {
      num++;
    }
  }
  cout<<num<<":";
  for (int i = 0; i < numNodes; i++)
  {
    if (exist[i])
    {
      cout<<" "<<i+1;
    }
  }
  cout<<endl;
  for (int i = 0; i < numNodes; i++)
  {
    if(exist[i]){
    for (int j = 0; j < numNodes; j++)
    {
      if(exist[i] && exist[j]){
      if (edges[i][j])
      {
        cout << i + 1 << " " << j + 1 <<endl;
      }
      }
    }
    }
  }
}
bool Graph::checkSimilar(int n1, int n2)
{
  if (similar[n1][n2])
  {
    // cout<<"1\n";
    return true;
  }
  else
  {
    bool found = false;
    int incoming = 0;
    for (int src_n1 = 0; src_n1 < numNodes; src_n1++)
    {
      if (edges[src_n1][n1])
      {
        incoming++;
        if (src_n1 == n2)
        {
          found = true;
        }
      }
    }
    if (incoming == 1 && found)
    {
      // cout<<"2\n";
      return true;
    }
    bool ans1 = false;
    bool ans2 = false;

    for (int src_n1 = 0; src_n1 < numNodes; src_n1++)
    {
      if (edges[src_n1][n1])
      { ans1=false;
        for (int src_n2 = 0; src_n2 < numNodes; src_n2++)
        {  
          if (edges[src_n2][n2])
          {
            if (checkSimilar(src_n1, src_n2))
            {
              ans1=true;
              break;
              
            }
          }
        }
        if(!ans1){
          return false;
        }
      }
    }

     for (int src_n1 = 0; src_n1 < numNodes; src_n1++)
    {
      if (edges[src_n1][n2])
      { ans2=false;
        for (int src_n2 = 0; src_n2 < numNodes; src_n2++)
        {  
          if (edges[src_n2][n1])
          {
            if (checkSimilar(src_n1, src_n2))
            {
              ans2=true;
              break;
              
            }
          }
        }
        if(!ans2){
          return false;
        }
      }
    }
if(ans1 && ans2){
    return true;
}
return false;
  }
}

void Graph::createEquivalence()
{
  for (int i = 0; i < numNodes; i++)
  {
    similar[i][i] = true;
    for (int j = 0; j < numNodes; j++)
    {
      if (similar[i][j])
      {
        similar[j][i] = true;
      }
    }
  }

  bool new_sim[numNodes][numNodes];
  // while(true){
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      bool new_ans = false;
      for (int k = 0; k < numNodes; k++)
      {
        new_ans = new_ans ||  (similar[i][k] && similar[k][j]);
      }
      new_sim[i][j] = similar[i][j] || new_ans;
    }
  }
  bool same=true;
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if(similar[i][j]!=new_sim[i][j]){
        same=same*false;
      }
      similar[i][j]=new_sim[i][j];
    }
  }
  //printSimilar();
  if(same){
    return;
  }
  else{
    createEquivalence();
  }
}
void Graph::processSimilar()
{
  for (int src = 0; src < numNodes; src++)
  {
    for (int dest = 0; dest < numNodes; dest++)
    {
      if (checkSimilar(src, dest))
      {
        // cout<<"huh?\n";
        addSimilar(src, dest);
      }
    }
  }
}
void Graph::collapse(){
  for (int n1 = 0; n1 < numNodes; n1++)
  {
    for (int n2 = 0; n2 < numNodes; n2++)
    {
      
      if(similar[n1][n2] && n1!=n2 && exist[n2]){
        for(int dest=0;dest<numNodes;dest++){
          if(exist[dest] && n2!=dest){
          edges[n2][dest]=edges[n2][dest] || edges[n1][dest];
          edges[dest][n2]=edges[dest][n2] || edges[dest][n1];
          }
        }
        exist[n1]=false;
        break;
      }
    }
  }
}
void Graph::addSimilar(int node1, int node2)
{
  similar[node1][node2] = true;
}

#endif
