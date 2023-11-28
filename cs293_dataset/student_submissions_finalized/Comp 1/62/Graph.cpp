#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

//sets up dfs over the entire graph,
// sets up the variables, counters/tallies for the dfs
// calls helper /recursive dfs on components 
// updates the graph information object declared in graph.h
void Graph::modifiedDFS() { 
  LinkedList<BST*>* forest = new LinkedList<BST*>(); // list of tree roots corresponding to each connected component

  for(int i=0;i<numNodes;i++){ // init member arrays, clearing them here for safety
    arrival[i] = parent[i] = -1;
    incycle[i] =false;
    visited[i] = 0;
  }
  int time =0;
  BSTWrapper newtree;// add then call DFS recursive
  for(int i=0;i<numNodes;i++){
    if (visited[i]==0){
      modifiedDFSrecursive(i,newtree,time); // updates the newtree
      forest->insert(newtree.Root());// inserts the root of the newtree to the list
      newtree.clear();// empty the newtree for use in the next loop
    }
  }
  int visits[2]={0,0}; // [visited-once,visited-twice]
  int cycled=0;
  for(int i=0;i<numNodes;i++){visits[visited[i]-1]++;cycled+=incycle[i];}// update these variables to return
  Gi = new GraphInfo(forest,visits[0],visits[1],cycled);// set Gi
  return;
}
//recursively called DFS modified
void Graph::modifiedDFSrecursive(int root,BSTWrapper& tree, int& time) {
  tree.add(nodes[root].value);
  if (visited[root]++==0) arrival[root] = time++;// set arrival if the first time visiting
  if (nodes[root].adjacency){ // null adjacency corresponds to no edges connecting, so just take the other case
  // iterate over edges of the adjacency
    for (LLNode<int>* edge = nodes[root].adjacency->Head(); edge!=nullptr; edge = edge->next){
      int val = edge->value;
      if (parent[root]==val) continue;// do not retraverse the parents
      if (visited[root]==1&&visited[val]&&arrival[val]<arrival[root]){//"back edge"
        //trace upwards updating incycle
        for (int i=root;i!=-1;i=parent[i]){
          incycle[i]=true;
          if (i==val) break;
        }
      }
      if (visited[val]<2){ // valid forward edge, can also be a "back edge"
        if (visited[val]==0) parent[val] = root;//first time visiting that val - update the parent array
        modifiedDFSrecursive(val,tree,time);
      }
    }
  }
}

void Graph::printResults() {
  if (Gi==nullptr){ 
    cerr<<"DFS not run. Aborted"<<endl;
    return;
  }
  cout<<
  "No. of connected components: "<< Gi->numconnected <<  
  "\nNo. of nodes visited once: " << Gi->nodesonce<<
  "\nNo. of nodes visited twice: " << Gi->nodestwice<<
  "\nNo. of nodes that are present in a cycle:" << Gi->incycle << endl;
  //print each tree in the forest
  for (LLNode<BST*>*current = Gi->forest->Head(); current!=nullptr; current = current->next){
    current->value->printBST();
    cout<<endl;
  }
  return;
}

#endif
