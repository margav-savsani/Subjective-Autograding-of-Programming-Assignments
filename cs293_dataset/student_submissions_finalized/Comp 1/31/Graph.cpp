#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void addtolist(listOfObjects<int>* listSofarend, int value){
  listSofarend->next = new listOfObjects<int>(value);
  (listSofarend->next)->prev = listSofarend;
}

void removefromlist(listOfObjects<int>* listSofarend){
  listSofarend->next = NULL;
}
// Add code as appropriate for your implementation
void Graph::doDFS(int currNode,listOfObjects<BST>* tList, int parent,listOfObjects<int>* listSofar, listOfObjects<int>* listSofarend){
  //cout << "curr: " << currNode << " par: " << parent << endl;
  visited[currNode]++;

  tList->object.insert(nodes[currNode].value);
  addtolist(listSofarend,currNode);
  listSofarend = listSofarend->next;

  listOfObjects<int>* currList = adjList[currNode]->next;
  while(currList!=NULL){
    int adjNode = currList->object;
    if(visited[adjNode]>0 && adjNode!=parent){
      if(InaCycle[currNode]==0 || InaCycle[parent]==0){
        listOfObjects<int>* list = listSofarend;
        bool b=false;
        while(list!=NULL){
          InaCycle[list->object]++;
          if(list->object==adjNode || (list->object==currNode&&b==true) ){break;}
          list = list->prev;
          b = true;
        }
      }
    }
    if(visited[adjNode]<2 && adjNode!=parent){
      doDFS(adjNode,tList,currNode, listSofar, listSofarend);
    }
    currList = currList->next;
  }

  listSofarend = listSofarend->prev;
  removefromlist(listSofarend);

  return;
}
void Graph::modifiedDFS() {
  listOfObjects<BST>* tList = treeList;
  for(int i=0; i<numNodes; i++){
    if(visited[i]==0){
      numConnComp++;
      listOfObjects<int>* listSofar = new listOfObjects<int>(-1);
      doDFS(i,tList,-1,listSofar, listSofar);
      tList->next = new listOfObjects<BST>(BST());
      tList = tList->next;
    }
  }
}

void Graph::printResults() {
  cout << "No.of connected components: " << numConnComp << endl;
  int vtwice=0;
  int vonce=0;
  for(int i=0; i<numNodes; i++){
    if(visited[i]==1){
      vonce++;
    }
    else if(visited[i]==2){
      vtwice++;
    }
  }
  int nodesincycle=0;
  for(int i=0; i<numNodes; i++){
    if(InaCycle[i]!=0){
      nodesincycle++;
    }
  }
  cout << "No.of nodes visited once: " << vonce << endl;
  cout << "No.of nodes visited twice: " << vtwice << endl;
  cout << "No. of nodes that are present in a cycle: " << nodesincycle << endl;
  listOfObjects<BST>* l = treeList;
  while(l!=NULL){
    l->object.printBST("");
    cout << "\n";
    l = l->next;
  }
  return;
}

#endif
