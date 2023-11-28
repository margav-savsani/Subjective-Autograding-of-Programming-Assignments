#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::DFS(int index){

  dummy[index] = 1;
  listOfObjects<int> *p = nodes[index].adjlist;

  while(p!=nullptr){

    if(dummy[p->object]==0){
      dumpar[p->object] = index;
      DFS(p->object);
    }

    else{
      if(p->object!=dumpar[index]){
        incycle[index] = 1;
        incycle[p->object] = 1;
      }
    }

    p = p->next;
  }
}

void Graph::modifiedDFS(int s) {
  
  static int recursions = 0;

  recursions++; 
  visited[s]++;
  listOfObjects<BST*> *imp = bsts;
  while(imp->next!=nullptr){
    imp = imp->next;
  }
  imp->object->insert(s+1);

  listOfObjects<int> *p = nodes[s].adjlist;

  while(p!=nullptr){
    if(visited[p->object]==0){
      parent[p->object] = s;
    }

    if(visited[p->object]!=2 && p->object!=parent[s]){
      modifiedDFS(p->object);
    }

    p = p->next;
  }

  if(recursions==1){
    int k = 1;
    while(k<numNodes){
      if(visited[k]==0){
        listOfObjects<BST*> *later = new listOfObjects<BST*>(new BST());
        listOfObjects<BST*> *last  = bsts;
        while(last->next!=nullptr){
          last = last->next;
        }

        later->prev = last;
        last->next = later;

        modifiedDFS(k);
      }

      k++;
    }
  }

  recursions--;
  return;
}

void Graph::printResults() {

  listOfObjects<BST*> *p = bsts;
  int count = 0;

  while(p!=nullptr){
    count++;
    p = p->next;
  }

  cout << "No. of connected components: " << count << endl;

  int once=0;
  for(int i=0;i<numNodes;i++){
    if(visited[i]==1){
      once++;
    }
  }

  cout << "No. of nodes visited once: " << once << endl;

  int twice = numNodes-once;
  cout << "No. of nodes visited twice: " << twice << endl;

  for(int i=0;i<numNodes;i++){
    if(incycle[i]==0){
      DFS(i);

      for(int j=0;j<numNodes;j++){
        dummy[j] = 0;
        dumpar[j] = -1;
      }
    }
  }

  int number = 0;
  for(int i=0;i<numNodes;i++){
    if(incycle[i]==1){
      number++;
    }
  }

  cout << "No. of nodes that are present in a cycle: " << number << endl;

  p = bsts;
  while(p!=nullptr){
    p->object->printBST("");

    p = p->next;
  }

  return;
}

#endif
