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
  for(int j=0;j < numNodes;j++)
  {
    // cout << "modified dfs " << j+1 << endl;
    // cout << visited[j] << endl;
    if(visited[j]==0)
    {
      numofcomponents++;
      // TreeNode* t = new TreeNode(j+1);
      BST* tree = new BST();
      DFSutil(j, tree, 0);
      // cout << "can print a tree ----" << endl;
      // tree->printBST("");
      trees[n_trees] = tree; //storing all trees
      n_trees++;
    }
  }

  return;
}

void Graph::DFSutil(int i, BST* tree, int not_this)
{
  // cout << "DFS util " << i+1 << endl;
  tree->insert(i+1);
  visited[i]++;
  recstack[cyc_idx] = i+1;
  cyc_idx++;
  // if(visited[i] == 1) ar1[i] = counter;
  // if(visited[i] == 2) ar2[i] = counter;
  // counter++;

  if(adj_list[i]->next != NULL) 
  {
    listOfObjects* head = adj_list[i]->next;
    while(head != NULL)
    {
      // cout << head->object + 1 << endl;
      // cout << "inside while" << endl;
      int w = head->object;
      if(visited[w] < 2 && w+1 != not_this)
      {
        DFSutil(w, tree, i+1);
      }
      head = head->next;
    }
    cyc_idx--;
  }
  
  

  // cout << "------------RECURSION STACK-------------" << endl;
  // for(int i=0;i<cyc_idx;i++)
  // {
  //   cout << recstack[i] << ",";
  // }
  // cout << endl;
  for(i=0;i<numNodes;i++)
  {
    int fi=-1;
    int si=-1;
    if(visited[i] == 2)
    {
      for(int j=0;j<cyc_idx;j++)
      {
        if(recstack[j] == i+1)
        {
          if(fi == -1 && si == -1) fi = j;
          else if(fi != -1 && si == -1) si = j;
          else;
        }
      }
      if(si-fi > 2) 
      {
        for(int j=fi;j<si;j++)
        {
          // cout << "====IN CYCLE===="<<recstack[j] <<  endl;
          incycle[recstack[j]-1] = true;
        }
      }
    }
  }

  // if(visited[i] == 1) dr1[i] = counter;
  // if(visited[i] == 2) dr2[i] = counter;

  return;
}

void Graph::printResults() 
{
  cout << "No. of connected components: " << numofcomponents << endl;
  //number of nodes visited once
  for(int i=0;i<numNodes;i++)
  {
    if(visited[i] == 1) n_visit_once++;
  }

  cout << "No. of nodes visited once: " << n_visit_once;
  int cnt = 0;
  for(int i=0;i<numNodes;i++)
  {
    if(visited[i] == 1) 
    {
      cnt++;
      if(cnt == 1) cout <<" (";
      if(cnt < n_visit_once) cout << i+1 << ",";
      if(cnt == n_visit_once) cout << i+1 << ")" << endl;
    }
  }
  if(cnt == 0) cout << endl;

  cout << "No. of nodes visited twice: " << numNodes-n_visit_once;
  cnt = 0;
  for(int i=0;i<numNodes;i++)
  {
    if(visited[i] == 2) 
    {
      cnt++;
      if(cnt == 1) cout <<" (";
      if(cnt < (numNodes-n_visit_once)) cout << i+1 << ",";
      if(cnt == (numNodes-n_visit_once)) cout << i+1 << ")" << endl;
    }
  }
  if(cnt == 0) cout << endl;

  cout << "No. of nodes that are present in a cycle: ";
  for(int i=0;i<numNodes;i++)
  {
    if(incycle[i])
    {
      num_in_cycle++;
      // cout << i+1 << endl;
    } 
  }
  cout << num_in_cycle << endl;

  for(int i=0;i<n_trees;i++)
  {
    cout << "------------------------------" << endl;
    trees[i]->printBST("");
  }

  return;
}

#endif
