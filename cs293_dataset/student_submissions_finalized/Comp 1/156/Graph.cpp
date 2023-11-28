#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// To check if all nodes are visited, traverse through the array and then where you
// find the first 0 (visited value) then then do DFS on that node, and now once done again
// start traversing the array from where you left last time and continue the above thing 
// and you are done
// Make a parent array too so that when you do DFS you can store parent of a node 
// and not visit it from that node
void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited==0){
      BST *tree = new BST;
      listOfObjects<DFSEdge> *EdgeList = nullptr;
      DFSConnected(nodes[i],EdgeList,tree);
      if(Trees==nullptr){
        Trees = new listOfObjects<BST>(*tree);
      }
      else{
        listOfObjects<BST> *x = Trees;
        while(x->next!=nullptr){
          x = x->next;
        }
        x->next = new listOfObjects<BST>(*tree);
      }
      numConnected++;
    }
  }
  for(int i=0;i<numNodes;i++){
    if(nodes[i].num_adj>1 && nodes[i].visited==2){
      numNodesInCycle++;
    }
  }
}

// now we have the BST as well for this connected component
void Graph::DFSConnected(Node &node, listOfObjects<DFSEdge> *EdgeList, BST *tree) {

  listOfObjects<Node> *x = nodes[node.value-1].adj; // Adjacency list of the node
  
  if(nodes[node.value-1].visited==0){
    nodes[node.value-1].visited++;
    numVisitedOnce++;
  }
  else if(nodes[node.value-1].visited==1){
    nodes[node.value-1].visited++;
    numVisitedTwice++;
    numVisitedOnce--;
  }
  
  // update the BST too
  tree->insert(node.value);
 
  //  && !nodes[node.value-1].backtracked
  while(x!=nullptr){
    if(nodes[x->object.value-1].visited<2){
      if(EdgeList==nullptr){
        DFSEdge *edge = new DFSEdge();
        EdgeList = new listOfObjects<DFSEdge>(*edge);
        EdgeList->object.set(node.value,x->object.value);
        DFSConnected(x->object,EdgeList,tree);
      }
      else{
        listOfObjects<DFSEdge> *y = EdgeList;
        listOfObjects<DFSEdge> *z = y;
        bool ReverseEdgePresent = false;
        // Update EdgeList and call the DFS on that node if reverse node is not
        // already present in the edge list
        while(y!=nullptr){
          z = y;
          if(y->object.from == x->object.value && y->object.to == node.value){
            ReverseEdgePresent = true;
            break;
          }
          y = y->next;
        }
        if(!ReverseEdgePresent){
          DFSEdge *edge = new DFSEdge();
          z->next = new listOfObjects<DFSEdge>(*edge);
          z->next->object.set(node.value,x->object.value);
          DFSConnected(x->object,EdgeList,tree);
        }
      }
    }
    x = x->next;
  }

  nodes[node.value-1].backtracked = true;
}

void Graph::printResults() {
  cout << "No. of connected components: " << numConnected << endl;
  cout << "No. of nodes visited once: " << numVisitedOnce << endl;
  cout << "No. of nodes visited twice: " << numVisitedTwice << endl;
  cout << "No. of nodes that are present in a cycle: " << numNodesInCycle << endl;
  cout << "Binary Search Trees: " << endl;
  listOfObjects<BST> *x = Trees;
  int i=1;
  while(x!=nullptr){
    cout << "Connected component " << i << ":" << endl;
    x->object.printBST("");
    x = x->next;
    i++;
  }
}

#endif
