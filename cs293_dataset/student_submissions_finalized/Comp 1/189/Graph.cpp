#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void BST::printBST1(TreeNode *root,const string& prefix,bool isLeft){
  
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->NodeValue << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST1( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST1( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }

}

void BST::printBST(TreeNode *node) {

  // insert your code here
  printBST1(node,"",false);
}

void BST::insert(int x, TreeNode *n){
  if(n==nullptr){
    n->NodeValue = x;
    n->left = nullptr;
    n->right = nullptr;
    return;
  }
  else{
    if(x<n->NodeValue){
      if(n->left==nullptr){
        n->left->NodeValue=x;
        n->left->left=nullptr;
        n->left->right=nullptr;
        n->left->parent=n;
      }
      else{
        insert(x,n->left);
      }
    }
    else{
      if(n->right==nullptr){
        n->right->NodeValue=x;
        n->right->left=nullptr;
        n->right->right=nullptr;
        n->right->parent=n;
      }
      else{
        insert(x,n->right);
      }
    }
  }
}

int Graph::indexOfUnvisitedNode(){
  int k = -1;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visitedCount==0){
      k = i;
    }
  }
  return k;
}

void Graph::modifiedDFSNodeParameter(Node *n,BST* Tree){
  Tree->insert(n->value,Tree->root);
  n->visitedCount++;
  for(int i=0;i<=n->adjacentNodesCount;i++){
    if(n->adjacentNodes[i]->visitedCount<2){
      modifiedDFSNodeParameter(n->adjacentNodes[i],Tree);
    }
  }
}

void Graph::modifiedDFS() {
  Node *startNode = &nodes[0];
  *(BSTtrees[BSTCount]) = BST();
  BSTCount++;
  modifiedDFSNodeParameter(startNode,BSTtrees[BSTCount-1]);
  int startNodeIndex=0;
  startNodeIndex=indexOfUnvisitedNode();
  while(startNodeIndex!=-1){
    startNode=&nodes[startNodeIndex];
    *(BSTtrees[BSTCount]) = BST();
    BSTCount++;
    modifiedDFSNodeParameter(startNode,BSTtrees[BSTCount-1]);
    startNodeIndex=indexOfUnvisitedNode();
  }
  

  return;
}

void Graph::printResults() {
  int numberOfNodesVisitedOnce=0;
  int numberOfNodesVisitedTwice=0;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visitedCount==1){
      numberOfNodesVisitedOnce++;
    }
  }
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visitedCount == 2){
      numberOfNodesVisitedTwice++;
    }
  }
  cout<<"No of connected components "<<BSTCount<<endl;
  cout<<"No of nods visited once "<<numberOfNodesVisitedOnce<<endl;
  cout<<"No of nodes visited twice "<<numberOfNodesVisitedTwice<<endl;
  for(int i=0;i<BSTCount;i++){
    BSTtrees[i]->printBST(BSTtrees[i]->root);
  }
  return;
}

#endif
