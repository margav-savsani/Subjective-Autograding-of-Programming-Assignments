#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

BST::BST(){root = NULL; }
BST::BST(BSTNode *root){this->root = root; }


void Graph::modifiedDFS() {

  for (int i = 0; i < numNodes; i++) {
    for(int j = 0; j < numNodes; j++){
      marked[j] = false;
    }
  
    if(nodes[i].visited == 0){
      numConnectedComp++;
      BST* newTree = new BST();
      trees.push_back(newTree);
      DFSrecursive(nodes[i], -1, newTree);
    }
  }

  for(auto i : badvalues){
    for(auto j : nodes[i].adj){
      int count = 0;
      for(auto k : nodes[j].adj){
        if(badvalues.count(k)) count++;
      }
      if(count == nodes[j].adj.size() - 1){
      badvalues.insert(j);
      }
    }

    
  }

  numNodesInCycle = numNodesInCycle - badvalues.size();  

  return;
}

void Graph::DFSrecursive(Node &n, int parent, BST* tree){
  n.visited++;

  if(n.visited > 2){
    return;
  } else {

    tree->insert(n.value);

    if(n.visited == 1){
      numNodesVisitedOnce++;
      marked[n.value-1] = true;
    }

    else if(n.visited == 2){
      numNodesVisitedOnce--;
      numNodesVisitedTwice++;
      if(n.adj.size() == 1){
        badvalues.insert(n.value-1);

        // for(auto i : n.adj){
        //   if(nodes[i].adj.size() == 2){
        //     numNodesInCycle--;
        //   }
        // }

      }
      // if(n.adj.size() == 2){
      //   for(auto i : n.adj){
      //     if(badvalues.count(i)){
      //       numNodesInCycle--;
      //       badvalues.insert(i);
      //     }
      //   }
      // }
      if(marked[n.value - 1]){// && n.adj.size() != 1
        cout << n.value << endl;
        numNodesInCycle++;
      }
    }

    for (auto i : n.adj){
      if(i != parent)
        DFSrecursive(nodes[i], n.value - 1, tree);
    }

  }
  return; 
}


void Graph::printResults() {

  cout << "No. of connected components: " << numConnectedComp;cout << endl;
  cout << "No. of nodes visited once: " << numNodesVisitedOnce;cout << endl;
  cout << "No. of nodes visited twice: " << numNodesVisitedTwice;cout << endl;
  cout << "No. of nodes that are present in a cycle: " << numNodesInCycle;cout << endl;

  for(auto i : trees){
    cout << endl << "**********" << endl;
    i->printBST("", false);
    
  }

  for(auto i : badvalues){
    cout << i + 1<< endl;
  }

  return;
}

#endif
