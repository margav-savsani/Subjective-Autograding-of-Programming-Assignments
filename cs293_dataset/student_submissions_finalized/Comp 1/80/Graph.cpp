#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

int n_ones = 0;
int n_twos = 0;


int** matrix;




void my_dfs(int start, Node* node_arr, int* visited, int prev, BST* bst){
  visited[start]+=1;
  if(prev!=-1){
    matrix[prev][start]=1;
  }
  // cout << "got prev details" << prev << endl;

  Node* n = &node_arr[start];
  linked_list* mark1 = n->start;


  while(mark1!=nullptr){
    if(mark1->node_number==prev){
      if(mark1->prev==nullptr && mark1->next==nullptr){
        // cout << "a" << endl;
        n->start=mark1->next;
        n->end = mark1->next;
      }
      else if(mark1->prev==nullptr){
        // cout << "b" << endl;
        n->start = mark1->next;
        mark1->next->prev=nullptr;
      }
      else if(mark1->next==nullptr){
        // cout << "c" << endl;
        n->end = mark1->prev;
        mark1->prev->next=nullptr;
      }
      else{
        // cout << "d" << endl;
        mark1->prev->next = mark1->next;
        mark1->next->prev = mark1->prev;
      }
    }
    mark1=mark1->next;
  }

  
  n_ones+=1;
  bst->insert(start+1);
  // cout << "visiting " << start+1 << endl;
  linked_list* mark = node_arr[start].start;

  
  linked_list* marker = node_arr[start].start;
  while(marker!=nullptr){
    // cout << "bordering nodess " << marker->node_number+1 << endl;
    marker=marker->next;
  }

  while(mark!=nullptr){
    if(visited[mark->node_number]<2 && mark->node_number!=prev /*&& !node_arr[start].exists_in_to_backtracking_list(mark->node_number)*/ ){
      if(visited[mark->node_number]==1){
        n_twos+=1;
        n_ones-=2;
      }

      my_dfs(mark->node_number, node_arr, visited, start, bst);
      // node_arr[start].add_to_backtracking_list(mark->node_number);
    }
    mark=mark->next;
  }

}




void Graph::modifiedDFS() {

  int visited[numNodes];

  matrix = new int*[numNodes];
  for(int i =0; i<numNodes; i++){
    matrix[i] = new int[numNodes];
    for(int j=0; j<numNodes; j++){
      matrix[i][j] = 0;
    }
  }



  for(int i = 0; i<numNodes; i++){
    visited[i]=0;
  }

  for(int i = 0; i<numNodes; i++){
    if(visited[i]<1){
      BST* my_bst = new BST();
      // cout << "starting to search from node " << i+1 << endl;
      linked_list* marker = nodes[i].start;
      while(marker!=nullptr){
        // cout << "bordering node " << marker->node_number+1 << endl;
        marker=marker->next;
      }
      n_ones = 0; n_twos = 0;
      my_dfs(i, nodes, visited, -1, my_bst);
      num_ones+=n_ones;
      num_twos+=n_twos;
      num_components+=1;

      if(my_bst_list==nullptr){
        my_bst_list = new BST_linked_list;
        bst_list_marker = my_bst_list;
        my_bst_list->object=my_bst;
        // my_bst->printBST("", false);
      }
      else{
        bst_list_marker->next = new BST_linked_list;
        bst_list_marker->next->object = my_bst;
        bst_list_marker = bst_list_marker->next;
        // my_bst->printBST("", false);
      }
    }
  }
  return;
}

void Graph::printResults() {
  cout << "No. of connected components: " << num_components << endl;
  cout << "No. of nodes visited once: " << num_ones << endl;
  cout << "No. of nodes visited twice: " << num_twos << endl;
  cout << "No. of nodes that are present in a cycle: " << num_twos << endl;
  cout << "Now printing BSTs:" << endl;

  BST_linked_list* my_bst_mark = my_bst_list;
  while (my_bst_list!=nullptr){
    my_bst_list->object->printBST("", false);
    my_bst_list = my_bst_list->next;

  }
  
   
  return;
}

#endif
