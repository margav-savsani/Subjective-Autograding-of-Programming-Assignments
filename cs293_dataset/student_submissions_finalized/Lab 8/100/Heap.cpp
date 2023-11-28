#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

string buildBinary(int num){
  string res="";
  int x=num;
  while(x>0){
    res = to_string(x%2) + res;
    x/=2;
  }
  return res;
}

template<typename T>
TreeNode<T> * getFreeNode(string path,TreeNode<T> *node){
  if(node==nullptr)return nullptr;
  for(int i=1; i<path.length()-1;i++){
    if(path[i]==0)node=node->left;
    else node=node->right;
  }
  return node;
}

template<typename T>
void Heap<T>::insert(T obj) {

  if(root==nullptr){
    root=new TreeNode<T>(obj);
    numNodes++;
    return;
  }

  string s=buildBinary(numNodes);
  TreeNode<T>* node=getFreeNode(s,root);

  TreeNode<T>* newNode=new TreeNode<T>(obj);
  if(node->left==nullptr){
    node->left=newNode;
    newNode->parent=node;
    numNodes++;
  }
  else {
    node->right=newNode;
    newNode->parent=node;
    numNodes++;
  }

  heapify(node);

  return;
}

template<typename T>
TreeNode<T> * maxNode(TreeNode<T> *lnode,TreeNode<T> *rnode){
  if(lnode==nullptr)return rnode;
  if(rnode=nullptr)return lnode;
  if(lnode->object < rnode->object)return rnode;
  else return lnode;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if(node==nullptr)return;

  TreeNode<T> *maxnode=maxNode(node->left,node->right);
  if(node->object < maxnode->object)swap(node->object,maxnode->object);
  heapify(node->parent);

}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  static int level=-1;
  level++;
  if(node==nullptr)return;

  cout << node->object <<" ";

  printHeap(node->left);
  printHeap(node->right);
  if(level==0)cout<<"\n";
  level--;

  return;
}

  
