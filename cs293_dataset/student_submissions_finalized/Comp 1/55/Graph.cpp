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
  int visited[numNodes] = {0};
  int inCycle[numNodes] = {0};
  int parent1[numNodes];
  int parent2[numNodes];
  for(int i=0;i<numNodes;i++){
    parent1[i] = -1;parent2[i] = -1;
  }
	for(int i = 0; i < numNodes; i++){
    if(componentNumbers[i]==0){
      BST* tree = new BST;
      DFS(i, visited, inCycle, tree, parent1, parent2);
      if(lstTrees == nullptr){
        lstTrees = new ListOfTrees(tree);
        // //!!
        // cout<<numConnectedComponents<<endl;
        // //!!    
        }
      else{
        ListOfTrees* lstTreeCopy = lstTrees;
        while(lstTreeCopy->next!=nullptr){
          lstTreeCopy = lstTreeCopy->next;
        }
        lstTreeCopy->next = new ListOfTrees(tree);
        // //!!
        // cout<<numConnectedComponents<<endl;
        // //!!
      }
      numConnectedComponents++;
    }
  }
  result.numConnectedComponents = numConnectedComponents-1;
  result.lstTrees = lstTrees;
  result.numInCycle = 0;
  result.visitedOnce = 0;
  result.visitedTwice = 0;
  for(int i=0;i<numNodes;i++){
    if(inCycle[i]==1){
      result.numInCycle++;
    }
    if(visited[i]==1){
      result.visitedOnce++;
    }
    else if(visited[i]==2){
      result.visitedTwice++;
    }
  }
  return;
}

void Graph::DFS(int i, int *visited, int *inCycle, BST* tree, int *parent1, int *parent2){
  visited[i]++;
  tree->insert(i+1);
  //Insert into BST
  componentNumbers[i] = numConnectedComponents;
  nodes[i].tracker++;
  for(adjacencyList* adjacencyList = nodes[i].adjacents; adjacencyList!=nullptr; adjacencyList = adjacencyList->next){
    //!!
    cout<<adjacencyList->neighbourValue<<" is adjacent to " << i <<endl;
    //!!
    int nodeNumber = adjacencyList->neighbourValue;
    if(nodeNumber==parent1[i] || nodeNumber==parent2[i]) continue;
    else if(visited[nodeNumber]<2){
      if(parent1[nodeNumber]==-1){
        parent1[nodeNumber] = i;
      }
      else{
        parent2[nodeNumber] = i;
      }
    }

    if(visited[nodeNumber]==2){
      if(nodes[nodeNumber].tracker>0){
        inCycle[i] = 1;
        inCycle[nodeNumber] = 1;
      }
      continue;
    }
    else{
      if(nodes[nodeNumber].tracker>0){
        inCycle[i] = 1;
        inCycle[nodeNumber] = 1;
      }
      DFS(nodeNumber, visited, inCycle, tree, parent1, parent2);
    }
  }
  nodes[i].tracker--;
  return;
}

void Graph::printResults() {
  cout<<"Number of Connected Components: "<<result.numConnectedComponents<<endl;
  cout<<"Number of nodes visited Once: "<<result.visitedOnce<<endl;
  cout<<"Number of nodes visited Twice: "<<result.visitedTwice<<endl;
  cout<<"Number of nodes that are present in a cycle: "<<result.numInCycle<<endl;
  cout<<"Printing Trees: "<<endl;
  for(ListOfTrees *i = result.lstTrees; i!=nullptr; i = i->next){
    cout<<"Here is Tree number: "<<componentNumbers[i->tree->root->value-1]<<endl;
    i->tree->printBST("",false);
  }
	return;
}

BST::BST(){root=NULL; }
BST::BST(TreeNode *root){this->root=root; }
void BST::insert(int value){
  if(root == nullptr){
    root = new TreeNode(value);
  }
  else{
    TreeNode *node = root;
    TreeNode *parent = nullptr;
    while (node!= nullptr){
      if(value<=node->value){
        parent = node;
        node = node->left;
      }
      else{
        parent = node;
        node = node->right;
      }
    }
    if(value<=parent->value){
      parent->left = new TreeNode(value);
      parent->left->parent = parent;
    }
    else {
      parent->right = new TreeNode(value);
      parent->right->parent = parent;
    }
  }
}

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        // root = root->right;
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
#endif
