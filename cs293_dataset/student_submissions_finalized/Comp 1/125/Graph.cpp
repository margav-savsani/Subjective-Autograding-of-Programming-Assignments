#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;

bool BST::insert(int val)
{
  if(root==NULL){
    TreeNode* newNode = new TreeNode(val);
    root = newNode;
    root->parent=NULL;
    return true;
  }
  TreeNode* true_root = root;
  if(root->value<=val){
    if(root->right==NULL){
      TreeNode* newNode = new TreeNode(val,NULL,NULL,root);
      root->right=newNode;
    }
    else{
      root = true_root->right;
      insert(val);
      root = true_root;
    }
  }
  else{
    if(root->left==NULL){
      TreeNode* newNode = new TreeNode(val,NULL,NULL,root);
      root->left=newNode;
    }
    else{
      root = true_root->left;
      insert(val);
      root = true_root;
    }
  }
  root = true_root;
  return true;
}
bool BST::find(int val)
{
  if(root==NULL) return false;
  if(root->value==val) return true;
  TreeNode* true_root = root;
  if(root->value<=val){
      root = true_root->right;
      bool ans = find(val);
      root = true_root;
      return ans;
  }
  else{
      root = true_root->left;
      bool ans = find(val);
      root = true_root;
      return ans;
  }
}

void BST::printBST(const string& prefix, bool isLeft, fstream& graphFile)
{
  if( root != nullptr )
  {
    graphFile << prefix;

    graphFile << (isLeft ? "|--" : "|__" );

    // print the value of the node
    graphFile << root->value << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST( prefix + (isLeft ? "│   " : "    "), true, graphFile);
    root = curr->right;
    printBST( prefix + (isLeft ? "│   " : "    "), false, graphFile);
    root = curr;
  }
}

void Graph::modifiedDFS() {
  for (int i = 0; i <= numNodes; i++) one_visits[i] = -1;
  for (int i = 0; i <= numNodes; i++) two_visits[i] = -1;
  for (int i = 0; i <= numNodes; i++) visited[i]=0;
  delete[] bst_roots;
  bst_roots = new BST[numNodes];
  connectedComponents = 0;

  int one_visit_index = 0;
  int two_visit_index = 0;
  for(int i = 0; i<numNodes; i++){
    if(visited[i]>0) continue;
    BST bst;
    modDFS(&nodes[i], -1, &bst);
    bst_roots[connectedComponents] = bst;
    connectedComponents++;
  }

  for(int i = 0; i<numNodes; i++){
    if(visited[i]==1){
      one_visits[one_visit_index] = i+1;
      one_visit_index++;
    }
  }
  for(int i = 0; i<numNodes; i++){
    if(visited[i]==2){
      two_visits[two_visit_index] = i+1;
      two_visit_index++;
    }
  }
  return;
}

void Graph::modDFS(Node *x, int previous, BST *bst){
  if(visited[x->value]==2) return;
  visited[x->value]++;
  if(x->adjacent_edges==NULL){
    bst->insert(x->value+1);
    return;
  }
  x->del(previous);
  bst->insert(x->value+1);
  if(x->adjacent_edges==NULL) return;
  listOfNodes* y = x->adjacent_edges->head;
  while(y!=NULL){
    if(!y->allowed){
      y = y->next;
      continue;
    }
    modDFS(y->node, x->value, bst);
    y = y->next;
  }
} 

void Graph::printResults() {
  graphFile << "No. of connected components: " << connectedComponents << '\n';
  int nodesInCycle = 0;
  int index = 0;
  while(one_visits[index]!=-1) index++;
  if(index==0) graphFile << "No. of nodes visited once: " << index << '\n';
  else graphFile << "No. of nodes visited once: " << index << "(";
  index=0;
  while(one_visits[index]!=-1){
    if(one_visits[index+1]==-1) graphFile << one_visits[index]<< ")\n";
    else graphFile << one_visits[index]<< ", ";
    index++;
  }
  index = 0;
  while(two_visits[index]!=-1) index++;
  if(index==0) graphFile << "No. of nodes visited twice: " << index << '\n';
  else graphFile << "No. of nodes visited twice: " << index << "(";
  index=0;
  while(two_visits[index]!=-1){
    if(two_visits[index+1]==-1) graphFile << two_visits[index]<< ")\n";
    else graphFile << two_visits[index]<< ", ";
    index++;
  }
  graphFile << "No. of nodes that are present in a cycle: " << index << '\n';
  index = 0;
  while(bst_roots[index].root!=NULL){
    bst_roots[index].printBST("", false, graphFile);
    index++;
  }
  return;
}

#endif
