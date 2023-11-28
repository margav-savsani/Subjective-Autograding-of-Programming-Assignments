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
  int numVisits[numNodes];
  for(int i = 0; i < numNodes; i++){
    numVisits[i] = 0;
  }
  int currIndex = 0;
  int connectedComponents = 0;
  while(true){
    if(currIndex >= numNodes){
      break;
    }

    if(numVisits[currIndex] != 0){
      currIndex++;
      continue;
    }
    BST* tree = new BST();
    myDFS(currIndex + 1, numVisits, tree);
    cout << "Tree "<< ++connectedComponents<<": " << endl;
    tree->print();
    // connectedComponents++;
    currIndex++;
  }

  cout << "Connected Components: " << connectedComponents << endl;

  int visitedOnce = 0, visitedTwice = 0;

  for(int i = 0; i < numNodes; i++){
    if(numVisits[i] == 1){
      visitedOnce++;
    }

    else{
      visitedTwice++;
    }
  }

  cout << "Number of Nodes Visited Once: " << visitedOnce << endl;
  cout << "Number of Nodes Visited Twice: " << visitedTwice << endl;
}

void Graph::printResults() {
  bool visited[numNodes];
  for(int i = 0; i < numNodes; i++){
    visited[i] = false;
  }
  int currIndex = 0;
  while(true){

    if(currIndex >= numNodes){
      break;
    }

    if(visited[currIndex]){
      currIndex++;
      continue;
    }
    int time = 0;
    actualDFS(currIndex + 1, visited, time);
    currIndex++;
  }

  int inCycle = 0;

  for(int i = 0; i < numNodes; i++){
    if(nodes[i].isInCycle){
      inCycle++;
    }
  }

  cout << "Nodes in Cycle: " << inCycle << endl;
  return;
}

void Graph::actualDFS(int numNode, bool* visited, int &time){
  nodes[numNode - 1].arrivalTime = time;
  visited[numNode - 1] = true;
  LinkedListNode* currNode = nodes[numNode - 1].AdjacenyList.getHead();

  while(currNode != nullptr){
    if(nodes[numNode - 1].parent == currNode->value){
      currNode = currNode->next;
      continue;
    }
    if(visited[currNode->value - 1] && nodes[currNode->value - 1].arrivalTime < nodes[numNode - 1].arrivalTime){
      nodes[numNode - 1].isInCycle = true;
      nodes[currNode->value - 1].isInCycle = true;
      int parent = nodes[numNode - 1].parent;
      while(parent != currNode->value){
        nodes[parent - 1].isInCycle = true;
        parent = nodes[parent - 1].parent;
      }
      currNode = currNode->next;
      continue;
    }
    if(!visited[currNode->value - 1]){
      nodes[currNode->value - 1].parent = numNode;
      time = time + 1;
      actualDFS(currNode->value, visited, time);
      currNode = currNode->next;
      continue;
    }

    currNode = currNode->next;
  }
}

void Graph::myDFS(int nodeNum, int* numVisits, BST* tree){
  tree->insert(nodeNum);
  numVisits[nodeNum - 1] ++;
  LinkedListNode* currNode = nodes[nodeNum - 1].AdjacenyList.getHead();

  while(currNode != nullptr){
    if(nodes[nodeNum - 1].parent1 == currNode->value || nodes[nodeNum - 1].parent2 == currNode->value){
      currNode = currNode->next;
      continue;
    }
    if(numVisits[currNode->value - 1] > 1){
      currNode = currNode->next;
      continue;
    }

    if(numVisits[currNode->value - 1] == 1){
      nodes[currNode->value - 1].parent2 = nodeNum;
      myDFS(currNode->value,numVisits, tree);
    }

    else{
      nodes[currNode->value - 1].parent1 = nodeNum;
      myDFS(currNode->value,numVisits, tree);
    }
    currNode = currNode->next;
  }
}

#endif
