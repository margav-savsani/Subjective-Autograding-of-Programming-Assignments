#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <bits/stdc++.h>

template<typename T>
TreeNode<T> *parent(TreeNode<T> *root,int x,int h){
    
    if(h==1 || h==0){ return root; }
    else{
        double a = pow(2,h); int b = a;
        if(x >= b-1 && x <= b + b/2 -2){ return parent(root->left,x - b/2,h-1); }
        else { return parent(root->right, x - b,h-1); }
    }
    
}

template<typename T>
int lr(TreeNode<T> *parent, TreeNode<T> *child){
    if(parent->left==child) return 0;
    else { return 1; }
}

template<typename T>
void heapify(TreeNode<T> *child){
    
    if(child->parent == nullptr){ return; }
    else{
       if(lr(child->parent,child)){  }
       else {  }
    }
}

template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr) { root = new TreeNode(obj); return; }
  else{
      int x = n;
      int h = log2(n+1);
  
      TreeNode<T> *p = parent(root,x,h);
  
      if(p->left==nullptr) { p->left = new TreeNode(obj); (p->left)->parent=p; heapify(p->left);}
      else { p->right = new TreeNode(obj); (p->right)->parent=p; heapify(p->right);}
  
      n++;
      return;
   }   
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here

  return root;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
