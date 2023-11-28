#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

int heap_size = 0; string heapBinarySize = "0";

string bin(int n){
    string x = "";
    if (n > 1)
        x += bin(n / 2);
    x += to_string(n % 2);
    return x;
}

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *z = new TreeNode<T>(obj);
  TreeNode<T> *x = locateLast();
  
  if (x == NULL){
    root = z;
  }
  else if (x == root){
    x->left = z;
    z->parent = x;
    HeapifyUp(z);
  }
  else {
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
        next = next->parent->right;
        while (next->left != NULL){
          next = next->left;
        }
        next->left = z;
        z->parent = next;
      }
    }
    HeapifyUp(z);
  }

  heap_size++; heapBinarySize = bin(heap_size);
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> *lastNode = locateLast();
  if (lastNode == NULL) return;
  heap_size--; heapBinarySize = bin(heap_size);
  
  if (lastNode == root) root = NULL;
  else {
    root->object = lastNode->object;
    if (lastNode->parent->left == lastNode) lastNode->parent->left = NULL;
    else if (lastNode->parent->right == lastNode) lastNode->parent->right = NULL;
    
    HeapifyDown(root);
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node, const string& prefix, bool isLeft) {
  if( node != nullptr ){
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );

        cout << node->object<< endl;
        printHeap(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printHeap(node->right, prefix + (isLeft ? "│   " : "    "), false);
  }
}

template<typename T>
TreeNode<T>* Heap<T>::locateLast(){
  TreeNode<T> *x = root;
  if (heap_size == 0) return NULL;
  if (heap_size == 1) return root;

  for (int i=1; i<heapBinarySize.length(); i++){
    if (heapBinarySize[i]=='0'){
      x = x->left;
    }
    else if (heapBinarySize[i]=='1'){
      x = x->right;
    }
  }
  return x;
} 

template<typename T>
void Heap<T>::HeapifyUp(TreeNode<T>* v){
  if (v == NULL || v->parent == NULL) return;
  else if (v->parent->left != NULL && v->parent->right == NULL){
    if (v->parent->object < v->parent->left->object){
      T temp = v->parent->object;
      v->parent->object = v->parent->left->object;
      v->parent->left->object = temp;
    }
    HeapifyUp(v->parent);
  }
  else if (v->parent->left == NULL && v->parent->right != NULL){
    if (v->parent->object < v->parent->right->object){
      T temp = v->parent->object;
      v->parent->object = v->parent->right->object;
      v->parent->right->object = temp;
    }
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
  if (v == NULL) return;
  if (v->left == NULL && v->right == NULL) return;
  else if (v->left != NULL && v->right == NULL){
    if (v->object < v->left->object){
      T temp = v->left->object;
      v->left->object = v->object;
      v->object = temp;
    }
    HeapifyDown(v->left);
  }
  else if (v->left == NULL && v->right != NULL){
    if (v->object < v->right->object){
      T temp = v->right->object;
      v->right->object = v->object;
      v->object = temp;
    }
    HeapifyDown(v->right);
  }
  else {
    if (v->object < v->left->object || v->object < v->right->object){
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