#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  if(root == nullptr){
    root = new TreeNode<T>(obj);
    lastNode = root;
    return;
  }

  TreeNode<T>* nextParent = lastNode;
  while(true){
    if(nextParent == root){
      while(nextParent->left != nullptr){
        nextParent = nextParent->left;
      }

      nextParent->left = new TreeNode<T>(obj);
      lastNode = nextParent->left;
      lastNode->parent = nextParent;
      
      TreeNode<T>* currNode = lastNode;
      TreeNode<T>* parentNode = lastNode->parent;

      while(parentNode != nullptr){
        if(currNode->object < parentNode->object){
          break;
        }
        swap(currNode->object, parentNode->object);

        currNode = currNode->parent;
        parentNode = parentNode->parent;
      }
      return;
    }

    if(nextParent->parent->left == nextParent){
      nextParent = nextParent->parent;
      break;
    }

    nextParent = nextParent->parent;
  }

  if(nextParent->right == nullptr){
    nextParent->right = new TreeNode<T>(obj);
    lastNode = nextParent->right;
    lastNode->parent = nextParent;
  }

  else{
    nextParent = nextParent->right;

    while(nextParent->left != nullptr){
      nextParent = nextParent->left;
    }

    nextParent->left = new TreeNode<T>(obj);
    lastNode = nextParent->left;
    lastNode->parent = nextParent;
  }

  TreeNode<T>* currNode = lastNode;
  TreeNode<T>* parentNode = lastNode->parent;

  while(parentNode != nullptr){
    if(currNode->object < parentNode->object){
      break;
    }
    swap(currNode->object, parentNode->object);
    
    currNode = currNode->parent;
    parentNode = parentNode->parent;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  if (node == nullptr){return;}
  printHeap(node->left);
  std::cout << node->object << " ";
  printHeap(node->right);

  return;
}

  
