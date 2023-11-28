#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include <vector>
using namespace std;

int recursiveDFS(int* visited, int* visitedonce, int** parents, int* arrTime, Node* source, BST* tree, int timevar, int* noofNodesinCycle) {

  timevar++;

  // deepestbackedge marks an edge from a descendant to an ancestor of source
  int deepestBackEdge = timevar+1;

  // arrival time as in Naveen sir's slides
  arrTime[source->value-1] = min(timevar, arrTime[source->value-1]);
  
  // iterate through each element in adjacency list of source
  for (int i = 0; i < source->adjancency.size(); i++) {

    // once a direction is made from one node to another, it is not possible to make an opp direction from the other node to the first node
    if (parents[source->value-1][0] != source->adjancency[i]->value && parents[source->value-1][1] != source->adjancency[i]->value) {

      // you can visit only once and twice
      if (visited[source->adjancency[i]->value-1] == 0 || visited[source->adjancency[i]->value-1] == 1) {
        visited[source->adjancency[i]->value-1] += 1;

        // updaing list of parents
        if (parents[source->adjancency[i]->value-1][0] == 0) {
          parents[source->adjancency[i]->value-1][0] = source->value;
        } else {
          if (parents[source->adjancency[i]->value-1][0] != source->value) {
            parents[source->adjancency[i]->value-1][1] = source->value;
          }
        }

        // inserting to BST
        tree->insert(source->adjancency[i]->value);
        
        // get minimum of deepbackages of all children
        deepestBackEdge = min(deepestBackEdge, recursiveDFS(visited, visitedonce, parents, arrTime, source->adjancency[i], tree, timevar, noofNodesinCycle));
      } else {
        // This is back edge to ancestor, checking whether it is backedging to above source
        deepestBackEdge = min(deepestBackEdge, arrTime[source->adjancency[i]->value-1]);
      }
    }
  }


  if (deepestBackEdge <= arrTime[source->value-1] && visitedonce[source->value-1] == 0) {
    (*noofNodesinCycle)++;
    visitedonce[source->value-1] = 1;
  }

  return deepestBackEdge;

}

void Graph::modifiedDFS() {

  // Naveen sir's idea of going through visited array once
  for (int i = 0; i < numNodes; i++) {
    if (visited[i] == 0) {
      visited[i] = 1;
      arrTime[i] = 0;

      TreeNode* root = new TreeNode(i+1);
      BST *tree = new BST(root);
      Trees.push_back(tree);
      
      noofComponents++;
      recursiveDFS(visited, visitedonce, parents, arrTime, &nodes[i], tree, 0, &noofNodesinCycle);
    }
  }

  return;
}

void Graph::printResults() {

  int once = 0;
  int twice = 0;

  for (int i = 0; i < numNodes; i++) {
    if (visited[i] == 1) {
      once += 1;
    } else {
      twice += 1;
    }
  }

  cout << "No. of connected components: " << noofComponents << endl;
  cout << "No. of nodes visited once: " << once << endl;
  cout << "No. of nodes visited twice: " << twice << endl;
  cout << "No. of nodes that are present in a cycle: " << noofNodesinCycle << endl;

  for (int i = 0; i < Trees.size(); i++) {
    Trees[i]->printBST("");
  }

  return;
}

#endif
