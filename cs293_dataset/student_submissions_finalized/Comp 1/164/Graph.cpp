#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for (int i = 0; i < numNodes;i++)
    {
      nodes[i].color=0;//equates color of every node to zero ie white
    }
    for (int i = 0; i < numNodes; i++)
    {
      if(nodes[i].color==0)
      {
        newDFS(i,-1);//reccursive call for each node
        no_co++;
        count=1;

      }
    }
    
    for (int i = 0; i < numNodes;i++)
    {
      nodes[i].color=0;//equates color of every node to zero ie white
    }
    for (int i = 0; i < numNodes; i++)
    {
      if(nodes[i].color==0)
      {
        DFS(i,-1);//reccursive call for each node
        count=1;
        no_co++;

      }
    }
  return;
}

void Graph::printResults() {
  b.printBST("");
    for (int i = 0; i < numNodes; i++)
    {
      if(nodes[i].no_v==1)
      {
        one_time++;//counts the numbe of nodes visited once
      }
      if(nodes[i].no_v==2)
      {
        two_time++;//counts the numbe of nodes visited twice
      }
    }
    cout<<"No. of connected components:"<<no_co<<endl;//prints the number of connected components
    cout<<"No. of nodes visited once:"<<one_time<<endl;//prints the number of nodes visited once
    cout<<"No. of nodes visited twice:"<<two_time<<endl;// prints the number of nodes visited twice
    int n=0;
      cout<<"Elements which are present in a cycle:"<<endl;

    for (int i = 0; i < numNodes; i++)
    {
      if(nodes[i].incycle==1)
      {cout<<i+1<<endl;n++;}//prints the elements in the cycle

    }
    cout<<"Total no of elements in the cycle:"<<n<<endl;//prints the total number of elements in the cycle
  return;
}

#endif
