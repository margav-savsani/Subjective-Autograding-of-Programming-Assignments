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

void modDFS(int n, listOfObjects<Node> *l, adjacencyList adjList[], int num_visited[], BST b){
  listOfObjects<Node> *l1;  // for storing the order of traversal
  l1 = l;
  listOfObjects<Node> *l2;

  listOfObjects<Node> *a;   // list for traversing adjacency list
  a = adjList[n].list;

  bool isfound = false;

  while(a != nullptr){
    l1 = nullptr;
    l1 = l;

    if(num_visited[a->object.value - 1] == 0){
      b.insert(a->object.value);

      while(l1 != nullptr){
        l2 = nullptr;
        l2 = l1;
        l1 = l1->next;
      }

      l2->next = new listOfObjects<Node>(a->object);
      l2->next->prev = l2;
      num_visited[a->object.value - 1]++;
      modDFS(a->object.value-1, l, adjList, num_visited, b);
      a = a->next;
    }

    else if(num_visited[a->object.value - 1] == 1){
      l1 = l;
      isfound = false;
      while(l1 != nullptr){
        if(l1->object.value == adjList[n].n.value  || l1->object.value == a->object.value){
          isfound = true;
          if(l1->object.value == adjList[n].n.value){

            while(l1 != nullptr){
              l2 = nullptr;
              l2 = l1;
              l1 = l1->next;
            }

            l2->next = new listOfObjects<Node>(a->object);
            l2->next->prev = l2;

            num_visited[a->object.value - 1]++;
            modDFS(a->object.value-1, l, adjList, num_visited, b);
            a = a->next;
          }
          else if(l1->object.value == a->object.value){
            isfound = false;
            a = a->next;
            break;
          }

        }
        l1 = l1->next;
      }
      if(!isfound){
        while(l1 != nullptr){
          l2 = nullptr;
          l2 = l1;
          l1 = l1->next;
        }

        l2->next = new listOfObjects<Node>(a->object);
        l2->next->prev = l2;

        num_visited[a->object.value - 1]++;
        modDFS(a->object.value-1, l, adjList, num_visited, b);
        a = a->next;
        isfound = false;
      }
    
    }

    else{
      a = a->next;
    }
  }

}

void Graph::modifiedDFS() {
  
  //BST *b;
  b = new BST[numNodes]; // max number of possible connected components

  num_connected_com = 0;
  int j = 0;
  listOfObjects<Node> *l;
  //int k = 0;
  for(int i = 0; i < numNodes; i++){
    if(num_visited[i] == 0){
      num_connected_com++;
      b[j].insert(adjList[i].n.value);  // check here some issue
      l = new listOfObjects<Node>(adjList[i].n);
      modDFS(j, l, adjList, num_visited, b[j]);
      j++;

    }
  }
  
  return;
}

void Graph::printResults() {

  // No. of connected components: done
  // No. of nodes visited once: done
  // No. of nodes visited twice: done
  // No. of nodes that are present in a cycle:
  // Each BST that has been generated using the printBST function provided.

  int visited_once = 0;
  int visited_twice = 0;

  for(int i = 0; i < numNodes; i++){
    if(num_visited[i] == 1){
      visited_once ++;
    }
    else if(num_visited[i] == 2){
      visited_twice ++;
    }
  }

  cout << "No. of connected components: " << num_connected_com << endl;
  cout << "No. of nodes visited once: " << visited_once << endl;
  cout << "No. of nodes visited twice: " << visited_twice << endl;
  cout << "No. of nodes that are present in a cycle: " << endl;
  
  int i = 0;
  while(b[i].root != nullptr){
    b[i].printBST(b[i].root, "", true);
  }

  return;
}

#endif
