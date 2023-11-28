#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


TreeNode<T>* bottom_rightmost_node(TreeNode<T>  root){ //makes a new node beside  
  
}

bool operator>(TreeNode<T>* arg1,TreeNode<T>* arg2){

}

template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    TreeNode<T>  *new_node=new TreeNode<T>(obj);
    root=*new_node;
    return;
  } 
  TreeNode<T>  *new_node=bottom_rightmost_node(root),*par_node;
  new_node->object=obj;
  while(new_node->parent != nullptr){
    par_node=new_node->parent;
    if(par_node->left!= nullptr && par_node->right!= nullptr ){
      if(par_node->left>par_node || par_node->right>par_node  ){
        if(par_node->left>par_node->right){
          if(par_node->parent != nullptr){
            T temp=par_node->object;
            par_node->object=par_node->left->object;
            par_node->pa
          }
        }
      }
    }
  }
  

  TreeNode<T>   b=root,c;
  while(b!=nullptr){
    c=b;
    if(b.left=nullptr) break;
    b=*(b.left);
  }
  TreeNode<T> *curr_node=new_node,*par_node ;

  return;
}

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