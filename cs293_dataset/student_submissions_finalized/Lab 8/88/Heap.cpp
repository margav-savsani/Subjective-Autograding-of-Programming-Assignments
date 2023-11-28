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
    root = new TreeNode<T>(obj);
    n=1;
  }
  else{
    n++;
    int pos=n;
    int max_pow_two=0;
    while(n>>(max_pow_two+1) > 0){
      max_pow_two++;
    }
    TreeNode<T> *prev=nullptr, *curr=root;
    for(int i=max_pow_two-1; i>=0; i--){
      prev = curr;
      if((n>>i) & 1){
        curr = curr->right;
      }
      else{
        curr = curr->left;
      }
    }
    if(n & 1){
      prev->right = new TreeNode<T>(obj);
    }
    else{
      prev->left = new TreeNode<T>(obj);
    }
    
    while(prev != nullptr){
      if(prev->object < obj){
        curr->object = prev->object;
        prev-> object = obj;
      }
      else break;
      curr = prev;
      prev = prev->parent;
    }
    
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  
  // insert your code here
  TreeNode<T> max = root->object;
  if(n==1){
    n = 0;
    delete[] root;
    root = nullptr;
  }
  else{
    int pos=n;
    int max_pow_two=0;
    while(n>>(max_pow_two+1) > 0){
      max_pow_two++;
    }
    TreeNode<T> *prev=nullptr, *curr=root;
    for(int i=max_pow_two-1; i>=0; i--){
      prev = curr;
      if((n>>i) & 1){
        curr = curr->right;
      }
      else{
        curr = curr->left;
      }
    }
    root->object = curr->object;
    delete[] curr;
    heapify(root);
  }
  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node) {
  
  // insert your code here
  if(node->left == nullptr) return;
  else if(node->right == nullptr && node->object < node->left->object){
    T obj = node->object;
    node->object = node->left->object;
    node->left->object = obj;
    heapify(node->left);
  }
  else{
    if(node->object < node->left->object && node->object < node->right->object){
      if(node->left->object < node->right->object){
        T obj = node->object;
        node->object = node->right->object;
        node->right->object = obj;
        heapify(node->right);
      }
      else{
        T obj = node->object;
        node->object = node->left->object;
        node->left->object = obj;
        heapify(node->left);
      }
    }
    else if(node->object < node->left->object){
      T obj = node->object;
      node->object = node->left->object;
      node->left->object = obj;
      heapify(node->left);
    }
    else if(node->object < node->right->object){
      T obj = node->object;
      node->object = node->right->object;
      node->right->object = obj;
      heapify(node->right);
    }
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

template<typename T>
void printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<(root->object);
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  /*
  else {
    cout << "NULL tree" << endl;
  }
  */
}
  
