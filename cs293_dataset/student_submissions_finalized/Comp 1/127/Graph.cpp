#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#include <stack>
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {

  for(int alpha=0; alpha<numNodes; alpha++) {
    if(visited[alpha]==0) {

      numComponents+=1;
      BST_list.push_back(BST());

      stack<int> DFS_stack;
      stack<int> parent_stack;
      DFS_stack.push(alpha);
      parent_stack.push(-1);

      int cur_node;
      int parent_node;
      while(!DFS_stack.empty()) {

        cur_node=DFS_stack.top();
        DFS_stack.pop();

        parent_node=parent_stack.top();
        parent_stack.pop();

        if(visited[cur_node]<2) {
          visited[cur_node]+=1;

          BST_list[BST_list.size()-1].insert(cur_node);
          for(std::list<int>::iterator it=adjacency_list[cur_node].begin(); it!=adjacency_list[cur_node].end(); it++) {
            if(visited[*it]<2 && *it!=parent_node) {
              DFS_stack.push(*it);
              parent_stack.push(cur_node);
            }
          }
        }

      }
    }
  }

  return;
}

void Graph::printResults() {

  int num_vis_once=0;
  int num_vis_twice=0;

  for(int beta=0; beta<numNodes; beta++) {
    if(visited[beta]==1) {
      num_vis_once+=1;
    }
    else if(visited[beta]==2) {
      num_vis_twice+=1;
    }
  }

  std::cout<<"No. of connected components: "<<numComponents<<"\n";
  std::cout<<"No. of nodes visited once: "<<num_vis_once<<"\n";
  std::cout<<"No. of nodes visited twice: "<<num_vis_twice<<"\n";

  for(int delta=0; delta<BST_list.size(); delta++) {
    std::cout<<"\nBST for component "<<delta+1<<":\n";
    BST_list[delta].printBST(BST_list[delta].root, "", true);
  }

  return;
}

#endif
