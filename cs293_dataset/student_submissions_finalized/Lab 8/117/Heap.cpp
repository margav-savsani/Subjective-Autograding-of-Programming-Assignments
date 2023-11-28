#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){
    root = new TreeNode (obj);
    last = root;
    return;
  }
  TreeNode<T>* myMin = last;
  bool completeTree = 0;
  while(myMin->parent != nullptr){
    if(myMin->parent->right != myMin){
      break;
    }
    myMin=myMin->parent;
  }
  if(myMin->parent == nullptr){
    while(myMin->left != nullptr){
      myMin = myMin->left;
    }
    myMin->left = new TreeNode (obj);
    myMin->left->parent = myMin;
    last = myMin->left;
    myMin = last;
  }
  else{
    if(myMin->parent->right == nullptr){
      myMin->parent->right = new TreeNode (obj);
      myMin->parent->right->parent = myMin->parent;
      last = myMin->parent->right;
      myMin = last;
    }
    else{
      myMin = myMin->parent->right;
      while(myMin->left != nullptr){
        myMin = myMin->left;
      }
      myMin->left = new TreeNode (obj);
      myMin->left->parent = myMin;
      last = myMin->left;
      myMin = last;
    }
  }
  while(true){
    if(myMin->parent == nullptr) break;
    if(myMin->parent->object < myMin->object){
      T temp =myMin->object;
      myMin->object = myMin->parent->object;
      myMin->parent->object = temp;
    }
    else{
      break;
    }
    myMin=myMin->parent;
  }
  return;
}

template<typename T>
T Heap<T>::delMax() {
  T ans = getMax();
  // insert your code here
  TreeNode<T>* originalLast = last;
  root->object = last->object;
  if(root->left == nullptr and root->right == nullptr){
    delete(root);
    root = nullptr;
    return ans;
  }
  while(last->parent != nullptr){
    if(last->parent->left != last){
      break;
    }
    last = last->parent;
  }
  if(last->parent == nullptr){
    while(last->right != nullptr){
      last = last->right;
    }
  }
  else{
    if(last->left != nullptr){    
      last = last->left;
      while(last->right != nullptr){
        last = last->right;
      }
    }
  }
  if(originalLast->parent->right == originalLast) originalLast->parent->right = nullptr;
  else originalLast->parent->left = nullptr;
  delete(originalLast);
  if(root == nullptr) return ans;
  heapify(root);
  return ans;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  if(node == nullptr) return;
  cout << node->object<< endl;
  //cout << last->object<< endl;
  printHeap(node->left);
  printHeap(node->right);
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::myprint(){
  printHeap(root);
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node){
  while(true){
    if(node->right == nullptr && node->left == nullptr) return;
    else{
      if(node->right == nullptr){
        if(node->object < node->left->object){
          T temp = node->object;
          node->object = node->left->object;
          node->left->object = temp;
        }
        return;
      }
      else{
        if(node->object < node->right->object  &&  node->left->object < node->right->object ){
          T temp = node->object;
          node->object = node->right->object;
          node->right->object = temp;
          node = node->right;
        }
        else if(node->object < node->left->object &&  node->right->object < node->left->object){
          T temp = node->object;
          node->object = node->left->object;
          node->left->object = temp;
          node = node->left;
        }
        else return;
      }
    }
  }
}