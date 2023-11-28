#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode* x = new TreeNode(obj);
  if(last_inserted == nullptr){
    root = x;
    last_inserted = x;
  }
  else{
    TreeNode* currNode = last_inserted;
    TreeNode* parentNode = currNode->parent;
    while(parentNode!=nullptr){
      if(parentNode->left == currNode) break;
      else{
        currNode = parentNode;
        parentNode = parentNode->parent;
      }
    }
    if(parentNode == nullptr){
      while(currNode->left != nullptr){
        currNode = currNode->left;
      }
      currNode->left = x;
      x->parent = currNode;
      last_inserted = x;
    }
    else{
      currNode = parentNode->right;
      if(currNode == nullptr){
        parentNode->right = x;
        x->parent = parentNode;
        last_inserted = x;
      }
      else{
        while(currNode->left != nullptr){
        currNode = currNode->left;
      }
        currNode->left = x;
        x->parent = currNode;
        last_inserted = x;
      }
    }
  }
  parentNode = x->parent;
  while(parentNode != nullptr){
    if(x->object->rating > parentNode->object->rating){
      swap(x->object,parentNode->object);
      x = parentNode;
      parentNode = parentNode->parent;
    }
    else{
      break;
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  //swapping the last_inserted node content with root content
  swap(root->object,last_inserted->object);
  TreeNode* parentNode = last_inserted->parent;
  if(parentNode == nullptr){
    root = nullptr;
    last_inserted = nullptr;
    return;
  }
  if(parentNode->left == last_inserted){
    TreeNode* currentNode = last_inserted;
    parentNode->left == nullptr;
    while(parentNode != nullptr){
      if(parentNode->right == currentNode){
        break;
      }
      currentNode = parentNode;
      parentNode = parentNode->parent;
    }
    if(parentNode != nullptr){
    currentNode = parentNode->left;
    }
    while(currentNode->right != nullptr){
      currentNode = currentNode->right;
    }
    last_inserted = currentNode;
    heapify(root);
  }
  else{
    parentNode->right == nullptr;
    last_inserted = parentNode->left;
    heapify(root);
  }

  return;
}

void Heap<T>::heapify(TreeNode* node){
  TreeNode *maxNode;
  if(node->left == nullptr && node->right == nullptr){
    return;
  }
  if(node->right == nullptr){
    if(node->left->object->rating > node->object->rating){
      swap(node->object,node->left->object);
      node = node->left;
      heapify(node);
      return;
    }
    else{
      return;
    }
  }
  else{
    if(node->left->object->rating > node->right->object->rating){
      swap(node->object,node->left->object);
      node = node->left;
      heapify(node);
      return;
    }
    else{
      swap(node->object,node->right->object);
      node = node->right;
      heapify(node);
      return;
    }
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  if(node == nullptr) return;
  else{
    cout << node->object->rating << " ";
    printHeap(node->left);
    printHeap(node->right);
  }

  return;
}

  
