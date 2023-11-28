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
  for(int dfsStartIdx = 0; dfsStartIdx < numNodes; dfsStartIdx++){ // Go through all vertices
    if(nodes[dfsStartIdx].visitedCount == 0){ // If vertex unexplored
      nodes[dfsStartIdx].visitedCount++; // Node has been visited once more

      TreeNode* newRoot = new TreeNode(dfsStartIdx+1); // New BST roo
      BST newBST = BST(newRoot);
      // Add this new BST root to the components list
      if(components == nullptr){
        components = new linkedListNode<BST>(newBST);
      } else{
        linkedListNode<BST>* newLLNode = new linkedListNode(newBST);
        newLLNode->next = components;
        components->prev = newLLNode;
        components = newLLNode;
      }

      // Instantiate a new path
      path = new linkedListNode<int>(dfsStartIdx);

      modifiedDFSHelper(dfsStartIdx); // Call helper function
      numConnectedComponents++; // Increment number of connected components
    }
  }

  return;
}

void Graph::modifiedDFSHelper(int currNodeIdx){
  nodes[currNodeIdx].numTimesOnPath++; // Increase the number of times node is on path

  if(nodes[currNodeIdx].numTimesOnPath >= 2){ // If node on path for more than once
    linkedListNode<int>* cllnode = path->next;
    nodes[currNodeIdx].isCycleNode = true; // Mark this as a cycle node

    // Mark all nodes in this cycle as a cycle node
    while(cllnode->data != currNodeIdx){
      nodes[cllnode->data].isCycleNode = true;
      cllnode = cllnode->next;
    }
  }

  // Traverse all neighbours of node
  linkedListNode<int>* currLLNode = nodes[currNodeIdx].adjacencyListHead;
  for(; currLLNode != nullptr; currLLNode = currLLNode->next){ // Traversing...
    int nextNodeIdx = currLLNode->data; // Index of neighbouring node
    int numParentsCurr = nodes[currNodeIdx].visitedCount; // Number of parents this node has
    bool toVisit = true; // Should visit the neighbour?
    for(int i = 0; i < numParentsCurr; i++){
      if(nextNodeIdx == nodes[currNodeIdx].dfs_parents[i]){ // If neighbour is a parent
        toVisit = false; // DO NOT visit
        break;
      }
    }
    if(!toVisit)
      continue;
    
    // If neighbouring node is visited twice
    if(nodes[nextNodeIdx].visitedCount >= 2){
      continue; // Skip
    }

    nodes[nextNodeIdx].dfs_parents[nodes[nextNodeIdx].visitedCount] = currNodeIdx; // Set myself to be parent of neighbouring node
    nodes[nextNodeIdx].visitedCount++; // Increment visitedCount of neighbouring node
    components->data.insert(nextNodeIdx+1); // Insert myself into the current connected component

    // Add myself to head of path
    linkedListNode<int>* newPathObject = new linkedListNode<int>(nextNodeIdx);
    path->prev = newPathObject;
    newPathObject->next = path;
    path = newPathObject;
    modifiedDFSHelper(nextNodeIdx); // Continue DFS from neighbour
  }
  nodes[currNodeIdx].numTimesOnPath--; // Decrement the number of times I am on path
  // Remove myself from path
  path = path->next;
  if(path != nullptr){
    delete path->prev;
    path->prev = nullptr;
  }
}

void Graph::printResults(){
  int numNodesVisitedOnce = 0; // Number of nodes visited once
  int numNodesVisitedTwice = 0; // Number of nodes visited twice
  int numNodesInCycle = 0; // Number of nodes which are part of a cycle
  for(int nodeIdx = 0; nodeIdx < numNodes; nodeIdx++){ // Traverse through all nodes
    if(nodes[nodeIdx].visitedCount == 1)
      numNodesVisitedOnce++;
    if(nodes[nodeIdx].visitedCount == 2)
      numNodesVisitedTwice++;
    if(nodes[nodeIdx].isCycleNode)
      numNodesInCycle++;
  }

  cout << "No. of connected components: " << numConnectedComponents << endl;
  cout << "No. of nodes visited once: " << numNodesVisitedOnce << endl;
  cout << "No. of nodes visited twice: " << numNodesVisitedTwice << endl;
  cout << "No. of nodes that are present in a cycle: " << numNodesInCycle << endl;

  // Traverse through each component and print the BST of that connected component
  linkedListNode<BST>* currLLNode = components;
  int compNumber = 1; // The index of the component
  while(currLLNode != nullptr){
    cout << "Component " << compNumber << ":" << endl;
    currLLNode->data.printBST("");
    compNumber++;

    currLLNode = currLLNode->next;
  }
}

#endif
