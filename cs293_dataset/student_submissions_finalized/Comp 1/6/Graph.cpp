#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::DFS(int v, int from, int* &visited, int* &from_lst_1, int* &from_lst_2, bool* &is_cycle, listOfObjects<int>* &stack_imp)
{
  list_BSTs[no_of_BSTs].insert(v);
  (visited[v])++;     
  if(visited[v] == 1)
    from_lst_1[v] = from;         // to update parent node of v is from 'from' during first travel
  else if(visited[v] == 2)
    from_lst_2[v] = from;         // to update parent node of v is from 'from' during second travel
  listOfObjects<int> *it_list = nodes[v].neighbour_list;
  while(it_list != nullptr)
  {
    int dest = it_list->object;
    if(visited[dest] >= 2)
    {
      stack_imp->check_for_cycles(dest, is_cycle);     // check for presence of cycle in the stack
      it_list = it_list->next;
      continue;
    }
    else if(visited[dest] == 1)
    {
      if(from_lst_1[v] == dest)                   //Conditon check- If path already traversed from dest to v during first visit of v, then there should no DFS movement from v to dest
      {
        it_list = it_list->next;
        continue;
      }
      else if(from_lst_2[v] == dest)              //Conditon check- If path already traversed from dest to v during second visit of v, then there should no DFS movement from v to dest
      {
        it_list = it_list->next;
        continue;
      }
      else
      {
        stack_imp->check_for_cycles(dest, is_cycle);       // check for presence of cycle in the stack
        stack_imp->insert_stack_elem(dest);                // insert element in stack
        DFS(dest, v, visited, from_lst_1, from_lst_2, is_cycle, stack_imp);
      }
    }
    else
    {
      stack_imp->insert_stack_elem(dest);                  // insert element in stack
      DFS(dest, v, visited, from_lst_1, from_lst_2, is_cycle, stack_imp);
    }
    it_list = it_list->next;
  }
  stack_imp->remove_stack_elem();                          // remove top element from stack
}

void Graph::modifiedDFS()
{
  connected_components = 0;
  elem_once = 0;
  elem_twice = 0;
  node_cycle = 0;
  no_of_BSTs = 0;
  list_BSTs = new BST[numNodes];

  int *visited_nodes = new int[numNodes + 1];         // int array to keep a track of no a times a node is visited
  bool* is_cycle = new bool[numNodes + 1];            // boolean array to keep a track of nodes in a cycle
  int *from_nodes_1 = new int[numNodes + 1];          // int array to keep a track of parent of nodes during first visit of node 
  int *from_nodes_2 = new int[numNodes + 1];          // int array to keep a track of parent of nodes during second visit of node
  listOfObjects<int> *stack_imp = new listOfObjects<int>(1);
  for (int i = 0; i <= numNodes; i++)
  {
    is_cycle[i] = false;
    visited_nodes[i] = 0;
    from_nodes_1[i] = 0;
    from_nodes_2[i] = 0;
  }
  int iter = 1;
  for(int iter = 1; iter<=numNodes; iter++)
  {
    if(visited_nodes[iter] == 0)
    {
      connected_components++;
      stack_imp = new listOfObjects<int>(iter);
      DFS(iter, 0, visited_nodes, from_nodes_1, from_nodes_2, is_cycle, stack_imp);
      no_of_BSTs++;
    }
  }
  node_cycle = 0;
  elem_once = 0;
  for(int i=1; i<=numNodes; i++)
  {
    if(is_cycle[i])
      node_cycle++;
    if(visited_nodes[i] == 1)
      elem_once++;
  }
  elem_twice = numNodes - elem_once;
  return;
}

void Graph::printResults()
{
  cout<<"No. of connected components: "<<connected_components<<endl;
  cout<<"No. of nodes visited once: "<<elem_once<<endl;
  cout<<"No. of nodes visited twice: "<<elem_twice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<node_cycle<<endl;
  cout<<"List of BSTs :- "<<endl;
  for(int i=0; i<no_of_BSTs; i++)
  {
    cout<<"BST No."<<i+1<<endl;
    list_BSTs[i].printBST(list_BSTs[i].root, "", false);
    cout<<endl;
  }

  
  return;
}

#endif
