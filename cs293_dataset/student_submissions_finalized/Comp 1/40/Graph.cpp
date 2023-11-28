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
  
  ourDFS(nodes[0]);      //calling dfs on the first node

  for (int i = 0; i < numNodes; i++)    //checking for disconnected components
  {
    if(count[i] == 0){           //this says that this node was not covered in DFS done till now so it's a new component in itself
      TreeNode *temp;
      vecofbst.push_back(BST());     //pushing a BST to our vector of bst
      ourDFS(nodes[i]);              //dfs on the new node along with incrementing components 
      components++;
    }
  }
    
  for (int i = 0; i < numNodes; i++) //self explanatory - calculating how many vertices are visited once and twice
  {
    if(count[i] == 1) visitedonce++;
    else visitedtwice++;
  }
  for (int i = 0; i < numNodes; i++) //self explanatory - calculating how many nodes are part of a cycle
  {
    if (ifcycle[i]) nodesincycle++;
  }
}

void Graph::ourDFS(Node v) {

  int node = v.value - 1;           //treating nodes as an integer i.e nodes[i] is denoted by int i 
  count[node]++;                    //incrementing count as we just visited
  if(vecofbst.size() == 0){         //if vector of bst is empty ie no insertion yet (nodes[0] case)
    TreeNode *temp;
    temp = new TreeNode(nodes[0].value);
    vecofbst.push_back(BST( temp));
  }
  else{                              //otherwise
    vecofbst.back().insert(v.value);
  }

  int size = adj[node].size();        //number of node adjacent to node (vector)
  for (int i = 0; i < size; i++)      //looping through all adjacent edges
  {
    if (count[adj[node][i]] == 0){    
      if (adj[node][i] != predecessor[node]){   //as we don't want to go do dfs on the predecessor which would lead ot back and forth
        predecessor[adj[node][i]] = node;       //updating predecessors
        ourDFS(nodes[adj[node][i]]);
      }
    }
    else if (count[adj[node][i]] == 1){         //if the adjacent node was already visited once
      if (adj[node][i] != predecessor[node]){
        int x = node;         
        bool reachesparent = true;              //checking if we can reach the adjacent node by backtracking from our node (if yes then it forms a cycle)
        while (x != adj[node][i]){
          if(x == -1){                          //predecessor does not exit ie we failed :)
            reachesparent = false;
            break;
          }
          x = predecessor[x];
        }
        if(reachesparent){                      //if cycle exists
          int x = node;
          while (x != adj[node][i]){
            ifcycle[x] = true;
            x = predecessor[x];
          }
          ifcycle[x] = true;                    //updating the boolean array ifcycles to true for all the above nodes which are part of a cycle
        }
        ourDFS(nodes[adj[node][i]]);            //calling dfs as count is not 2 yet (we can visit)
      }
    }
    else{
      if (adj[node][i] != predecessor[node]){   //count of adjacent node == 2 case, essentially same as above except that we dont do dfs at last as we cannot visit the adjacent node
        int x = node;
        bool reachesparent = true;
        while (x != adj[node][i]){
          if(x == -1){
            reachesparent = false;
            break;
          }
          x = predecessor[x];
        }
        if(reachesparent){
          int x = node;
          while (x != adj[node][i]){
            ifcycle[x] = true;
            x = predecessor[x];
          }
          ifcycle[x] = true;
        }
      }
    }

  }
  
}
  

void Graph::printResults() {               //Just a beautiful and easy print function
  cout<<"No. of connected components: "<<components<<endl;
  cout<<"No. of nodes visited once: "<<visitedonce<<endl;
  cout<<"No. of nodes visited twice: "<<visitedtwice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<nodesincycle<<endl;

  for(int i=0; i < vecofbst.size(); i++){    //looping through our vector of BST and printing them all
    vecofbst[i].printBST("");
  }
  return;
}

#endif
