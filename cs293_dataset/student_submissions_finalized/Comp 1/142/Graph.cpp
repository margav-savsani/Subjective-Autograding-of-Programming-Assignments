#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;

void BST::insert(Node *root, int index, Node *nodes) {
    // if(find(value))return false;
    // Node new_node = nodes[index];
    while(root!=nullptr){
        if(root->value == nodes[index].value) return ;
        if(root->value < nodes[index].value) insert(root->left, index, nodes);
        else insert(root->right, index, nodes);
    }
    return ;
}

void Graph::DFS(int index, int *visited, BST *T)
{ 
  while(nodes[index].adjacencyList.object != 0 )
  {
      visited[index]++;
      //if 0 to 1 .... once_visited++
      //if 1 to 2 .... once_visited-- and twice_visited++
      int adj_vertex = nodes[index].adjacencyList.object -1;
      if(visited[adj_vertex]==1)
      {
        once_visited++;
      }
      else if(visited[adj_vertex]==2)
      {
        once_visited--;
        twice_visited++;
      }
      if(visited[adj_vertex] == 0 || visited[adj_vertex] == 1)
      {
        T->insert(&nodes[index],adj_vertex, nodes);
        DFS(adj_vertex, visited, T);
      }
      nodes[index].adjacencyList = nodes[index].adjacencyList->next;
    
  }
  //ARRAY IMPLEMENTATION(WITHOUT LISTOFOBJECTS)
  // nodes[index].adj_list_size
  // for (int j = 0 ; j < nodes[index].adj_list_size; j++) 
  // {
  //   int adj_vertex = (nodes[index].adjacencyList)[j] - 1;
  //   cout << adj_vertex << endl;
  //   if(visited[adj_vertex] == 0 || visited[adj_vertex] == 1)
  //   {
  //     visited[adj_vertex]++;
  //     //if 0 to 1 .... once_visited++
  //     //if 1 to 2 .... once_visited-- and twice_visited++
  //     if(visited[adj_vertex]==1)
  //     {
  //       once_visited++;
  //     }
  //     else if(visited[adj_vertex]==2)
  //     {
  //       once_visited--;
  //       twice_visited++;
  //     }
  //     T->insert(&nodes[index],adj_vertex, nodes);
  //     DFS(adj_vertex, visited, T);
  //   }
  // }
}
void Graph::modifiedDFS() {
  int visited[numNodes];
   //'visited' array stores the number of times each vertex is visited, index of vertex is same as that in array 'nodes' 
  for(int i = 0; i < numNodes; i++)
  {
    visited[i] = 0;
  }
  for(int i = 0; i < numNodes; i++)
  {
    if(visited[i] == 0)
    {
      conn_comp++;
      BST *T = new BST();
      DFS(i, visited, T);
      // T->printBinaryTree();
    }
    else continue;
  }
  return;
}

void Graph::printResults() {
  cout << "No. of connected components: " << conn_comp << endl;
  cout << "No. of nodes visited once: " << once_visited << endl;
  cout << "No. of nodes visited twice: " << twice_visited << endl;
  cout << "No. of nodes that are present in a cycle: " << nodes_in_cycle << endl;        

  return;
}

void BST::printBinaryTree(Node *root, const string& prefix, bool isLeft)
  {
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->value;
    cout << endl;
    Node *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  /*
  else {
    cout << "NULL tree" << endl;
  }
  */
  }

#endif
