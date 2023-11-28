#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
//goes to the parent of the num array-indexed node
TreeNode<T> *goToPrev(int num, TreeNode<T> *root){
  if(num == 1) return NULL;
  TreeNode<T> *curr = root;
  int i = 1;
  while(i <= num){
    i *= 2;
  }
  i = i / 2;
  int k = (num - i);
  i = i / 2;
  while(k >= 0){
    if(i == 1) return curr;
    if(k >= i){
      curr = curr->right;
      k -= i;
    }
    else curr = curr->left;
    i = i / 2;
  }
  //shouldn't reach here.
  return NULL;
}

template<typename T>
void Heap<T>::insert(T obj) {
	// insert your code here
  num++;
  if(num == 1){
    root = new TreeNode<T>(obj);
    last = root;
    return;
  }
  TreeNode<T> *curr = goToPrev(num, root);
  if(curr->left == NULL){
    curr->left = new TreeNode<T>(obj);
    curr->left->parent = curr;
    curr = curr->left;
  }
  else{
    curr->right = new TreeNode<T>(obj);
    curr->right->parent = curr;
    curr = curr->right;
  }
  //now curr points to the newly inserted node. (numbered num)
  last = curr;
  //bubble up the value until heap balance restored
  while(curr->parent != NULL && curr->parent->object < curr->object){
    T temp = curr->parent->object;
    curr->parent->object = curr->object;
    curr->object = temp;
    curr = curr->parent;
  }
}

template<typename T>
T Heap<T>::delMax() {
	// insert your code here
  num--;
  if(last == root){
    T temp = root->object;
    delete root;
    return temp;
  }
  T to_return = root->object;
  root->object = last->object;
  //to heapify it from the root.
  //deleting the last node, resetting it.
  if(last->parent->left == last){
    last->parent->left = NULL;
  }
  else last->parent->right = NULL;
  delete last;
  if(num == 1) last = root;
  else{
    TreeNode *prev = goToPrev(num, root);
    if(prev->right != NULL){
      last = prev->right;
    }
    else last = prev->last;
  }
  //heapify from the root.
  TreeNode *curr = root;
  while(curr->left != NULL && curr->object < curr->left->object
    ||  curr->right != NULL && curr->object < curr->right->object){
      T local_max;
      if(curr->left->object > curr->right->object){
        local_max = curr->left->object;
        curr->left->object = curr->object;
        curr->object = local_max;
      }
      else{
        local_max = curr->right->object;
        curr->right->object = curr->object;
        curr->object = local_max;
      }
  }
  return to_return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

	// insert your code here

	return;
}


