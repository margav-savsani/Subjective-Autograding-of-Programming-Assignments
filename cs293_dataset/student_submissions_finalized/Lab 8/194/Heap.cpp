#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  TreeNode<T> *ins_node = new TreeNode<T> (obj);

  if(root==nullptr){
    root = ins_node;
    tail = ins_node->left;
    tail->parent=root;
    return;
  }
  
  tail->object = ins_node->object;
  
  //tail->parent = ins_node->parent;
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  
  if(root==nullptr){
    return;
  }

  
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  
  // insert your code here
  if(node==nullptr){
    return;
  }
  cout<<node->object<<" ";
  printHeap(node->left);
  printHeap(node->right);
  return;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) {
  while(true){ 
    if(node->left==nullptr && node->right==nullptr){
      break;
    }
    else if(node->right==nullptr){
      if(node->left->object > node->object){
        Swap(node,node->left);
        continue;
      }
      else{
        break;
      }
    }
    else{
      if((node->left->object>node->object)&&(node->right->object>node->object)){
        if(node->left->object > node->right->object){
          Swap(node,node->left);
          continue;
        }
        else{
          Swap(node,node->right);
          continue;
        }
      }
      else if(node->left->object>node->object){
        Swap(node,node->left);
        continue;
      }
      else if(node->right->object>node->object){
        Swap(node,node->right);
        continue;
      }
      else{
        break;
      }
    }
  }
  return;
}
  
template<typename T> 
void Heap<T>::Swap(TreeNode<T> *node1, TreeNode<T> *node2){
  T object1 = node1->object;
  node1->object = node2->object;
  node2->object = object1;
}