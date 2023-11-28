#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::setTail(TreeNode<T> *node){
  if(node->parent == nullptr){
    tail = node;
    while(tail->left != nullptr){
      tail = tail->left;
    }
  }
  else if(node->parent->left == node){
    tail = node->parent->right;
    while(tail->left != nullptr){
      tail = tail->left;
    }
  }
  else if(node->parent->right == node){
    setTail(node->parent);
  }
}

template<typename T>
void Heap<T>::swap(TreeNode<T> *node1,TreeNode<T> *node2){
  T temp = node1->object;
  node1->object = node2->object;
  node2->object = temp;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if(node->parent != nullptr && node->parent->object < node->object){
    swap(node, node->parent);
    heapify(node->parent);
  }
}

template<typename T>
void Heap<T>::revHeapify(TreeNode<T> *node)
{
  if (node == nullptr || node->left == nullptr)
    return;
  TreeNode<T> *max = node->left;
  if (node->right != nullptr && max->object < node->right->object )
  {
    max = node->right;
  }
  if (node->object < max->object)
  {
    swap(node, max);
    revHeapify(max);
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){
    root = new TreeNode<T>(obj);
    tail = root;
  } 
  else if(tail->left == nullptr){
    tail->left = new TreeNode<T>(obj);
    tail->left->parent = tail;
    heapify(tail->left);
  }
  else{
    tail->right = new TreeNode<T>(obj);
    tail->right->parent = tail;
    heapify(tail->right);
    TreeNode<T> *prevTail = tail;
    setTail(tail);
    tail->prev = prevTail;
  }
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if (root == nullptr) return;
  if (tail == root)
  {
    tail = nullptr;
    root = nullptr;
  }
  else if (tail->right != nullptr){
    swap(tail->right, root);
    tail->right = nullptr;
    revHeapify(root);
  } 
  else if (tail->left != nullptr){
    swap(tail->left, root);
    tail->left = nullptr;
    revHeapify(root);
  }
  else{
    tail = tail->prev;
    delMax();
  }
  return;
}

template<typename T>
void Heap<T>::print(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;

    print(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    print(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  print(root, "", false);
  return;
}

