#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::DFS(Node N,BST* bst){
  visited[N.value-1]++;
  bst->insert(N.value);
  // This stack is for checking cycles
  Stack.push_back(N);
  if(visited[N.value-1] == 2){
    NoOfNodesVisitedTwice++;
    // I have initialized no. of nodes visited once to the total no. of nodes
    // So now I am substracting them
    NoOfNodesVisitedOnce--;
  }
  for(auto node : UndirectedEdgeList[N.value-1]){
    Stack.push_back(nodes[node]);
      for(int start=0;start<Stack.size();start++){
        int val = Stack[start].value;
        for(int end=start+1;end<Stack.size();end++){
          if(Stack[end].value == val && (end-start)>2){
            for(int k=start+1;k<(end);k++){
              presentInCycle[Stack[k].value-1] = true;
              //For printing the elements in a cycle
              //cout << Stack[k].value << " ";
            }
            //cout << endl;
            break;
          }
        }
      }
      Stack.pop_back();
  }

  // Recursive calls
  for(auto node : AdjacencyList[N.value-1]){
    if(visited[node] < 2){
      int index=0;
      for (auto i :AdjacencyList[node]) {
        if (i == (N.value-1)) {
            AdjacencyList[node].erase(AdjacencyList[node].begin()+index);
            break;
        }
        index++;
      }
      DFS(nodes[node],bst);
    }
  }
  // Removing them from Stack since I am about to exit from DFS
  Stack.pop_back();
  return;
}

void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++){
    // Each if case will lead to a different Connected componenet
    if(visited[i] == 0){
      BST *tempBST = new BST();
      NoOfConnectedComponents++;
      DFS(nodes[i],tempBST);
      BSTrees.push_back(tempBST);
    }
  }
  return;
}

void Graph::printResults() {
  for(int i=0;i<numNodes;i++){
    if(presentInCycle[i]){NoOfNodesInACycle++;}
  }
  cout << "No. of connected components: " << NoOfConnectedComponents << endl;
  cout << "No. of nodes visited once: " << NoOfNodesVisitedOnce << endl;
  cout << "No. of nodes visited twice: " << NoOfNodesVisitedTwice << endl;
  cout << "No. of nodes that are present in a cycle: " << NoOfNodesInACycle << endl;
  for(auto tree : BSTrees){
    tree->printBST(" ");
  }
  return;
}

#endif
