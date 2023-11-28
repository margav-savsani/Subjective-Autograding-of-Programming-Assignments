#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

bool Graph::checksimilar(int node1, int node2) {
  // Checks similarity ONLY FOR CONDITION 2
  
  /*
  1. Iterating through two for loops of parents
  2. One for loop = source
  3. Checks for target in the other for loop
  4. Repeats process with the for loops inverted (interchanged)
  */

  if (nodes[node1-1]->incurcount == 0 || nodes[node2-1]->incurcount == 0) {return false;}

  for (int i = 0; i < nodes[node1-1]->incurcount; i++) {
    bool flag = false;
    for (int j = 0; j < nodes[node2-1]->incurcount; j++) {
      if (similar[nodes[node1-1]->inadjacency[i]-1][nodes[node2-1]->inadjacency[j]-1]) {
        flag = true; 
        break;
      }
    }

    if (!flag) {return false;}
  }

  for (int i = 0; i < nodes[node2-1]->incurcount; i++) {
    bool flag = false;
    for (int j = 0; j < nodes[node1-1]->incurcount; j++) {
      if (similar[nodes[node2-1]->inadjacency[i]-1][nodes[node1-1]->inadjacency[j]-1]) {
        flag = true; break;
      }
    }

    if (!flag) {return false;}
  }

  // Finally, if all conditions are satisfied, returns true
  return true;
}

void Graph::printsourcenodes() {
  graphFile << "Source nodes : " ;
  for (int i = 0; i < numNodes; i++) {
    if (nodes[i]->incurcount == 0 && nodes[i]->outcurcount > 0) {
      graphFile << nodes[i]->value << " ";
    }
  }
  graphFile << endl;
}


void Graph::processprospects(int node1, int node2) {
  /*
  1. Storing ALL possible prospects in a list (data member)
  2. Doing this using recursion -> All possible pairs of children of two related nodes are related
  3. Doing the same thing on all children of this children
  */

  // storing prospect : adding a pair.

  prospects[countprospect] = Edge(node1, node2);
  countprospect ++;
  prospects[countprospect] = Edge(node2, node1);
  countprospect++;

  /*
  Termination condition : 
  1. If no children in even one of the nodes then terminate
  */

  if (nodes[node1-1]->outcurcount == 0 || nodes[node2-1]->outcurcount == 0) {return;}

  else {
    // calling the function recursively
    for (int i = 0; i < nodes[node1-1]->outcurcount; i++) {
      for (int j = 0; j < nodes[node2-1]->outcurcount; j++) {
        processprospects(nodes[nodes[node1-1]->outadjacency[i]-1]->value, nodes[nodes[node2-1]->outadjacency[j]-1]->value);
      }
    }
  }

}

void Graph::printsimilarnodes() {
  
  /*
  Two nodes n1 and n2 are said to be similar iff one of the following conditions is satisfied:
  1. Both n1 and n2 are source nodes, and the user specifies n1 and n2 as similar.
  2. Both n1 and n2 are non-source nodes, and for every node m1 that has an edge
  to n1, there is a node m2 that has an edge to n2, where m1 and m2 are similar,
  and vice versa.
  3. If n1 has a single incoming edge from n2, and there are no other incoming
  edges of n1, then n1 and n2 are said to be similar.
  4. No other nodes n1 and n2 are similar.
  */
  
  /*
  1. Adding all nodes with only one in-edge to the relation
  */

  for (int i = 0; i < numNodes; i++) {
    if (nodes[i]->incurcount == 1) {
      similar[i][nodes[i]->inadjacency[0]-1] = 1;
    }
  }

  /*
  1. Iterates through prospects (iterating to stuff already similar better time complexity wise)
  2. If any of them are similar, add that in the relation and start again from the beginning
  3. If not, keep moving on
  4. If we go through the entire list and no change occurs then done
  */

  int curprospect = 0; 

  while (curprospect != countprospect) {

    Edge e = prospects[curprospect];

    if (!similar[e.node1-1][e.node2-1]) {
      if (checksimilar(e.node1, e.node2)) {
        similar[e.node1-1][e.node2-1] = 1;
        similar[e.node2-1][e.node1-1] = 1;
        curprospect = 0;
      }
    }
    curprospect ++ ;
  }

  /* Finally, printing out the similar nodes */
  graphFile << "Similar node pairs: " ;
  for (int i = 0; i < numNodes; i++) {
    for (int j = 0; j < numNodes; j++) {
      if (similar[i][j]) {
        graphFile << "(" << i+1 << "," << j+1 << ") " ;
        similaredge[simcount] = Edge(i+1, j+1); simcount++;
      }
    }
  }
  graphFile << endl;

}

void Graph::printcollapsed() {

  /*
  prints out the graph obtained by collapsing the symmetric, transitive
  closure of all pairs of similar nodes in a file named outgraph.txt. When printing the
  graph use the same file format as indicated earlier, but with identifiers of nodes
  clearly printed space-separated after a colon after the number of nodes.
  */

  // Output format

  /*
  numNodesInCollapsedGraph : nodeId1 nodeId2 ...
  DirectedEdge1_source DirectedEdge1_target
  DirectedEdge2_source DirectedEdge2_targer
  ...
  */

  /*
  for (int i = 0; i < numNodes; i++) {
    for (int j = 0; j < numNodes; j++) {
      graphFile << edgematrix[i][j] << " ";
    }
    graphFile << endl;
  }
  */
  
  for (int i = 0; i < simcount; i++) {
    
    /*
    1. Finding the actual place where the "edge" is to be added
    2. Taking OR of those columns in the edge matrix to give the correct edges to other components 
    3. Adjacency matrix is finally obtained
    */
    

    Edge e = similaredge[i];

    int node1 = e.node1, node2 = e.node2;
    int node = node1;
    while (merged[node-1] != 0) {
      node = merged[node-1];
    } 
    node1 = node;
    node = node2;
    while (merged[node-1] != 0) {
      node = merged[node-1];
    } 
    node2 = node;
    
    // Now merging both columns and rows -> making sure to ignore internal edges. 
    if (node1 > node2) {
      merged[node2-1] = node1;
      for (int i = 0; i < numNodes; i++) {
        edgematrix[node1-1][i] = edgematrix[node1-1][i] || edgematrix[node2-1][i];
      }
      for (int i = 0; i < numNodes; i++) {
        edgematrix[i][node1-1] = edgematrix[i][node1-1] || edgematrix[i][node2-1];
      }
      edgematrix[node1-1][node2-1] = 0;
      edgematrix[node2-1][node1-1] = 0;
    }
    else if (node1 < node2){
      merged[node1-1] = node2;
      for (int i = 0; i < numNodes; i++) {
        edgematrix[node2-1][i] = edgematrix[node1-1][i] || edgematrix[node2-1][i];
      }
      for (int i = 0; i < numNodes; i++) {
        edgematrix[i][node2-1] = edgematrix[i][node1-1] || edgematrix[i][node2-1];
      }
      edgematrix[node1-1][node2-1] = 0;
      edgematrix[node2-1][node1-1] = 0;
    }
  }

  // Computing required numbers for the collapsed graph.
  Edge finaledges[numNodes*numNodes];
  int finalnodes[numNodes];
  int nodecount = 0;
  int edgecount = 0;
  int count = 0;
  for (int i = 0; i < numNodes; i++) {
    if (merged[i] == 0) {
      finalnodes[nodecount] = i+1;
      nodecount++;
      for (int j = 0; j < numNodes; j++) {
        if (edgematrix[i][j]){
          // putting the edge in the correct place
          int node = j+1;
          while (merged[node-1] != 0) {node = merged[node-1];}
          bool flag = false;
          for (int k = 0; k < edgecount; k++) {
            if (finaledges[k] == Edge(i+1, node)){
              flag = true;
              break;
            }
          }
          if (!flag) {
            finaledges[edgecount] = Edge(i+1, node);
            edgecount++;
          }
        }
      }
    }
  }

  // Finally, printing all the required quantities. 
  graphFile << "Collapsed graph: " << endl;
  graphFile << nodecount << " : ";
  for (int i = 0; i < nodecount; i++) {graphFile << finalnodes[i] << " ";}
  graphFile << endl;
 
  for (int i = 0; i < edgecount; i++) {
    Edge e = finaledges[i];
    if (e.node1 != e.node2)
      graphFile << e.node1 << " " << e.node2 << endl;
  }

  /*
  for (int i = 0; i < numNodes; i++) {
    for (int j = 0; j < numNodes; j++) {
      graphFile << edgematrix[i][j] << " ";
    }
    graphFile << endl;
  }
  */

}

void Graph::printResults() {

  /*
  1. Printing output of all three components
  2. Printing is done internally 
  */

  printsourcenodes();
  printsimilarnodes();
  printcollapsed();
}


