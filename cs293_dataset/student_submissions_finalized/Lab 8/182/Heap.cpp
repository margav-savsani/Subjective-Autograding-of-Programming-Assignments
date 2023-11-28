#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *n,*currnode=root,*parentof;
  n=new TreeNode(obj);
  int residue=1+noofnodes-pow(2,getheightoftree())
  bool binary[getheightoftree()];
  for (int i = 0; i < getheightoftree(); i++)
  {
    binary[i]=(residue%2==1);
    residue=(residue-binary[i])/2;
  }
  for(int i=getheightoftree()-1;i>=0;i--){
    if(binary[i]) currnode=currnode->right;
    else {parent=currnode;currnode=currnode->left;}
  }
  currnode=n;
  n->parent=parentof;
  if(binary[0])parentof->right=n;
  else parentof->left=n;
  
  while(parentof!=root){
    swap(n->object,parentof->object);
    n=n->parent;
    parentof=parentof->parent;
  }
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here


  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  if(node==nullptr){return;}
  while(node!=nullptr){    
    printHeap(node->left);
    cout<<node->object<<" ";
    printHeap(node->right);
  }
  return;
}

  
