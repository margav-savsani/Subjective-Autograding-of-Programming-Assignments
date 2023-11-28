#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif



template<typename T>
void Heap<T>::recur(TreeNode<T> *node,int nodes1,int nodes2,T obj) {
  if(nodes1<=(nodes2-1/2)){
    node = node->left;
  }
  else{
    node = node->right;
  }
  if(node == nullptr){
    node = new TreeNode(obj);
    num_nodes++;
  }
  recur(node,nodes1-((nodes2-1)/2)-1,(nodes2-1)/2,obj)

}
template<typename T>
void Heap<T>::insert(T obj) {
  if(root == nullptr){
    root = new TreeNode(obj);
    num_nodes++;
  }
  else{
    int p =1;
    nonodes = num_nodes;
    while(nonodes>0) {
      nonodes = nonodes - p;
      p = p*2;
     
    }
    recur(root,num_nodes+1,2*p-1,obj);
  }
  
  return;
}

template<typename T>
void Heap<T>::delMax() {

  

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  

  return;
}

  
