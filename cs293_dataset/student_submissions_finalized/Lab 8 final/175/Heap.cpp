#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <bitset>

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if (root == nullptr){ // the 'root' case
    count = 1;
    root = new TreeNode<T>(obj);
    return;
  }
  count ++;
  string str = bitset< 32 >(count).to_string(); // converting to bit strings
  int pos = 0;
  while (str[pos] == '0'){
    pos ++;
  }
  TreeNode<T> *tmp = root, *parent = nullptr;
  for (int i = pos + 1; i < str.size(); i++){ // of the bit is 0, go left else go right
    parent = tmp;
    if (str[i] == '0'){
      tmp = tmp->left;
    }
    else if (str[i] == '1'){
      tmp = tmp->right;
    }
  }
  if (count % 2 == 0){
    parent->left = new TreeNode<T>(obj); // insert a new node
    tmp = parent->left;
  }
  else{
    parent->right = new TreeNode<T>(obj); // insert a new node
    tmp = parent->right;
  }
  tmp->parent = parent;
  while(tmp->object.rating > tmp->parent->object.rating){ // bubble the new element upwards if its parent has lower rating than itself
    T foo = tmp->object;
    tmp->object = tmp->parent->object;
    tmp->parent->object = foo;
    tmp = tmp->parent;
    if (tmp == root) break;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  if (count == 1){ // the 'root' case
    root = nullptr;
    count --;
    return;
  }
  string str = bitset< 32 >(count).to_string(); // converting to bit strings
  int pos = 0;
  while (str[pos] == '0'){
    pos ++;
  }
  TreeNode<T> *tmp = root, *parent = nullptr;
  for (int i = pos + 1; i < str.size(); i++){ // of the bit is 0, go left else go right
    parent = tmp;
    if (str[i] == '0'){
      tmp = tmp->left;
    }
    else if (str[i] == '1'){
      tmp = tmp->right;
    }
  }
  T foo =tmp->object; // we have found the last object in the heap
  if (count % 2 == 0){
    parent->left = nullptr; // deleting the child
  }
  else{
    parent->right = nullptr; // deleting the child
  }
  count --;
  root->object = foo; // swapping the last element with the root
  tmp = root;
  while (true){ // performing a heapify on the 'root'
    if (tmp->left == nullptr && tmp->right == nullptr) break; // nothing to do if its a leaf
    else if (tmp->right == nullptr){ // the main idea is, if the element is smaller than its children, then swap the element with it
      if (tmp->object.rating >= tmp->left->object.rating) break;
      else{
        foo = tmp->object;
        tmp->object = tmp->left->object;
        tmp->left->object = foo;
        break;
      }
    }
    else{ // the main idea is, if the element is smaller than any of its children, then swap the element with the maximum of the two children
      if (tmp->object.rating >= tmp->left->object.rating && tmp->object.rating >= tmp->right->object.rating) break;
      else if (tmp->object.rating >= tmp->left->object.rating && tmp->object.rating < tmp->right->object.rating){
        foo = tmp->object;
        tmp->object = tmp->right->object;
        tmp->right->object = foo;
        tmp = tmp->right;
      }
      else if (tmp->object.rating < tmp->left->object.rating && tmp->object.rating >= tmp->right->object.rating){
        foo = tmp->object;
        tmp->object = tmp->left->object;
        tmp->left->object = foo;
        tmp = tmp->left;
      }
      else{
        if (tmp->left->object.rating >= tmp->right->object.rating){
          foo = tmp->object;
          tmp->object = tmp->left->object;
          tmp->left->object = foo;
          tmp = tmp->left;
        }
        else{
          foo = tmp->object;
          tmp->object = tmp->right->object;
          tmp->right->object = foo;
          tmp = tmp->right;
        }
      }
    }
  }
  return;
}

template<typename T>
void Heap<T>::print(const string& prefix, TreeNode<T> *node, bool isLeft)
{
  // copied from Lab 3 and made some cosmetic changes
  if( node != nullptr )
  {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__" );

      // print the value of the node
      cout << node->object << endl;
      // enter the next tree level - left and right branch
      print( prefix + (isLeft ? "│   " : "    "), node->left, true);
      print( prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here
  print("", node); // calling the helper function
  return;
}

template<typename T>
void Heap<T>::recursiveDelete(TreeNode<T> *currNode) { // frees memory recursively
  if (currNode != nullptr) {
    TreeNode<T> *leftChild = currNode->left;
    TreeNode<T> *rightChild = currNode->right;
  
    delete currNode;
    recursiveDelete(leftChild);
    recursiveDelete(rightChild);
  }
  return;
}