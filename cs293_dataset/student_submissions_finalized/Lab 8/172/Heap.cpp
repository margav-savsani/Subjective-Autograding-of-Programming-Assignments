
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> newNode=new TreeNode(obj);
  if(root==nullptr) {
    root=new TreeNode(obj);
    lastNode=root;
  }
  else{
    TreeNode<T> last=lastNode;
    TreeNode<T> last_par=lastNode->parent;
    int found_place=0;
    while(last_par!=nullptr){
     if(last_par->left==last){
      last_par->right=newNode;
      newNode->parent=last_par->right;
      lastNode=newNode;
      found_place=1;
      break;
     }
     else{
      last_par=last_par->parent;
      last=last_par;
     }
    }
    if(found_place!=1){
      TreeNode<T> left_most=root;
      while(left_most->left!=nullptr){
        left_most=left_most->left;
      }
      left_most->left=newNode;
      newNode->parent=left_most->left;
      lastNode=newNode;
    }
  }
  TreeNode<T> last=lastNode;
  TreeNode<T> last_par=newNode->parent;
  while(last_par!=nullptr){
    if(last_par->object<last->object){
      T obj=last_par->object;
      last_par->object=last->object;
      last->object=T;
    }
    else{break;}
    last=last_par;
    last_par=last_par->parent;
  }
  return;
}

template<typename T>
T Heap<T>::delMax(){
  root->object=lastNode->object;
  if(lastNode->parent->left==lastNode){lastNode->parent->left=nullptr;}
  else lastNode->parent->right=nullptr;
  TreeNode<T> abs_root=root;
  while(abs_root!=nullptr){
    if(abs_root->left!=nullptr && root->right!=nullptr){
      if(abs_root->object<abs_root->left->object && abs_root->object<abs_root->right->object){
        if(abs_root->left->object>abs_root->right->object){
          T obj=abs_root->object;
          abs_root->object=abs_root->left->object;
          abs_root->left->object=T;
          abs_root=abs_root->left;
        }
        else{
          T obj=abs_root->object;
          abs_root->object=abs_root->right->object;
          abs_root->right->object=T;
          abs_root=abs_root->right;
        }
      }
      else break;
    }
    else if(abs_root->left!=nullptr && abs_root->right==nullptr){
      if(abs_root->left->object>abs_root->object){
         T obj=abs_root->object;
         abs_root->object=abs_root->left->object;
         abs_root->left->object=T;
         abs_root=abs_root->left;
      }
      else break;
    }
    else if(abs_root->left==nullptr && abs_root->right==nullptr){
      break;
    }
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node){
  //not done yet
  // insert your code here
  int height=0;
  if(root!=nullptr){
    cout<<root->object;
    height++;
  }
  printHeap(node->left);
  printHeap(node->right);
  return;
}

  
