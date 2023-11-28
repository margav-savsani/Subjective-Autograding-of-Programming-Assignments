#ifndef HEAP_CPP
#define HEAP_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *z = new TreeNode<T>(obj);

  TreeNode<T> *x = locateLast();
  if (x == root){
    x->left = z;
    z->parent = x;
    return;
  }

  if (x->parent->left == x){
    x->parent->right = z;
    z->parent = x->parent;
  }
  else if (x->parent->right == x){
    TreeNode<T> *rightmost = root;
    while(rightmost->right != NULL){
      rightmost = rightmost->right;
    }
    if (x == rightmost) {
      TreeNode<T> *leftmost = root;
      while(leftmost->left != NULL){
        leftmost = leftmost->left;
      }
      leftmost->left = z;
      z->parent = leftmost;
    }
    else {
      TreeNode<T> *next = x;
      while (next->parent->right == next){
        next = next->parent;
      }
      next = next->parent->right; // assert
      while (next->left != NULL){
        next = next->left;
      }
      next->left = z;
      z->parent = next;
    }
    HeapifyUp(z);
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here

  TreeNode<T> *lastNode = locateLast();
  if (lastNode == root){
    root = NULL;
    return;
  }

  T temp = root->object;
  root->object = lastNode->object;
  
  if (lastNode->parent->left == lastNode){
    lastNode->parent->left = NULL;  
  }
  else if (lastNode->parent->right == lastNode){
    lastNode->parent->right = NULL;  
  } 
  HeapifyDown(root);

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here

  // if( root != nullptr )
  //   {
  //       cout << prefix;

  //       cout << (isLeft ? "|--" : "|__" );

  //       // print the value of the node
  //       cout << root->JourneyCode << endl;
  //       TreeNode *curr = root;
  //       root = root->left;
  //       // enter the next tree level - left and right branch
  //       printBST( prefix + (isLeft ? "│   " : "    "), true);
  //       root = curr->right;
  //       printBST( prefix + (isLeft ? "│   " : "    "), false);
  //       root = curr;
  //   }

  return;
}

template<typename T>
void Heap<T>::HeapifyUp(TreeNode<T>* v){
  // check if heap condition is true
  if (v == NULL || v->parent == NULL) return;
  else if (v->parent->left != NULL && v->parent->right == NULL){
    T temp = v->parent->object;
    v->parent->object = v->parent->left->object;
    v->parent->left->object = temp;
    HeapifyUp(v->parent);
  }
  else if (v->parent->left == NULL && v->parent->right != NULL){
    T temp = v->parent->object;
    v->parent->object = v->parent->right->object;
    v->parent->right->object = temp;
    HeapifyUp(v->parent);
  }
  else {
    if (v->parent->object < v->parent->left->object || v->parent->object < v->parent->right->object){
      if (v->parent->right->object < v->parent->left->object){
        T temp = v->parent->object;
        v->parent->object = v->parent->left->object;
        v->parent->left->object = temp;
      }
      else if (v->parent->left->object < v->parent->right->object){
        T temp = v->parent->object;
        v->parent->object = v->parent->right->object;
        v->parent->right->object = temp;
      }
      HeapifyUp(v->parent);
    }
    else {
      return;
    }
  }
}

template<typename T>
void Heap<T>::HeapifyDown(TreeNode<T>* v){
  // check if heap condition is true
  if (v == NULL || (v->left == NULL && v->right == NULL)) return;
  else if (v->left != NULL && v->right == NULL){
    T temp = v->left->object;
    v->left->object = v->object;
    v->object = temp;
    HeapifyDown(v->left);
  }
  else if (v->left == NULL && v->right != NULL){
    T temp = v->right->object;
    v->right->object = v->object;
    v->object = temp;
    HeapifyDown(v->right);
  }
  else {
    if (v->parent->object < v->parent->left->object || v->parent->object < v->parent->right->object){
      if (v->right->object < v->left->object){
        T temp = v->left->object;
        v->left->object = v->object;
        v->object = temp;
        HeapifyDown(v->left);
      }
      else if (v->left->object < v->right->object){
        T temp = v->right->object;
        v->right->object = v->object;
        v->object = temp;
        HeapifyDown(v->right);
      }
    }
    else {
      return;
    }
  }
}

#endif
  
