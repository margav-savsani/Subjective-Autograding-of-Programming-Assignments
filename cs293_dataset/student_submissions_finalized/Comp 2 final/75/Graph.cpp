#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
#define NEG_INF -1000

bool Graph:: insert(int n1, int n2) {// Adds an edge from n1 to n2 node
    // if (n1 == n2) {return false;} // cannot add an edge from the same node to iteself
      bool insert1 = false;
      bool insert2 = false;
      // Add n2 to the list of n1
      Node* toAdd = new Node(n2+1);
      Node* currNode = nodes[n1].list;

      if (currNode==nullptr){
        nodes[n1].list = toAdd;
        parents[n2].add(n1+1);
        insert1 = true;
      }
      else{
        bool found = false;
        while(currNode->next!=nullptr){
          if(currNode->value == n2+1){
            found = true;
            break;
          }
          currNode = currNode->next;
        }
        if(currNode->value == n2+1){
            found = true;
        }

        if (!found){
          currNode->next = toAdd;
          insert1 = true;
        }
      }
      if(insert1){
        outEdges[n1]++;inEdges[n2]++;
        parents[n2].add(n1+1);
      }
      return (insert1);
    }

void Graph::printGraph(){
    for (int i = 0; i<numNodes;i++){
      cout<<nodes[i].value<<" -----> ";

      Node* currNode = nodes[i].list;
      while(currNode!=nullptr){
        cout<<currNode->value<<" | ";
        currNode = currNode->next;
      }
      cout<<endl;
    }
  }
Graph:: Graph(int nNodes)
{
    numNodes = nNodes;
    nodes = new Node[numNodes];
    inEdges = new int[numNodes];
    outEdges = new int[numNodes];
    visited = new bool[numNodes];
    parents = new myList<int>[numNodes];
    index = 0;
    maxDistance = new int[numNodes];
    visitedDFS = new bool[numNodes];
    numComponents = 0;
    compNum = new int[numNodes];

    for(int i = 0 ; i<numNodes;i++){
        inEdges[i] = 0;
        outEdges[i] = 0;
        visited[i] = false; 
        maxDistance[i] = NEG_INF;
    }
    
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
  }
void Graph:: topologicalSort(int sourceArray[]){ 
	for (int i = 0; i < numSource; i++){
      int* stack = new int[numNodes];
      recTopological(sourceArray[i], stack); 

      // setting the max distance of source to be 0
      maxDistance[sourceArray[i]-1] = 0;
      while (index != 0) {
        // Get the next vertex from topological order
        int u = stack[--index];
        // Update distances of all adjacent vertices
        if (maxDistance[u-1] != -1000) {
            Node* currNode = nodes[u-1].list;
            while(currNode!=nullptr){
                if (maxDistance[currNode->value -1] < maxDistance[u-1] + 1){
                    maxDistance[currNode->value -1] = maxDistance[u-1] + 1;}
                currNode = currNode->next;
            }
        }
      }
      index = 0;
  }
}
void Graph:: recTopological(int v, int stack[]){
  visited[v-1] = true; 

  // go through its adjacent node to do recursive topological sort
  Node* currNode = nodes[v-1].list;
  while(currNode!=nullptr){
    if(visited[currNode->value -1]==false){
      recTopological(currNode->value, stack);
    }
    currNode = currNode->next;
  }

	stack[index] = v;
  index++;
}
bool Graph:: find(int n1, int n2){// checks whether n1->n2 exists
  Node* currNode = nodes[n1-1].list;
  bool found = false;
  while(currNode!=nullptr){
    if(currNode->value == n2){
      found = true;
      break;
    }
    currNode = currNode->next;
  }

  return(found);
}
void Graph:: recDFS(int v){
  visitedDFS[v] = true; 
  compNum[v] = numComponents;
  // go through its adjacent node to do recursive topological sort
  Node* currNode = nodes[v].list;
  while(currNode!=nullptr){
    if(visitedDFS[currNode->value -1]==false){
      recDFS(currNode->value-1);
    }
    currNode = currNode->next;
  }
}
void Graph:: DFS(){
  int pointer = 0;
  while(pointer<numNodes){
    //DFS
    recDFS(pointer);// does DFS on the index of the node which is not visited
    numComponents++;
    while(visitedDFS[pointer]!=false){
      pointer++;
    }
  }
}
      

#endif
