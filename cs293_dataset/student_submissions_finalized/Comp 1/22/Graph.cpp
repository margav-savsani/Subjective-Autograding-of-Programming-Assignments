#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::dfs(int i, BST *tree, int prevNodeIndex)
{
  visited[i]++;



  Node *currNode = &nodes[i];

  // graphFile<<i+1<<endl;


  currNode->predIndices.QInsert(prevNodeIndex);
  tree->insert(currNode->value);
  int *neighbours = currNode->neighbours.returnArray();

  DynamicQueue<int> visitIs0;
  for(int j=0;j<currNode->neighbours.size();j++)
  {
    // cout<<currNode->value<<"  Neigh: "<<nodes[neighbours[j]].value<<endl;
    if(currNode->predIndices.isPresent(neighbours[j]) || currNode->dontVisit.isPresent(neighbours[j])) continue;

    if(visited[neighbours[j]]==0){

      visitIs0.QInsert(neighbours[j]);
      // cout<<"IN LOOP"<<endl;
      dfs(neighbours[j],tree, i);
      
      // (&nodes[i])->dontVisit.QInsert(neighbours[j]);
      if(!(inCycle.isPresent(neighbours[j]))) {(&nodes[i])->dontVisit.QInsert(neighbours[j]);}

      // if(visited[i]==1){
      int *pred = currNode->predIndices.returnArray();
      for(int k=0;k<currNode->predIndices.size();k++)
      {
        if(visited[pred[k]]==2){ inCycle.QInsert(i);
          break;
        }
      }
      // }
    }
    else
    {
      if(inCycle.isPresent(i)==false) inCycle.QInsert(i);  
    }
  }


  for(int j=0;j<currNode->neighbours.size();j++)
  {
    // cout<<currNode->value<<"  Neigh: "<<nodes[neighbours[j]].value<<endl;
    if(currNode->predIndices.isPresent(neighbours[j]) || currNode->dontVisit.isPresent(neighbours[j])) continue;

    if(visited[neighbours[j]]==1 && !(visitIs0.isPresent(neighbours[j]))){

      // visitIs0.QInsert(neighbours[j]);
      // cout<<"IN LOOP"<<endl;
      dfs(neighbours[j],tree, i);
      if(!(inCycle.isPresent(neighbours[j]))) {(&nodes[i])->dontVisit.QInsert(neighbours[j]);}

      // if(visited[i]==1){
      int *pred = currNode->predIndices.returnArray();
      for(int k=0;k<currNode->predIndices.size();k++)
      {
        if(visited[pred[k]]==2){ inCycle.QInsert(i);
          break;
        }
      }
      // }
    }
    else
    {
      if(inCycle.isPresent(i)==false) inCycle.QInsert(i);  
    }
  }


  return;
}


void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++)
  {
    if(visited[i]==0)
    {
      connectedComponents++;
      BST *tree = new BST();
      trees.QInsert(tree);
      dfs(i, tree, i);
    }
  }
  return;
}

void Graph::printResults() {
  cout<<"No. of connected components:"<<connectedComponents<<'\n';
  
  for(int i=0;i<numNodes;i++)
  {
    if(visited[i]==1) visitedOnce++;
    else if(visited[i]==2)visitedTwice++;
  }
  cout<<"No. of nodes visited once:"<<visitedOnce<<'\n';
  cout<<"No. of nodes visited twice:"<<visitedTwice<<'\n';

  cout<<"No. of nodes that are present in a cycle: "<<inCycle.size() <<"\n ============================================== \n";
  BST **treeArray = trees.returnArray();
  for(int i=0;i<trees.size();i++)
  {
    treeArray[i]->printBST("");
    cout<<"==============================\n";
  }

  return;
}

#endif
