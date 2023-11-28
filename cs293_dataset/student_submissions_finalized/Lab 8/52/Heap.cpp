#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <vector>

void binary(int n, vector<int>& v){
  while(n>0){
    v.push_back(n%2);
    n /= 2;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  if(n==0){
    root = new TreeNode<T>(obj);
    n++;
    return;
  }

  vector<int> path;
  binary(n+1, path);
  int l = path.size();

  TreeNode<T>* curr = root;
  for (int i = l-2; i > 0; i--)
  {
    if(path[i]){
      curr = curr->right;
    }
    else{
      curr = curr->left;
    }
  }

  TreeNode<T>* node = new TreeNode<T>(obj);
  if(path[0]){
    curr->right = node;
  }
  else{
    curr->left = node;
  }
  node->parent = curr;

  while(node->parent != nullptr && node->object > node->parent->object){
    swap(node->object, node->parent->object);
    node = node->parent;
  }

  n++;

  return;
}

template<typename T>
T Heap<T>::delMax() {
  T deleted;
  if(n==1){
    deleted = root->object;
    delete root;
    root = nullptr;
    n--;
    return deleted;
  }

  vector<int> path;
  binary(n, path);
  int l = path.size();

  TreeNode<T>* curr = root;
  for (int i = l-2; i > 0; i--)
  {
    if(path[i]){
      curr = curr->right;
    }
    else{
      curr = curr->left;
    }
  }

  if(path[0]){
    swap(root->object, curr->right->object);
    deleted = curr->right->object;
    delete curr->right;
    curr->right = nullptr;
  }
  else{
    swap(root->object, curr->left->object);
    deleted = curr->left->object;
    delete curr->left;
    curr->left = nullptr;
  }
  
  Heapify(root);
  n--;

  return deleted;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printBinaryTree(root, "", false);
  return;
}

template<typename T>
void printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft){
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

template<typename T>
void Heapify(TreeNode<T> *node){
  TreeNode<T> * max = node;
  if(node->left != nullptr && node->left->object > node->object){
    max = node->left;
  }
  if(node->right != nullptr && node->right->object > max->object){
    max = node->right;
  }

  if(max != node){
    swap(node->object, max->object);
    Heapify(max);
  }
}


  
