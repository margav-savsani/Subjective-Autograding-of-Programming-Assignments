#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#ifndef GRAPH_BST_H
#include "Graph.h"
#include <vector>
#endif


BST::BST(){root=nullptr;}

void BST::insert(int value){
  TreeNode* new_node;
    new_node=new TreeNode(value);
// Create a new node to insert
    TreeNode* x;TreeNode* y;
    x=root;
    y=nullptr;
    while(x!=nullptr){
// Search for its place in BST
        y=x;
        if(value<x->value) x=x->left;
        else x=x->right;
    }
// put the node in its position
    new_node->parent=y;
    if(y==nullptr){root=new_node;}
    else if(value<y->value) y->left=new_node;
    else y->right=new_node;
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
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
void Graph::cycle_checker(Node &node,int p,int par[]){
  if(node.visited == 2){
    return;
  }
  if(node.visited == 1){
    int cur = p;
     while (cur != node.value) {
            cur = par[cur];
              cyclenumber++;
        }
      return;
  }
  par[node.value]=p;
  node.visited = 1;
   list<int>::iterator it;
        for(it = node.adjacency.begin();it != node.adjacency.end();++it){
          if(node.value == par[(*it)]){
            continue;
      }
      cycle_checker(nodes_c[(*it)-1],node.value,par);
  }
  node.visited = 2;
}
void Graph::dfs(Node &node,BST* Tree,int parent){

  node.visited++;
  Tree->insert(node.value);
   list<int>::iterator it;
        for(it = node.adjacency.begin();it != node.adjacency.end();++it){
          if((nodes[(*it)-1].visited < 2) && (*it) !=parent){
            nodes[*it-1].adjacency.remove(node.value);
            dfs(nodes[(*it)-1],Tree,node.value);
             }
      }
}

void Graph::modifiedDFS() {
   for(int i = 0;i < numNodes;i++) {
         if(nodes[i].adjacency.empty()){
          connectedcomps++;
         }}
  for(int i = 0;i < numNodes;i++) {
         if(nodes[i].visited == 0 && !nodes[i].adjacency.empty())  {
            BST* tree = new BST();
            connectedcomps++;
             dfs(nodes[i],tree,-1);
             trees.push_back(tree);
         }
         if(nodes_c[i].visited == 0 && !nodes_c[i].adjacency.empty()){
          int par[1000];
          cycle_checker(nodes_c[i],0,par);
         }
        }
  return;
}

void Graph::printResults() {

  cout<<"No. of connected components:"<<connectedcomps<<endl;
  int visited_once=0,visited_twice=0;
  for (int i = 0; i < numNodes; i++) {
      if(nodes[i].visited==1){
        visited_once++;
      }
       if(nodes[i].visited==2){
        visited_twice++;
      }
    }
  cout<<"No. of nodes visited once:"<<visited_once<<endl;
  cout<<"No. of nodes visited twice:"<<visited_twice<<endl;
  cout<<"No. of nodes that are present in a cycle:"<<cyclenumber<<endl;
  list<BST*>::iterator it;
  for(it =trees.begin();it!=trees.end();it++){
    (*it)->printBST("");
  }
}

#endif
