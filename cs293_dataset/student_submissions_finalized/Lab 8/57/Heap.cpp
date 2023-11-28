#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif



vector<int> converter(int number){
  // converts given no into binary form;
  ;}



template<typename T>
void Heap<T>::insert(T obj) {
  if(num==0){
    root=new TreeNode(obj);
    num++; return;
  }
  else{
    vector<int>k=converter(num+1);
    reverse(k.begin(),k.end());
    TreeNode<T> curr=root;
    for(int i=0;i<k.size()-1;i++){
      if(k[i]==0) curr=curr.left;
      else curr=curr.right;
    }
    if(k[k.size()-1]==0){
      curr.left=new TreeNode(obj);
      curr.left->parent=curr;
      return;

  // insert your code here

  return;
}}}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}



