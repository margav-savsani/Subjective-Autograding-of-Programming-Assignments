#include <bits/stdc++.h>
#include <math.h>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
TreeNode<T>* Heap<T>::checkempty(TreeNode<T> *node, int no, TreeNode<T>* t){
  /*static int recursionlevel = -1;
  recursionlevel++;
  if(( log2(no_of_elem+1)-int(log2(no_of_elem+1))==0 && recursionlevel>trunc(log2(no_of_elem))) || log2(no_of_elem+1)-int(log2(no_of_elem+1))!=0 && recursionlevel>=trunc(log2(no_of_elem))){
    recursionlevel--;
    return NULL;
  }
  else if(node->left==NULL){
    lft = true;
    recursionlevel--;
    return node;
  }
  else if(node->right==NULL){
    lft = false;
    recursionlevel--;
    return node;
  }
  TreeNode<T>* r = checkempty(node->left,lft);
  if(r!=NULL){
    recursionlevel--;
    return r;
  }
  else {
    TreeNode<T>* r2 = checkempty(node->right,lft);
    recursionlevel--;
    return r2;
  }*/
  TreeNode<T> *nodee = node;
  if(trunc(log2(no_of_elem+1))-log2(no_of_elem+1)==0){
    //l = trunc(log2(no_of_elem+1))+1;
    while(nodee->left!=NULL){
      nodee=nodee->left;
    }
    nodee->left = t; 
    return nodee;
  }
  else {
    int l = trunc(log2(no))+1;
    if(l==2){
      if(nodee->left==NULL){
        nodee->left = t;
        return nodee;
      }
      else{
        nodee->right = t;
        return nodee;
      }
    } 
    else if(pow(2,l)-1-no >= pow(2,l-1)/2){
      return checkempty(nodee->left,no-pow(2,l-2),t);
    }
    else {
      return checkempty(nodee->right,no-pow(2,l-1),t);
    }
  }

}

template<typename T>
void Heap<T>::swap(TreeNode<T> *par, TreeNode<T> *child){
  T obj = par->object;
  par->object = child->object;
  child->object = obj;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T>* node){
  while(node!=NULL){
    if(node->left!=NULL && node->right!=NULL){
      if((node->left)->object.rating>node->object.rating || (node->right)->object.rating>node->object.rating){
        swap(node,maxi(node->left, node->right));
      }
    }
    else if(node->right!=NULL){
      if((node->right)->object.rating>node->object.rating){
        swap(node,node->right);
      }
    }
    else if(node->left!=NULL){
      if((node->left)->object.rating>node->object.rating){
        swap(node,node->left);
      }
    }
    else{ return;}
    node = node->parent;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> t(obj);
  TreeNode<T> *found;
  if(root==NULL){
    root = new TreeNode<T>(t);
    lastelem = root; 
  }
  else {
    found = checkempty(root,no_of_elem, &t);
    //printHeap(root);
    Heapify(found);
    lastelem = &t;
  }
  no_of_elem++;
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  swap(lastelem, root);
  if((lastelem->parent)->right == lastelem)
    (lastelem->parent)->right = NULL;
  else (lastelem->parent)->left = NULL;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  bool isLeft = false;
  if (node != nullptr)
  {
    cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    cout << (node->object).rating << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    isLeft = true;
    // enter the next tree level - left and right branch
    printHeap(node);
    node = curr->right;
    isLeft = false;
    printHeap(node);
    //root = curr;
  }
  return;
}

  
