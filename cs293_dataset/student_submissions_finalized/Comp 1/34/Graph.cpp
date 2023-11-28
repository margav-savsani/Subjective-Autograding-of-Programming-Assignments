#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

// the below function checks if the edge between n1 and n2 is already added.
bool Graph::isPresent(int n1, int n2, int total_inserted)
{
  // cout << "Checking for index " << n1 << endl;
  // iterating over adjacecny list of n1 and looking for n2.
  listOfObjects<Node> *iter = nodes[n1].adjacent;
  while(iter != nullptr){
    // cout << iter->object.value << " " << n2 << endl;
    if(iter->object.value == n2+1){return true;}
    iter = iter->next;
  }
  // cout << "======================\n";
  return false;
}
void Graph::modifiedDFS()
{
  // iterating over all nodes and choosing those node for dfs which are not visited.
  // it will seperate the components .
  while (true)
  {
    // if all the nodes are visited then source will be -1 and we will end the function.
    int source = -1;
    for (int i = 0; i < numNodes; i++)
    {
      if (!nodes[i].visit1){
        source = i;
        break;
      }
      i++;
    }
    // if all the nodes are visited then source will be -1 and we will end the function.
    if (source == -1){return;}
    // if we found the unvisited node we increment the total component.
    total_comp++;
    if(tree == nullptr){
      tree = new listOfObjects<BST*>(new BST(source+1));
    }
    else{
      tree->next = new listOfObjects<BST*>(new BST(source+1));
      tree->next->prev = tree;
      tree = tree->next;
    }
    // -2 indicates root node.
    DFS(-2, source, true);
  }
  std::cout << "while ended\n";
  return;
}
// the below function traverses one component using the modified dfs rules.
void Graph::DFS(int par, int source, bool start){
  // to avoid the bidirection of edge in the dfs I comapred the values of parents.
  if(nodes[source].par1 == par || nodes[source].par2 == par)return;
  // if twice visited return.
  if(nodes[source].visit1 == true && nodes[source].visit2 == true)return;
  // update visits.
  if(nodes[source].visit1 == false)nodes[source].visit1 = true;
  else nodes[source].visit2 = true;
  if(!start){
    tree->object->insert(source+1);
  }
  // updating par1 nad par2.
  if(nodes[source].par1 == -1)nodes[source].par1 = par;
  else if(nodes[source].par2 == -1)nodes[source].par2 = par;
  // iterating over all the adjacent list and applying dfs appropriately
  listOfObjects<Node> *iter = nodes[source].adjacent;
  while(iter != nullptr){
    if(iter->object.value-1 != par){DFS(source, iter->object.value-1, false);}
    iter = iter->next;
  }
}
void Graph::printResults()
{
  int once = 0;
  int twice = 0;
  int thrice = 0;
  std::cout << "Total_component : " << total_comp << std::endl;
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].visit2){twice++;}
    else once++;
    // if(nodes[i].isCycle){cycle++;cout << "cycle nodes : " << i << endl;}
    // if(nodes[i].total_visit == 2)thrice++;
  }
  std::cout << "Once visited : " << once << std::endl;
  std::cout << "Twice visited :" << twice << std::endl;
  // since incycle = twice visited.
  std::cout << "In cycle :" << twice << std::endl;
  // std::cout << "Thrice visited :" << thrice << std::endl;
  while(tree != nullptr){
    cout << "==========================\n";
    tree->object->printBST("",tree->object);
    tree = tree->prev;
    cout << "--------------------------\n";
  }
  return;
}
#endif
