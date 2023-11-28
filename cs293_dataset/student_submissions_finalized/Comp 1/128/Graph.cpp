#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::DFS(Node &n, BST* my_tree){
  if(!n.visitonce){
    n.visitonce = true;
  }
  else if(!n.visitwice){
    n.visitwice = true;
  }

  for(int i=0; i< n.adjacency.size(); i++){
    if( !n.adjacency[i]->visitwice && n.adjacency[i]->value != n.parent_1 ){
      my_tree->insert((n.adjacency[i])->value);
      if(n.adjacency[i]->visitonce){
        n.adjacency[i]->parent_2 = n.value;
      }
      else{
        n.adjacency[i]->parent_1 = n.value;        
      }

      DFS(*(n.adjacency[i]), my_tree);
    }
  }
}

void Graph::modifiedDFS() {
  // go through Node array and check visited
  for(int i = 0; i < numNodes; i++){
    if( nodes[i].visitonce ){
      continue;
    }
    component_trees[num_comp] = new BST(nodes[i].value);
    num_comp++;
    DFS(nodes[i], component_trees[num_comp-1]);
  }
  return;
}

void Graph::printResults() {
  cout << "No. of connected components: "<< num_comp<<endl;

  int deg_array[numNodes];
  int ones = 0;
  int twos = 0;
  for(int i=0; i<numNodes; i++){
    deg_array[i] = nodes[i].adjacency.size();
    if(nodes[i].visitonce){ones++;}
    if(nodes[i].visitwice){twos++;}
  }

  bool exists_leaf = false;

  do
  {
    exists_leaf = false;

    for(int i = 0; i < numNodes; i++){
      exists_leaf = exists_leaf || (deg_array[i] == 1);
      if( deg_array[i] == 1 ){
        deg_array[i] = 0;
        for(auto it : nodes[i].adjacency ){
          deg_array[it->value-1]--;
        }
      }
    }

  } while (exists_leaf);
  
  int count = 0;
  for(int i = 0 ; i < numNodes; i++){
    if(deg_array[i] >= 2){
      count++;
    }
  }

  cout << "No. of nodes visited once: " << ones<<endl;
  cout << "No. of nodes visited twice: " << twos<<endl;
  cout << "No. of nodes that are present in a cycle: "<< count << endl;
  for( int i=0; i<num_comp; i++){
    component_trees[i]->printBST("", true);
  }
  return;
}

#endif
