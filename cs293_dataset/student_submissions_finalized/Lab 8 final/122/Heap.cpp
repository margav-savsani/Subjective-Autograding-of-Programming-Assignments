#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <bits/stdc++.h>

template<typename T>
void Heap<T>::insert(T obj) {
TreeNode<T> *pt;
cout <<"34";
if(root==nullptr){
 TreeNode<T> *ptr = new TreeNode<T>(obj);
 root = ptr;
  nodes++;
  cout <<"15";
}
else{
  int h = 1;
  int n = nodes;
  TreeNode<T> * ptr = root;
  while(true){
    int a = pow(2,h+1) - 1;
    if(n/a == 0){
      break;
    }
    else{
      h++;
    }
    
  }
    while(h != 1){
      if(n > (pow(2,h-1)  + pow(2,h) - 1)){
        n = n - pow(2,h) ;
        ptr = ptr->right;
        h--;
        cout << "!";
        continue;
      }
      else{
        n = n - pow(2,h-1) ;
        ptr = ptr->left;
        h--;
        cout <<"@";
        continue;
      }
      cout << "L";
  }
  if(ptr->left == nullptr){
    pt =  new TreeNode<T>(obj);
    ptr->left = pt;
    pt->parent = ptr;
    cout << "~";
    nodes++;
  }
  else{
    pt =  new TreeNode<T>(obj);
    ptr->right = pt;
    pt->parent = ptr;
    cout << "%";
    nodes++;
  }

while(pt->parent != nullptr){
 if(pt->parent->object < pt->object){
  T t = pt->parent->object;
  pt->parent->object = pt->object;
  pt->object = t; 
  pt = pt->parent;
  cout << "$";
  continue;
 }
 else{
  break;
 }
}
}
cout <<"*";
  return;
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> * ptr;
  cout << "ty";
  if(root->left == nullptr && root->right == nullptr){
    root = nullptr;
    cout <<"rishi";
    return;
  }
  else if(root->right == nullptr){
    root->object = root->left->object;
    root -> left = nullptr;
    return;
  }
  else if(nodes == 3){
    if(root->left->object < root->right->object){
      root->object = root->left->object;
      root->left = root->right;
      root->right == nullptr;
    }
    else {
      root->object = root->right->object;
      root->right = nullptr;
    }
  }
  else{
  int h = 1;
  int n = nodes-1;
  ptr = root;
  while(true){
    int a = pow(2,h+1) - 1;
    cout << "y";
    if(n/a == 0){
      cout <<"r";
      break;
    }
    else{
      h++;
    }
  }
    while(h != 1){
      if(n > (pow(2,h-1)  + pow(2,h) - 1)){
        n = n - pow(2,h) ;
        ptr = ptr->right;
        h--;
        continue;
      }
      else{
        n = n - pow(2,h-1) ;
        ptr = ptr->left;
        h--;
        continue;
      }
    }
  }
  if(ptr->right == nullptr){
    root->object = ptr->left->object;
    ptr->left = nullptr;
  }
  else{
    root->object = ptr->right->object;
    ptr->right = nullptr;
  }
  TreeNode<T> *x = root;
  while(true){
    if(x->right != nullptr && x->left != nullptr){
      if(x->left->object < x->right->object){
       T no = x->left->object;
       x->left->object = no;
       x->object = no;
       x = x->left;
      }
      else{
       T nol = x->right->object;
       x->right->object = nol;
       x->object = nol;
       x = x->right;
    }
   }
    else if(x->left == nullptr){
    nodes--;
    return;
    }
  else if(x->right == nullptr){
       T nea = x->left->object;
       x->left->object = nea;
       x->object = nea;
       nodes--;
       break;
  }

  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
