#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() 
{
  vector<int> parent(numNodes, -1);
  vector<int> arrival(numNodes);
  int time = 0;
  int nextRoot = 0;
  while (nextRoot < numNodes){
    
    vector<int> S;
    S.push_back(nextRoot);
    parent[nextRoot] = -1;

    BST *dfstree = nullptr;
    while(!S.empty()){
      int u = S.back();
      S.pop_back();
      
      if (visited[u] >= 2) continue;
      
      visited[u]++;
      if (visited[u] == 1) arrival[u] = ++time;
      if (!dfstree) dfstree = new BST(nodes[u].value); else dfstree->insert(nodes[u].value);

      if (!adj[u]) continue;

      ll *adjlist = adj[u]->inorder();
      vector<int> tmp; // used to reverse the current additions to the stack to ensure same order as a recursive program = the order in which the adjacency list stores the vertices.
      for (ll *it = adjlist; it; it = it->next){
        int v = *it;
        if (v == parent[u]) continue; // no going back the same edge we just came from.
        
        // backedge
        if (visited[v] && arrival[v] < arrival[u]){
          part_of_a_cycle[u] = true;
          // additionally we must add in all vertices spanned by the backedge to part-of-a-cycle.
          int i = u;
          while(i != v && i != nextRoot){
            i = parent[i];
            part_of_a_cycle[i] = true;
          }
        }

        if (visited[v] >= 2) continue;
        if (visited[v] == 0) parent[v] = u; // parent is updated only once.
        
        tmp.push_back(v);
      }
      while (!tmp.empty()){
        S.push_back(tmp.back()); tmp.pop_back();
      }
      delete adjlist;
    }
  
    dfsforest.push_back(dfstree);
    while(++nextRoot < numNodes && visited[nextRoot] > 0);
  }

  // for (int i = 0; i < visited.size(); i++) cout << i+1 << " " << char('0' + visited[i]) << endl;

}

void Graph::printResults() {
    cout << "Number of connected components: " << dfsforest.size() << endl;
    
    int numOnce = 0, numTwice = 0;
    for (int i = 0; i < numNodes; i++)
      if (visited[i] == 1) numOnce++; else numTwice++;
    
    cout << "Number of nodes visited once: "  << numOnce  << endl;
    cout << "Number of nodes visited twice: " << numTwice << endl;
    int numCycle = 0;
    for (int i = 0; i < numNodes; i++) numCycle += part_of_a_cycle[i];
    cout << "Number of nodes present in a cycle: " << numCycle << endl;
    cout << "The dfs forest:\n";
    int i = 0;
    for (BST *tree: dfsforest){
      cout << "connected component #" << (++i) << "\'s dfs bst\n=================" << endl; 
      tree->print("");
    }
    // for (int i = 0; i < visited.size(); i++) cout << i+1 << " " << char('0' + visited[i]) << endl;

    // reset visited and the dfsforest
    dfsforest = vector<BST *>();
    visited = vector<char>(); 
  }

#endif
