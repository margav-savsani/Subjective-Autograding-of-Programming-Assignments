#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"


// Max Heap -------------------------BHOOLNA MAT------------------------
template<typename T>
bool Heap<T>::Heapify(TreeNode<T>* node){
  if(!(node->left->object < node->object && node->right->object < node->object)){
    if(node->left->object < node->right->object){
      T object = node->right->object;
      node->right->object = node->object;
      node->object = object;
    }  
    else{
      T object = node->left->object;
      node->left->object = node->object;
      node->object = object;
    }
    return true;
  }
  else{
    return false;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  if(root == nullptr){
    root->object = obj;
    lastparent = root;
    newadd = root;
  }
  else{
    TreeNode<T> *par = lastparent;
    if(par->left == nullptr){
      par->left = new TreeNode<T>(obj);
      newadd = par->left; 
    }
    else{
      par->right = new TreeNode<T>(obj);
      if(par->parent == nullptr){
        lastparent = par->left->left;
      }
      else{
        if(par->parent->right == par){
          lastparent = par->parent->left->left;
        }
        else{
          lastparent = par->parent->right;
        }
      }
      newadd = par->right; 
    }
  }

  while(newadd == nullptr){
    if (newadd->object < newadd->parent->object) break;
    else{
      T object = newadd->object;
      newadd->object = newadd->parent->object;
      newadd->parent->object = newadd->object;
    }
  }
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  if(lastparent->left == nullptr){

  }
  else{
    root->object = lastparent->left->object;
    lastparent->left == nullptr;
    //then update lastparent, newadd
    TreeNode<T> *curr = root;
    while(curr != nullptr){
      if(!(curr->object > curr->right->object && curr->object > curr->left->object)){
        //Note curr->right and curr->left may be nullptr
        Heapify(curr);
      }
    }
  }

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  if( root != nullptr){
      bool isLeft=false
      cout << (isLeft ? "|--" : "|__" );

      // print the value of the node
      cout << root->object << endl;
      TreeNode<T> *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printHeapT( (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printHeap( (isLeft ? "│   " : "    "), false);
      root = curr;
  }
  
  return;
}

#endif
  
