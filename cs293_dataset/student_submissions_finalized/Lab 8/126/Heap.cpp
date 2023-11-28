#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *curr=new TreeNode(obj);
    if(root==nullptr){
        root=curr;
        end=root;
    }
    else{
        if(end->left==nullptr){
            end->left=curr;
            end=end->left;
        }
        else{
            end->right=curr;
            end=end->right;
        }
        TreeNode<T> *temp=end;
        while(true){
            if(temp->parent->object < temp->object){
                return;
            }
            if(temp->parent == nullptr){
                return;
            }
            else{
                T obj = temp->parent->object;
                temp->parent->object=temp->obect;
                temp->object= obj;
                temp=temp->parent;
            }
        }
    }
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

  
