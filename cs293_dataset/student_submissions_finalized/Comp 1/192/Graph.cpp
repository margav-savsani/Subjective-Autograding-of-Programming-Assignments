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
  //maintain a list of the number of times a node has been visited.
  int * visited = new int[numNodes]{0};


  
  

  for(int i = 0; i < numNodes; i++){
    //if not yet visited, it is a part of a new connected component.
    if (visited[i] == 0 ){
      numConnected++;

      // Create a new BST for this connected component.
      BST * dfsTree = new BST();

      //insert the start node in the stack and in the BST.
      ListNode * startNode = new ListNode(nodes[i].value);
      startNode->predec = numNodes + 1;
      

      // while the stack is not empty
      while(startNode){
          // pop the stack
          ListNode * toDelete = startNode;
          startNode = startNode->next;

         // if visited  < 2 then increment visited of the node.
          if(visited[toDelete->value - 1] < 2){
            visited[toDelete->value - 1]++;
            if (visited[toDelete->value - 1] == 2) numInCycle++;
            //Otherwise just move forward. 
          } else {
            
            delete toDelete;
            continue;
          }
          
          //Insert the popped element into the DFS
          dfsTree->insert((toDelete->value));

          //Go to the adjacency list of the popped element.
          ListNode* adjPtr = adjacencyList[toDelete->value -1];

          

          while(adjPtr){
            // If not predecessor and visited less than 2 times.
            if (visited[adjPtr->value - 1] < 2 && adjPtr->value != toDelete->predec ){
              //Add the element to the stack.
              ListNode * newNode  = new ListNode(adjPtr->value);
              newNode->predec = toDelete->value;
              newNode->next = startNode;
              startNode = newNode;

            } 
            //Go to the next element.
            adjPtr = adjPtr->next;
          } 
          //delete the popped element.
          toDelete->next = NULL;
          delete toDelete;

          

      }
      //Print the connected Component.
      cout << "Connected Component : " << numConnected << "\n";
      dfsTree->printBST("", false);
    }
    
    
  }

}

void Graph::printResults() {
  cout << "Number of Connected Components: "<< numConnected <<  endl;
  cout << "Number of nodes visited twice: "<< numInCycle <<  endl;
}

#endif
