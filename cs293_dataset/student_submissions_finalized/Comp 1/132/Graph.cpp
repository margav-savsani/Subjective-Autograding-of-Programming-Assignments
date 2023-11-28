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
  
    for (auto i : adj)
    if (visited[i.first] == false)
    modifiedDFSUtil(i.first);

  return;
}

void Graph::printResults() {



  return;
}

#endif
